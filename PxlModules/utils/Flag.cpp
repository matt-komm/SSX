#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>

static pxl::Logger logger("Flag");

class Flag:
    public pxl::Module
{
    private:
        pxl::Source* _source;
        std::vector<std::string> _flagNames;
        std::vector<int> _flagStatuses;
        
    public:
        Flag():
            Module()
        {
            addSink("input", "input");
            _source = addSource("out","out");
            
            addOption("flag names","",_flagNames);
            addOption("flag statuses","",std::vector<std::string>());
        }

        ~Flag()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("Flag");
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
            getOption("flag names",_flagNames);
            std::vector<std::string> flagStr;
            getOption("flag statuses",flagStr);
            
            if (_flagNames.size()!=flagStr.size())
            {
                throw std::runtime_error(this->getName()+": Number of flag names != flag statuses");
            }
            for (unsigned int i = 0; flagStr.size(); ++i)
            {
                try
                {
                    _flagStatuses.push_back(std::atoi(flagStr[i].c_str()));
                }
                catch (const std::runtime_error& e)
                {
                    throw std::runtime_error(this->getName()+": Error while parsing flag statuses: "+e.what());
                }
            }
        }
        
        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    for (unsigned int i = 0; i < _flagNames.size(); ++i)
                    {
                        event->setUserRecord(_flagNames[i],_flagStatuses[i]);
                    }
                    
                    _source->setTargets(event);
                    return _source->processTargets();
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
        
        void endJob() throw (std::runtime_error)
        {
        }

        void shutdown() throw(std::runtime_error)
        {
        }

        void destroy() throw (std::runtime_error)
        {
            delete this;
        }
};

PXL_MODULE_INIT(Flag)
PXL_PLUGIN_INIT
