#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>

static pxl::Logger logger("Duplicator");

class Duplicator:
    public pxl::Module
{
    private:
        pxl::Source* _source1;
        pxl::Source* _source2;
        
    public:
        Duplicator():
            Module()
        {
            addSink("input", "input");
            _source1 = addSource("out1","out1");
            _source2 = addSource("out2","out2");
        }

        ~Duplicator()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("Duplicator");
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
        }
        
        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    pxl::Event* eventClone = dynamic_cast<pxl::Event*>(event->clone());
                    _source1->setTargets(event);
                    bool success = _source1->processTargets();
                    _source2->setTargets(eventClone);
                    success &= _source2->processTargets();
                    
                    delete eventClone;
                    return success;
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

PXL_MODULE_INIT(Duplicator)
PXL_PLUGIN_INIT
