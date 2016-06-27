#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

static pxl::Logger logger("ElectronSelection");

class ElectronSelection:
    public pxl::Module
{
    private:
        pxl::Source* _outputIsoSource;
        //pxl::Source* _outputAntiIsoSource;
        pxl::Source* _outputOtherSource;
       
        std::string _inputEventViewName; 
        std::string _inputTightElectronName;
        std::string _tightElectronName;
        
        /*Tight Electron Related Criteria*/
        double _pTMinTightElectron;  //Minimum transverse momentum
        double _etaMaxTightElectron; //Maximum pseudorapidity

    public:
        ElectronSelection():
            Module(),
            _inputEventViewName("Reconstructed"),
            _inputTightElectronName("Electron"),
            _tightElectronName("TightElectron"),

            _pTMinTightElectron(35),
            _etaMaxTightElectron(2.5)
        {
            addSink("input", "input");
            _outputIsoSource = addSource("1 iso electron", "iso");
            //_outputAntiIsoSource = addSource("1 anti-iso electron", "anti-iso");
            _outputOtherSource = addSource("other", "other");

            addOption("Event view","name of the event view where electrons are selected",_inputEventViewName);
            addOption("Input electron name","name of particles to consider for selection",_inputTightElectronName);
            addOption("Name of selected tight electrons","",_tightElectronName);

            addOption("TightElectron Minimum pT","",_pTMinTightElectron);
            addOption("TightElectron Maximum eta","",_etaMaxTightElectron);
        }

        ~ElectronSelection()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("ElectronSelection");
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
            getOption("Event view",_inputEventViewName);
            getOption("Input electron name",_inputTightElectronName);
            getOption("Name of selected tight electrons",_tightElectronName);

            getOption("TightElectron Minimum pT",_pTMinTightElectron);
            getOption("TightElectron Maximum eta",_etaMaxTightElectron);
        }

        bool passTightCriteria(pxl::Particle* particle)
        {
            if (not (particle->getPt()>_pTMinTightElectron))
            {
                return false;
            }
            if (not (fabs(particle->getEta())<_etaMaxTightElectron))
            {
                return false;
            }
            if (not particle->getUserRecord("phys14eleIDTight"))
            {
                return false;
            }
            if (fabs(particle->getEta())>1.4442 && fabs(particle->getEta())<1.5660)
            {
                return false;
            }
            if (not particle->getUserRecord("passConversionVeto"))
            {
                return false;
            }
            return true;
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event *> (sink->get());
                if (event)
                {
                    std::vector<pxl::EventView*> eventViews;
                    event->getObjectsOfType(eventViews);
                    
                    std::vector<pxl::Particle*> tightElectrons;

                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        pxl::EventView* eventView = eventViews[ieventView];
                        if (eventView->getName()==_inputEventViewName)
                        {
                            std::vector<pxl::Particle*> particles;
                            eventView->getObjectsOfType(particles);

                            for (unsigned iparticle=0; iparticle<particles.size();++iparticle)
                            {
                                pxl::Particle* particle = particles[iparticle];

                                if (particle->getName()==_inputTightElectronName)
                                {
                                    if (passTightCriteria(particle))
                                    {
                                        tightElectrons.push_back(particle);
                                    }
                                }
                            }
                        }
                    
                        if (tightElectrons.size()==1)
                        {
                            tightElectrons.front()->setName(_tightElectronName);

                            _outputIsoSource->setTargets(event);
                            return _outputIsoSource->processTargets();
                        }
                        else
                        {
                            _outputOtherSource->setTargets(event);
                            return _outputOtherSource->processTargets();
                        }
                    }
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
        }

        void destroy() throw (std::runtime_error)
        {
            delete this;
        }
};

PXL_MODULE_INIT(ElectronSelection)
PXL_PLUGIN_INIT
