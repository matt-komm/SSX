#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include "NeutrinoPzSolver.hpp"
#include "angles.h"

#include <iostream>

static pxl::Logger logger("NeutrinoPz");

class NeutrinoPz:
    public pxl::Module
{
    private:
        pxl::Source* _output;
        pxl::Source* _noLepton;

        std::string _inputEventViewName;
        std::string _metName;
        std::string _leptonName;
        
        std::string _outputEventViewName;
        std::string _neutrinoName;
    

    public:
        NeutrinoPz() :
            Module(),
            _inputEventViewName("Reconstructed"),
            _metName("MET"),
            _leptonName("TightLepton"),
            
            _outputEventViewName("SingleTop"),
            _neutrinoName("Neutrino")

        {
            addSink("input", "Input");
            _noLepton = addSource("noLepton", "noLepton");
            _output = addSource("output", "output");

            addOption("input event view","name of the event view",_inputEventViewName);
            addOption("met name","name of the MET",_metName);
            addOption("lepton name","name of the lepton",_leptonName);
            
            addOption("output event view","name of the neutrino",_outputEventViewName);
            addOption("neutrino name","name of the neutrino",_neutrinoName);

        }

        ~NeutrinoPz()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("NeutrinoPz");
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
            getOption("input event view",_inputEventViewName);
            getOption("met name",_metName);
            getOption("lepton name",_leptonName);
            
            getOption("output event view",_outputEventViewName);
            getOption("neutrino name",_neutrinoName);
        }

        void endJob()
        {
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
                    
                    pxl::EventView* outputEventView = nullptr;
                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        if (eventViews[ieventView]->getName()==_outputEventViewName)
                        {
                            outputEventView=eventViews[ieventView];
                            break;
                        }
                    }
                    if (!outputEventView)
                    {
                        outputEventView = event->create<pxl::EventView>();
                        outputEventView->setName(_outputEventViewName);
                    }
                    
                    for (unsigned ieventView=0; ieventView<eventViews.size();++ieventView)
                    {
                        pxl::EventView* eventView = eventViews[ieventView];
                        if (eventView->getName()==_inputEventViewName)
                        {
                            std::vector<pxl::Particle*> particles;
                            eventView->getObjectsOfType(particles);
                            pxl::Particle* met=nullptr;
                            pxl::Particle* lepton=nullptr;
                            pxl::Particle* neutrino=nullptr;
                            for (unsigned iparticle=0; iparticle<particles.size();++iparticle)
                            {
                                pxl::Particle* particle = particles[iparticle];
                                if (!met &&(particle->getName()==_metName))
                                {
                                    met=particle;
                                }
                                if (!lepton &&(particle->getName()==_leptonName))
                                {
                                    lepton=particle;
                                }
                            }
                            if (met!=nullptr && lepton!=nullptr)
                            {
                                neutrino=outputEventView->create<pxl::Particle>();
                                neutrino->setName(_neutrinoName);
                                //our code
                                //solveNu4Momentum(neutrino,lepton->getVector(),met->getPx(),met->getPy());
                                //from Hamed - possible difference is in treating the complex solution cases
                                std::pair<math::XYZTLorentzVector,math::XYZTLorentzVector> nuVecs = NuMomentum(lepton->getPx(), lepton->getPy(), lepton->getPz(), lepton->getPt(), lepton->getE(), met->getPx(),met->getPy() );
                                //std::cout<<neutrino->getPt()-nuVec.Pt()<<std::endl;
                                neutrino->setP4(nuVecs.first.Px(),nuVecs.first.Py(),nuVecs.first.Pz(),nuVecs.first.E());

                                const double mtw_beforePz = calculateMTW(lepton,met);
                                
                                outputEventView->setUserRecord("mtw_beforePz",mtw_beforePz);
                                neutrino->setUserRecord("pz1",nuVecs.first.Pz());
                                neutrino->setUserRecord("pz2",nuVecs.second.Pz());
                                neutrino->setUserRecord("dpz",fabs(nuVecs.first.Pz()-nuVecs.second.Pz()));
                                
                            }
                            if (!met)
                            {
                                throw std::runtime_error("no MET with name '"+_metName+"' found!");
                            }
                            if (!lepton)
                            {
                                _noLepton->setTargets(event);
                                return _noLepton->processTargets();
                            }
                            if (met and lepton and !neutrino)
                            {
                                throw std::runtime_error("no neutrino reconstructed!");
                            }
                        }
                    }

                    _output->setTargets(event);
                    return _output->processTargets();
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

PXL_MODULE_INIT(NeutrinoPz)
PXL_PLUGIN_INIT

