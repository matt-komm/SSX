#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <random>
#include <unordered_map>

static pxl::Logger logger("Splitter");


class Splitter:
    public pxl::Module
{
    private:
        pxl::Source* _outputSource;
        pxl::Source* _outputVetoSource;
        
        double _percentage;
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
            _percentage(0.5),
            _random(true),
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
            
            addOption("percentage","percentage of events to select",_percentage);
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
        
            getOption("percentage",_percentage);
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
                
                if (_random)
                {
                    selected = _uniformDist(_generator)<_percentage;
                }
                
                else
                {
                    double fraction = 1.0*_splittingInfo[processName].second/_splittingInfo[processName].first;
                    selected = fraction<_percentage;
                }
                
                if (selected)
                {
                    event->setUserRecord(_splitName,true);
                    _splittingInfo[processName].second+=1;
                    _outputSource->setTargets(event);
                    return _outputSource->processTargets();
                }
                else
                {
                    event->setUserRecord(_splitName,false);
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
