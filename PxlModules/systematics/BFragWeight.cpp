#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <cmath>

static pxl::Logger logger("BFragWeight");

class BFragWeight:
    public pxl::Module
{
    private:
        pxl::Source* _outputSource;

        std::string _inputJetName;
        std::string _inputEventViewName;
        


    public:
        BFragWeight():
            Module(),
            _inputJetName("Jet"),
            _inputEventViewName("PTR")
        {
            addSink("input", "input");
            
            _outputSource = addSource("output","output");

            addOption("event view","name of the event view where jets are selected",_inputEventViewName);
            addOption("input jet name","name of particles to consider for selection",_inputJetName);
        }

        ~BFragWeight()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("BFragWeight");
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
            getOption("event view",_inputEventViewName);
            getOption("input jet name",_inputJetName);
        }
        
        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    std::vector<pxl::EventView*> eventViews;
                    event->getObjectsOfType(eventViews);
                    
                    std::vector<pxl::Particle*> selectedJets;
                    
                    std::vector<pxl::Particle*> dRCleaningObjects;
                    
                    pxl::EventView* inputEventView = nullptr;
                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {

                        pxl::EventView* eventView = eventViews[ieventView];
                        if (eventView->getName()==_inputEventViewName)
                        {
                            inputEventView=eventView;
                            std::vector<pxl::Particle*> particles;
                            eventView->getObjectsOfType(particles);

                            float upFrag = 1.;
                            float centralFrag = 1.;
                            float downFrag = 1.;
                            float PetersonFrag = 1.;
                            float semilepbrUp = 1.;
                            float semilepbrDown = 1.;
                            
                            for (unsigned iparticle=0; iparticle<particles.size();++iparticle)
                            {
                                pxl::Particle* particle = particles[iparticle];

                                if (particle->getName()==_inputJetName)
                                {
                                    if (particle->hasUserRecord("upFrag")) upFrag *=particle->getUserRecord("upFrag").toFloat();
                                    if (particle->hasUserRecord("centralFrag")) centralFrag *=particle->getUserRecord("centralFrag").toFloat();
                                    if (particle->hasUserRecord("downFrag")) downFrag *=particle->getUserRecord("downFrag").toFloat();
                                    if (particle->hasUserRecord("PetersonFrag")) PetersonFrag *=particle->getUserRecord("PetersonFrag").toFloat();
                                    if (particle->hasUserRecord("semilepbrUp")) semilepbrUp *=particle->getUserRecord("semilepbrUp").toFloat();
                                    if (particle->hasUserRecord("semilepbrDown")) semilepbrDown *=particle->getUserRecord("semilepbrDown").toFloat();
                                }
                            }
                            
                            inputEventView->setUserRecord("upFrag",upFrag);
                            inputEventView->setUserRecord("centralFrag",centralFrag);
                            inputEventView->setUserRecord("downFrag",downFrag);
                            inputEventView->setUserRecord("PetersonFrag",PetersonFrag);
                            inputEventView->setUserRecord("semilepbrUp",semilepbrUp);
                            inputEventView->setUserRecord("semilepbrDown",semilepbrDown);
                        }
                    }
                    
                    
                    _outputSource->setTargets(event);
                    return _outputSource->processTargets();
                    
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

PXL_MODULE_INIT(BFragWeight)
PXL_PLUGIN_INIT
