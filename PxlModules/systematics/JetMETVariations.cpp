#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <vector>
#include <array>
#include <regex>
#include <unordered_map>

static pxl::Logger logger("JetMETVariations");

class JetMETVariations:
    public pxl::Module
{
    private:
        struct Variation
        {
            std::array<pxl::Source*,2> sources;
            std::array<bool,2> active;
            std::string inputJetName;
            std::string inputMETName;
        };
    
        std::string _eventViewName;
    
        std::string _nominalJetName;
        std::string _nominalMETName;
        
        std::string _renamedJet;
        std::string _renamedMET;
        
        bool _removeOtherVariations;
        
        const std::vector<std::string> _variationNames;
        pxl::Source* _nominalSource;
        std::unordered_map<std::string, Variation> _variations;
        
        std::vector<std::string> _ignoreNames;
        std::vector<std::regex> _ignoreNamesRegex;
        
    public:
        JetMETVariations():
            Module(),
            _eventViewName("Reconstructed"),
            _nominalJetName("Jetsmeared"),
            _nominalMETName("MET"),
            _renamedJet("Jet"),
            _renamedMET("MET"),
            _removeOtherVariations(true),
            _variationNames({"Res","En","Unc"}),
            _ignoreNames({
                "\\S+hdamp\\S+",
                "\\S+herwig\\S+",
                "\\S+mtop\\S+",
                "\\S+scale\\S+",
                "\\S+colourFlip\\S+",
                "\\S+fsr\\S+",
                "\\S+isr\\S+"
            })
        {
            addSink("input", "input");
            
            addOption("event view name", "", _eventViewName);
            
            addOption("nominal jet name","",_nominalJetName);
            addOption("nominal MET name","",_nominalMETName);
            
            addOption("rename jet","",_renamedJet);
            addOption("rename MET","",_renamedMET);
            
            addOption("remove other variations","",_removeOtherVariations);
            
            addOption("ignore processes","",_ignoreNames);

            for (const std::string& name: _variationNames)
            {
                Variation variation;
                variation.sources={addSource(name+"Up",name+"Up"),addSource(name+"Down",name+"Down")};
                
                addOption(name+" jet name","","");
                addOption(name+" met name","","");

                variation.active={true,true};
                
                addOption("variate "+name+"Up","",true);
                addOption("variate "+name+"Down","",true);
                _variations[name]=std::move(variation);
            }
            
            _nominalSource = addSource("nominal","nominal");
            
            
            
        }

        ~JetMETVariations()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("JetMETVariations");
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
            getOption("event view name", _eventViewName);
        
            getOption("nominal jet name",_nominalJetName);
            getOption("nominal MET name",_nominalMETName);
            
            getOption("rename jet",_renamedJet);
            getOption("rename MET",_renamedMET);

            getOption("remove other variations",_removeOtherVariations);
            
            getOption("ignore processes",_ignoreNames);
            
            for (const std::string& s: _ignoreNames)
            {
                _ignoreNamesRegex.emplace_back(s);
            }

            for (auto variation = _variations.begin(); variation!= _variations.end();++variation)
            {
                getOption(variation->first+" jet name",variation->second.inputJetName);
                getOption(variation->first+" met name",variation->second.inputMETName);
                
                getOption("variate "+variation->first+"Up",variation->second.active[0]);
                getOption("variate "+variation->first+"Down",variation->second.active[1]);
            }
        }
        
        
        void renameJetMET(pxl::Event* event, const std::string& jetName, const std::string& metName)
        {
            std::vector<pxl::EventView*> eventViews;
            event->getObjectsOfType(eventViews);
            
            bool metRenamed = false;
            
            
            for (pxl::EventView* eventView: eventViews)
            {
                if (eventView->getName()==_eventViewName)
                {
                    std::vector<pxl::Particle*> particles;
                    eventView->getObjectsOfType(particles);
                    for (pxl::Particle* particle: particles)
                    {
                        if (particle->getName()==jetName)
                        {
                            //std::cout<<"    select Jet: "<<particle->getName()<<std::endl;
                            particle->setName(_renamedJet);
                        }
                        else if (particle->getName()==metName)
                        {
                            particle->setName(_renamedMET);
                            if (metRenamed)
                            {
                                throw std::runtime_error("Multiple MET objects found of name '"+metName+"'");
                            }
                            metRenamed=true;
                            //std::cout<<"    select MET: "<<particle->getName()<<std::endl;
                        }
                        
                        //remove particle if it begins with _renamedJet or _renamedMET
                        else if (_removeOtherVariations and std::equal(_renamedJet.begin(),_renamedJet.end(),particle->getName().begin()))
                        {
                            //std::cout<<"    delete: "<<particle->getName()<<std::endl;
                            eventView->removeObject(particle);
                        }
                        else if (_removeOtherVariations and std::equal(_renamedMET.begin(),_renamedMET.end(),particle->getName().begin()))
                        {
                            //std::cout<<"    delete: "<<particle->getName()<<std::endl;
                            eventView->removeObject(particle);
                        }
                        else
                        {
                            //std::cout<<"    keep: "<<particle->getName()<<" (!="<<_renamedMET<<"||"<<_renamedJet<<")"<<std::endl;
                        }
                        
                    }
                    
                    if (not metRenamed)
                    {
                        throw std::runtime_error("No MET object found of name '"+metName+"'");
                    }
                    
                }
            }
        }
        
        bool isIgnored(const pxl::Event* event) const
        {
            bool ignore = false;
            const std::string processName = event->getUserRecord("ProcessName").toString();
            for (auto it = _ignoreNamesRegex.cbegin(); it!=_ignoreNamesRegex.cend() and !ignore; ++it)
            {
                ignore = ignore || std::regex_match(processName,*it);
            }
            return ignore;
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    //std::cout<<"new event"<<std::endl;
                    bool success = true;
                    if (not event->getUserRecord("isRealData").toBool())
                    {
                        if (not isIgnored(event))
                        {
                            for (auto variation = _variations.begin(); variation!= _variations.end();++variation)
                            {
                                if (variation->second.active[0])
                                {
                                    //std::cout<<"  produce "<<variation->first<<"Up"<<std::endl;
                                    pxl::Event* eventShiftedUp = dynamic_cast<pxl::Event*>(event->clone());
                                    if (not eventShiftedUp)
                                    {
                                        throw std::runtime_error("cloning of Event failed");
                                    }
                                    eventShiftedUp->setUserRecord("ProcessName",eventShiftedUp->getUserRecord("ProcessName").toString()+"_"+variation->first+"Up");
                                    std::string jetName = variation->second.inputJetName+"Up";
                                    if (variation->second.inputJetName=="")
                                    {
                                        jetName=_nominalJetName;
                                    }
                                    std::string metName = variation->second.inputMETName+"Up";
                                    if (variation->second.inputMETName=="")
                                    {
                                        metName=_nominalMETName;
                                    }
                                    renameJetMET(eventShiftedUp,jetName,metName);
                                    variation->second.sources[0]->setTargets(eventShiftedUp);
                                    success &= variation->second.sources[0]->processTargets();
                                    delete eventShiftedUp;
                                }
                                if (variation->second.active[1])
                                {
                                    //std::cout<<"  produce "<<variation->first<<"Down"<<std::endl;
                                    pxl::Event* eventShiftedDown = dynamic_cast<pxl::Event*>(event->clone());
                                    if (not eventShiftedDown)
                                    {
                                        throw std::runtime_error("cloning of Event failed");
                                    }
                                    eventShiftedDown->setUserRecord("ProcessName",eventShiftedDown->getUserRecord("ProcessName").toString()+"_"+variation->first+"Down");
                                    std::string jetName = variation->second.inputJetName+"Down";
                                    if (variation->second.inputJetName=="")
                                    {
                                        jetName=_nominalJetName;
                                    }
                                    std::string metName = variation->second.inputMETName+"Down";
                                    if (variation->second.inputMETName=="")
                                    {
                                        metName=_nominalMETName;
                                    }
                                    renameJetMET(eventShiftedDown,jetName,metName);
                                    variation->second.sources[1]->setTargets(eventShiftedDown);
                                    success &= variation->second.sources[1]->processTargets();
                                    delete eventShiftedDown;
                                }
                            }
                        }
                        //std::cout<<"  produce "<<"Nominal"<<std::endl;
                        renameJetMET(event,_nominalJetName,_nominalMETName);
                    }
                    _nominalSource->setTargets(event);
                    success &= _nominalSource->processTargets();
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


PXL_MODULE_INIT(JetMETVariations)
PXL_PLUGIN_INIT
