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

static pxl::Logger logger("JetCategory");


class JetCategory:
    public pxl::Module
{
    private:
        pxl::Source* _outputTightSource;
        pxl::Source* _outputMedSource;
        pxl::Source* _outputLooseSource;
        pxl::Source* _outputNoneSource;
        
        std::string _evName;
        
        std::string _tightUR;
        std::string _medUR;
        std::string _looseUR;
        

    public:
        JetCategory():
            Module(),
            _evName("Reconstructed"),
            _tightUR("nSelectedBJetTight"),
            _medUR("nSelectedBJetMed"),
            _looseUR("nSelectedBJetLoose")
            
        {
            addSink("input", "input");
            _outputNoneSource = addSource("none","none");
            _outputTightSource = addSource("tight","tight");
            _outputMedSource = addSource("med","med");
            _outputLooseSource = addSource("loose","loose");
            
            addOption("inputEventView","",_evName);
            
            addOption("tight UR","",_tightUR);
            addOption("med UR","",_medUR);
            addOption("loose UR","",_looseUR);
            
                   
        }

        ~JetCategory()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("JetCategory");
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
            getOption("inputEventView",_evName);
            
            getOption("tight UR",_tightUR);
            getOption("med UR",_medUR);
            getOption("loose UR",_looseUR);
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                
                std::vector<pxl::EventView*> eventViews;
                event->getObjectsOfType(eventViews);
                
                for (pxl::EventView* ev: eventViews)
                {
                    if (ev->getName()==_evName)
                    {
                        long nTight = ev->getUserRecord(_tightUR).toUInt64();
                        long nMed = ev->getUserRecord(_medUR).toUInt64();
                        long nLoose = ev->getUserRecord(_looseUR).toUInt64();
                        
                        if (nTight>0)
                        {
                            _outputTightSource->setTargets(event);
                            return _outputTightSource->processTargets();
                        }
                        else if (nTight==0 and nMed>0)
                        {
                            _outputMedSource->setTargets(event);
                            return _outputMedSource->processTargets();
                        }
                        else if (nTight==0 and nMed==0 and nLoose>0)
                        {
                            _outputLooseSource->setTargets(event);
                            return _outputLooseSource->processTargets();
                        }
                        else if (nTight==0 and nMed==0 and nLoose==0)
                        {
                            _outputNoneSource->setTargets(event);
                            return _outputNoneSource->processTargets();
                        }
                    
                        
                    }
                }
             
                   
                _outputNoneSource->setTargets(event);
                return _outputNoneSource->processTargets();
                
                
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
            
        }

        void destroy() throw (std::runtime_error)
        {
            delete this;
        }
};

PXL_MODULE_INIT(JetCategory)
PXL_PLUGIN_INIT
