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
        pxl::Source* _outputSource;
        pxl::Source* _outputVetoSource;
        
        std::vector<std::string> _percentages;
        std::vector<std::pair<std::regex,double>> _splits;
        
        bool _random;
        
        std::string _processNameField;
        
        unsigned int _passedEvents;
        unsigned int _selectedEvents;
        
        std::string _splitName;
        
        std::random_device _randomDevice;
        std::mt19937 _generator;
        std::uniform_real_distribution<> _uniformDist;
        
        std::unordered_map<std::string,std::pair<int,int>> _splittingInfo;
        
    public:
        Splitter():
            Module(),
            _percentages({"[A-Za-z0-9_\\-]+=0.7"}),
            _random(false),
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
            
            addOption("percentages","percentage of events to select",_percentages);
            addOption("random","select events randomly",_random);
            
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
        
            getOption("percentages",_percentages);
            
            for (auto it: _percentages)
            {
                int pos = it.find("=");
                if (pos ==std::string::npos)
                {
                    throw std::runtime_error("Splitter percentage not found in '"+it+"'");
                }
                double percentage = std::atof(it.substr(pos+1).c_str());
                std::regex regex(it.substr(0,pos));
                _splits.emplace_back(regex,percentage);
            }
            
            getOption("random",_random);
            
            getOption("split name",_splitName);
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                
                const std::string processName = event->getUserRecord(_processNameField);
                if (_splittingInfo.find(processName)==_splittingInfo.end())
                {
                    _splittingInfo[processName] = std::make_pair<int,int>(0,0);
                }
                _splittingInfo[processName].first+=1;
                
                bool selected = false;
                double percentage = -1.0;
                
                for (auto it: _splits)
                {
                    if (std::regex_match(processName,it.first))
                    {
                        percentage=it.second;
                        break;
                    }
                }
                if (percentage<0)
                {
                    throw std::runtime_error("Cannot find splitting percentage for process '"+processName+"'");
                }
                
                if (_random)
                {
                    selected = _uniformDist(_generator)<percentage;
                }
                
                else
                {
                    
                    double fraction = 1.0*_splittingInfo[processName].second/_splittingInfo[processName].first;
                    selected = fraction<percentage;
                }
                
                if (selected)
                {
                    event->setUserRecord(_splitName,true);
                    event->setUserRecord(_splitName+"_frac",percentage);
                    _splittingInfo[processName].second+=1;
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
            for (auto it: _splittingInfo)
            {
                logger(pxl::LOG_LEVEL_INFO , "Split fraction for '",it.first,"': ",it.second.second/it.second.first, " (",it.second.first," events passed)");
            }
        }

        void destroy() throw (std::runtime_error)
        {
            delete this;
        }
};

PXL_MODULE_INIT(Splitter)
PXL_PLUGIN_INIT
