#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <random>
#include <regex>
#include <unordered_map>

static pxl::Logger logger("Splitter");


class Splitter:
    public pxl::Module
{
    private:
        struct SelectionInfo
        {   
            int selected;
            int total;
            
            SelectionInfo():
                selected(0), total(0)
            {
            }
        };
    
        pxl::Source* _outputSource;
        pxl::Source* _outputVetoSource;
        
        
        std::vector<std::pair<std::regex,double>> _splitPercentages;
        std::vector<std::pair<std::regex,int>> _splitLimits;
        
        bool _random;
        bool _useEventNumber;
        bool _useExistingFlag;
        
        std::string _processNameField;
        
        unsigned int _passedEvents;
        unsigned int _selectedEvents;
        
        std::string _splitName;
        
        std::random_device _randomDevice;
        std::mt19937 _generator;
        std::uniform_real_distribution<> _uniformDist;
        
        std::unordered_map<std::string,SelectionInfo> _splittingInfo;
        
    public:
        Splitter():
            Module(),
            _random(false),
            _useExistingFlag(false),
            _useEventNumber(true),
            _processNameField("ProcessName"),
            _passedEvents(0),
            _selectedEvents(0),
            _splitName("testing"),
            _generator(_randomDevice()),
            _uniformDist(0, 1)
            
        {
            addSink("input", "input");
            _outputSource = addSource("output","output");
            _outputVetoSource = addSource("veto","veto");
            
            addOption("process name field","",_processNameField);
            
            addOption("percentages","percentage of events to select",std::vector<std::string>{"[A-Za-z0-9_\\-]+=0.7"});
            addOption("limits","limit the events to split per process",std::vector<std::string>{"[A-Za-z0-9_\\-]+=-1"});
            addOption("random","select events randomly",_random);
            addOption("use event number","select events based on the event number,lumi,run",_useEventNumber);
            addOption("use existing flag","use flag from previous module",_useExistingFlag);
            
            addOption("split name","UR name to indicate if selected or not",_splitName);            
        }

        ~Splitter()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("Splitter");
            return type;
        }

        // static and dynamic methods are needed
        const std::string &getType() const
        {
            return getStaticType();
        }

        bool isRunnable() const
        {
            // this module does not provide events, so return false
            return false;
        }

        void initialize() throw (std::runtime_error)
        {
        }

        void beginJob() throw (std::runtime_error)
        {
            getOption("process name field",_processNameField);
        
            std::vector<std::string> percentages;
            std::vector<std::string> limits;
            
        
            getOption("percentages",percentages);
            getOption("limits",limits);
            
            
            for (auto it: percentages)
            {
                int pos = it.find("=");
                if (pos ==std::string::npos)
                {
                    throw std::runtime_error("Splitter percentage not found in '"+it+"'");
                }
                double percentage = std::atof(it.substr(pos+1).c_str());
                std::regex regex(it.substr(0,pos));
                _splitPercentages.emplace_back(regex,percentage);
            }
            
            for (auto it: limits)
            {
                int pos = it.find("=");
                if (pos ==std::string::npos)
                {
                    throw std::runtime_error("Splitter percentage not found in '"+it+"'");
                }
                int limit = std::atoi(it.substr(pos+1).c_str());
                std::regex regex(it.substr(0,pos));
                _splitLimits.emplace_back(regex,limit);
            }
            
            getOption("random",_random);
            getOption("use event number",_useEventNumber);
            getOption("use existing flag",_useExistingFlag);
            getOption("split name",_splitName);
            
            if (_random && _useEventNumber)
            {
                throw std::runtime_error(getName()+": Inconsistent configuration! use either 'random' or 'event number' but not both.");
            }
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                
                if (event->getUserRecord("isRealData").toBool())
                {
                    event->setUserRecord(_splitName,true);
                    event->setUserRecord(_splitName+"_frac",1.0);
                    _outputSource->setTargets(event);
                    return _outputSource->processTargets();
                }
                
                std::string processName = event->getUserRecord(_processNameField);
                if (event->hasUserRecord("nparton"))
                {
                    processName+=std::to_string(event->getUserRecord("nparton").toInt32())+"q";
                }
                if (event->hasUserRecord("nparton4"))
                {
                    processName+=std::to_string(event->getUserRecord("nparton4").toInt32())+"c";
                }
                if (event->hasUserRecord("nparton5"))
                {
                    processName+=std::to_string(event->getUserRecord("nparton5").toInt32())+"b";
                }
                
                if (_splittingInfo.find(processName)==_splittingInfo.end())
                {
                    _splittingInfo[processName] = SelectionInfo();
                }
                _splittingInfo[processName].total+=1;
                
                
                bool selected = false;
                double percentage = 1.0;
                int limit = std::numeric_limits<int>::max();
                
                
                

                
                if (_useExistingFlag)
                {
                    if (not (event->hasUserRecord(_splitName) or event->hasUserRecord(_splitName+"_frac")))
                    {
                        selected = true;
                        percentage = 1.0;
                    }
                    else
                    {
                        selected = event->getUserRecord(_splitName).toBool();
                        percentage = selected?event->getUserRecord(_splitName+"_frac").toDouble():1-event->getUserRecord(_splitName+"_frac").toDouble();
                    }
                }
                else
                {
                    for (auto itPercentage: _splitPercentages)
                    {
                        if (std::regex_match(processName,itPercentage.first))
                        {
                            percentage=itPercentage.second;
                            break;
                        }
                    }
                    for (auto itLimit: _splitLimits)
                    {
                        if (std::regex_match(processName,itLimit.first))
                        {
                            limit=itLimit.second;
                            break;
                        }
                    }
                
                    
                    if ((limit>0) and (limit<_splittingInfo[processName].selected))
                    {
                        selected = true;
                        percentage = 1.0;
                    }
                    else
                    {
                        
                        if (_random)
                        {
                            selected = _uniformDist(_generator)<percentage;
                        }
                        else if (_useEventNumber)
                        {
                            long eventNumber = event->getUserRecord("Event number").toUInt64();
                            long lumiSection = event->getUserRecord("LuminosityBlock").toUInt32();
                            
                            std::size_t hash = 0x9e3779b9;
                            hash ^= std::hash<long>{}(eventNumber) + 0x9e3779b9 + (hash<<6) + (hash>>2);
                            hash ^= std::hash<long>{}(lumiSection) + 0x9e3779b9 + (hash<<6) + (hash>>2);
                  
                            selected = 0.001*(hash%1000)<percentage;
                        }
                        else
                        {
                            double fraction = 1.0*_splittingInfo[processName].selected/_splittingInfo[processName].total;
                            selected = fraction<percentage;
                        }
                    }
                }
                
                
                if (selected)
                {
                    event->setUserRecord(_splitName,true);
                    event->setUserRecord(_splitName+"_frac",percentage);
                    _splittingInfo[processName].selected+=1;
                    _outputSource->setTargets(event);
                    return _outputSource->processTargets();
                }
                else
                {
                    event->setUserRecord(_splitName,false);
                    event->setUserRecord(_splitName+"_frac",1.-percentage);
                    _outputVetoSource->setTargets(event);
                    return _outputVetoSource->processTargets();
                }
                
            }
            catch(std::exception &e)
            {
                throw std::runtime_error(getName()+": "+e.what());
            }
            catch(...)
            {
                throw std::runtime_error(getName()+": unknown exception");
            }

            logger(pxl::LOG_LEVEL_ERROR , "Analysed event is not an pxl::Event !");
            return false;
        }

        void shutdown() throw(std::runtime_error)
        {
            for (auto itProcess: _splittingInfo)
            {
                double desiredPercentage = 1.0;
                for (auto itPercentage: _splitPercentages)
                {
                    if (std::regex_match(itProcess.first,itPercentage.first))
                    {
                        desiredPercentage=itPercentage.second;
                        break;
                    }
                }
                int passedEvents = itProcess.second.total;
                double achievedPercentage = 1.0*itProcess.second.selected/itProcess.second.total;
                
                logger(pxl::LOG_LEVEL_INFO , getName()+" split fraction for '",itProcess.first,"': ",1.0*achievedPercentage, " (desired="+std::to_string(desiredPercentage)+"; ",passedEvents," events processed)");
                if (!_useExistingFlag and desiredPercentage*passedEvents>10 and desiredPercentage>0 and std::fabs(desiredPercentage-achievedPercentage)/achievedPercentage>2.5/std::sqrt(passedEvents))
                {
                    logger(pxl::LOG_LEVEL_ERROR,getName()+" split actual split fraction ("+std::to_string(achievedPercentage)+") too far away from desired one ("+std::to_string(desiredPercentage)+") for process '"+itProcess.first+"' with processed events "+std::to_string(passedEvents));
                }
            }
        }

        void destroy() throw (std::runtime_error)
        {
            delete this;
        }
};

PXL_MODULE_INIT(Splitter)
PXL_PLUGIN_INIT
