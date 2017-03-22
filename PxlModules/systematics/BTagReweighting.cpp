#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include "BTagWeightCalculator.hpp"
#include "BTagCalibrationStandalone.hpp"

#include <string>
#include <unordered_map>
#include <memory>

#include "TFile.h"
#include "TH2F.h"


static pxl::Logger logger("BTagReweighting");

class BTagReweighting:
    public pxl::Module
{
    private:
        pxl::Source* _outputSource;
        
        BTagCalibration _btagCalib;
        
        std::vector<BTagCalibrationReader> _readerNominal_ttbar;
        std::vector<BTagCalibrationReader> _readerUp_ttbar;
        std::vector<BTagCalibrationReader> _readerDown_ttbar;
        
        std::vector<BTagCalibrationReader> _readerNominal_inc;
        std::vector<BTagCalibrationReader> _readerUp_inc;
        std::vector<BTagCalibrationReader> _readerDown_inc;
        
        std::vector<std::shared_ptr<TH2F>> mcEff_b;
        std::vector<std::shared_ptr<TH2F>> mcEff_c;
        std::vector<std::shared_ptr<TH2F>> mcEff_q;
        std::vector<std::shared_ptr<TH2F>> mcEff_other;
            
        BWGHT::BTagWeightCalculator _btagWeightCalc;
        
        constexpr static float MaxBJetPt = 670.0;
        constexpr static float MaxLJetPt = 1000.0;
        
        std::string _bTaggingAlgorithmName;
        
        std::string _sfFile;
        std::string _mcFile;
        std::vector<std::string> _histPostFix;
        std::string _eventViewName;
        std::vector<std::string> _jetNames;
        
        std::vector<double> _wp;

    public:
        BTagReweighting():
            Module(),               
            _bTaggingAlgorithmName("pfCombinedMVAV2BJetTags"),
            _eventViewName("Reconstructed"),
            _histPostFix({"loose","medium","tight"}),
            _jetNames({"SelectedJet"}),
            _wp({-0.5884,0.4432,0.9432})
        {
            addSink("input", "input");
            _outputSource = addSource("output","output");
            
            addOption("b tagging algorithm","",_bTaggingAlgorithmName);
            
            addOption("SF csv file","",_sfFile,pxl::OptionDescription::USAGE_FILE_OPEN);
            addOption("MC efficiency file","",_mcFile,pxl::OptionDescription::USAGE_FILE_OPEN);
            addOption("MC hist postfix","",_histPostFix);
            addOption("event view name","",_eventViewName);
            addOption("jet names","",_jetNames);
            
            std::vector<std::string> wp2str;
            for (double wp: _wp) wp2str.push_back(std::to_string(wp));
            addOption("workingpoint","",wp2str);
            
            
        }

        ~BTagReweighting()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("BTagReweighting");
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
            /*
            using namespace BWGHT;
            BTagWeightCalculator calc;
            WorkingPoint testWP(0.2);
            testWP.setEfficiencyFunction(new ConstEfficiencyFunction(0.7));
            testWP.setScaleFactorFunction(new ConstScaleFactorFunction(1.0));
            //calc.addWorkingPoint(testWP);
            WorkingPoint testWP2(0.6);
            testWP2.setEfficiencyFunction(new ConstEfficiencyFunction(0.5));
            testWP2.setScaleFactorFunction(new ConstScaleFactorFunction(1.5));
            calc.addWorkingPoint(testWP2);
            calc.getEventWeight({Jet(0.1),Jet(0.7),Jet(0.5)});
            */
            getOption("b tagging algorithm",_bTaggingAlgorithmName);
            
            getOption("SF csv file",_sfFile);
            getOption("MC efficiency file",_mcFile);
            getOption("MC hist postfix",_histPostFix);
            getOption("event view name",_eventViewName);
            getOption("jet names",_jetNames);
            
            
            _sfFile = getAnalysis()->findFile(_sfFile);
            _mcFile = getAnalysis()->findFile(_mcFile);
            
            std::vector<std::string> wp2str;
            _wp.clear();
            getOption("workingpoint",wp2str);
            for (const std::string& wp: wp2str) _wp.push_back(std::atof(wp.c_str()));
            
            
            
            _btagCalib = BTagCalibration("csvv1", _sfFile);
            
            std::vector<BTagEntry::OperatingPoint> opPoints({BTagEntry::OP_LOOSE,BTagEntry::OP_MEDIUM,BTagEntry::OP_TIGHT});
            
            for (unsigned int iwp = 0; iwp<3; ++iwp)
            {
                TFile mcEffFile(_mcFile.c_str());
                TH2F* hist_b = dynamic_cast<TH2F*>(mcEffFile.Get((std::string("b__")+_histPostFix[iwp]).c_str()));
                if (!hist_b)
                {
                    throw std::runtime_error("Cannot find histogram '"+(std::string("b__")+_histPostFix[iwp])+"' in file '"+_mcFile+"'");
                }
                hist_b->SetDirectory(0);
                mcEff_b.emplace_back(hist_b);
                
                TH2F* hist_c = dynamic_cast<TH2F*>(mcEffFile.Get((std::string("c__")+_histPostFix[iwp]).c_str()));
                if (!hist_c)
                {
                    throw std::runtime_error("Cannot find histogram '"+(std::string("c__")+_histPostFix[iwp])+"' in file '"+_mcFile+"'");
                }
                hist_c->SetDirectory(0);
                mcEff_c.emplace_back(hist_c);
                
                TH2F* hist_other = dynamic_cast<TH2F*>(mcEffFile.Get((std::string("other__")+_histPostFix[iwp]).c_str()));
                if (!hist_other)
                {
                    throw std::runtime_error("Cannot find histogram '"+(std::string("other__")+_histPostFix[iwp])+"' in file '"+_mcFile+"'");
                }
                hist_other->SetDirectory(0);
                mcEff_other.emplace_back(hist_other);
                
                mcEffFile.Close();

                
                _readerNominal_ttbar.push_back(BTagCalibrationReader(
                    &_btagCalib,               // calibration instance
                    opPoints[iwp],  // operating point
                    "ttbar",               // measurement type
                    "central"             // systematics type
                ));           
                _readerUp_ttbar.push_back(BTagCalibrationReader(&_btagCalib, opPoints[iwp], "ttbar", "up"));  // sys up
                _readerDown_ttbar.push_back(BTagCalibrationReader(&_btagCalib, opPoints[iwp], "ttbar", "down"));  // sys down
                            
                _readerNominal_inc.push_back(BTagCalibrationReader(
                    &_btagCalib,               // calibration instance
                    opPoints[iwp],  // operating point
                    "incl",               // measurement type
                    "central"             // systematics type
                ));           
                _readerUp_inc.push_back(BTagCalibrationReader(&_btagCalib, opPoints[iwp], "incl", "up"));  // sys up
                _readerDown_inc.push_back(BTagCalibrationReader(&_btagCalib, opPoints[iwp], "incl", "down"));  // sys down
       
                            
                            
                BWGHT::WorkingPoint tightWP(_wp[iwp]);
                
                tightWP.setEfficiencyFunction(new BWGHT::LambdaEfficiencyFunction([this,iwp](const BWGHT::Jet& jet, BWGHT::SYS::TYPE sys) -> double
                {
                    float pt = jet.pt; 
                    float eta = fabs(jet.eta);
                    
                    double efficiency =0.0;
                    
                    if (jet.flavor==5)
                    {
                        int etaBin = mcEff_b[iwp]->GetXaxis()->FindBin(eta);
                        int ptBin = mcEff_b[iwp]->GetYaxis()->FindBin(pt);
                        efficiency = mcEff_b[iwp]->GetBinContent(etaBin,ptBin);
                    }
                    else if (jet.flavor==4)
                    {
                        int etaBin = mcEff_c[iwp]->GetXaxis()->FindBin(eta);
                        int ptBin = mcEff_c[iwp]->GetYaxis()->FindBin(pt);
                        efficiency = mcEff_c[iwp]->GetBinContent(etaBin,ptBin);
                    }
                    else
                    {
                        int etaBin = mcEff_other[iwp]->GetXaxis()->FindBin(eta);
                        int ptBin = mcEff_other[iwp]->GetYaxis()->FindBin(pt);
                        efficiency = mcEff_other[iwp]->GetBinContent(etaBin,ptBin);
                    }
                    if (efficiency<0.01)
                    {
                        efficiency+=0.01/std::pow(1.5,iwp); //make eff less for tighter wps
                    }
                    return efficiency;
                
                }));
                
                tightWP.setScaleFactorFunction(new BWGHT::LambdaScaleFactorFunction([this,iwp](const BWGHT::Jet& jet, BWGHT::SYS::TYPE sys) -> double
                {
                    
                    float pt = jet.pt; 
                    float eta = jet.eta;
                    bool doubleUncertainty = false;
                    
                    BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
                    double jet_scalefactor =  1.0;
                    double jet_scalefactor_up =  1.0;
                    double jet_scalefactor_down = 1.0;
                    
                    if (jet.flavor==5)
                    {
                        flavor = BTagEntry::FLAV_B;
                        if (pt>MaxBJetPt)  
                        {
                            pt = MaxBJetPt; 
                            doubleUncertainty = true;
                        }
                        jet_scalefactor = _readerNominal_ttbar[iwp].eval(flavor, eta, pt); 
                        jet_scalefactor_up = _readerUp_ttbar[iwp].eval(flavor, eta, pt); 
                        jet_scalefactor_down = _readerDown_ttbar[iwp].eval(flavor, eta, pt);   
                    } 
                    else if (jet.flavor==4)
                    {
                        flavor = BTagEntry::FLAV_C;
                        if (pt>MaxBJetPt)  
                        {
                            pt = MaxBJetPt; 
                            doubleUncertainty = true;
                        }
                        jet_scalefactor = _readerNominal_ttbar[iwp].eval(flavor, eta, pt); 
                        jet_scalefactor_up = _readerUp_ttbar[iwp].eval(flavor, eta, pt); 
                        jet_scalefactor_down = _readerDown_ttbar[iwp].eval(flavor, eta, pt); 
                    } 
                    else
                    {
                        flavor = BTagEntry::FLAV_UDSG;
                        if (pt>MaxLJetPt)  
                        {
                            pt = MaxLJetPt; 
                            doubleUncertainty = true;
                        }
                        jet_scalefactor = _readerNominal_inc[iwp].eval(flavor, eta, pt); 
                        jet_scalefactor_up = _readerUp_inc[iwp].eval(flavor, eta, pt); 
                        jet_scalefactor_down = _readerDown_inc[iwp].eval(flavor, eta, pt);   
                    }

                    if (doubleUncertainty)
                    {
                        jet_scalefactor_up = 2*(jet_scalefactor_up - jet_scalefactor) + jet_scalefactor; 
                        jet_scalefactor_down = 2*(jet_scalefactor_down - jet_scalefactor) + jet_scalefactor; 
                    }

                    else if (sys== BWGHT::SYS::BC_UP and (flavor==BTagEntry::FLAV_B or flavor==BTagEntry::FLAV_C))
                    {
                        return jet_scalefactor_up;
                    }
                    else if (sys== BWGHT::SYS::BC_DOWN and (flavor==BTagEntry::FLAV_B or flavor==BTagEntry::FLAV_C))
                    {
                        return jet_scalefactor_down;
                    }
                    else if (sys== BWGHT::SYS::L_UP and flavor==BTagEntry::FLAV_UDSG)
                    {
                        return jet_scalefactor_up;
                    }
                    else if (sys== BWGHT::SYS::L_DOWN and flavor==BTagEntry::FLAV_UDSG)
                    {
                        return jet_scalefactor_down;
                    }
                    return jet_scalefactor;
                
                }));
                _btagWeightCalc.addWorkingPoint(tightWP);
            }
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
            
                    for (pxl::EventView* eventView: eventViews)
                    {
                        if (eventView->getName()==_eventViewName)
                        {
                            std::vector<pxl::Particle*> particles;
                            eventView->getObjectsOfType(particles);
                            
                            
                            std::vector<BWGHT::Jet> jets;
                            for (pxl::Particle* particle: particles)
                            {
                                //skip particles outside b-tagging acceptance
                                if (fabs(particle->getEta())>2.4)
                                {
                                    continue;
                                }
                                
                                if (std::find(_jetNames.cbegin(),_jetNames.cend(),particle->getName())!=_jetNames.cend())
                                {
                                    //use parton flavor 0 if no genParton found
                                    jets.emplace_back(
                                        particle->getUserRecord(_bTaggingAlgorithmName).toFloat(),
                                        abs(particle->hasUserRecord("partonFlavour") ? particle->getUserRecord("partonFlavour").toInt32() : 0),
                                        particle->getPt(),particle->getEta()
                                    );
                                }
                            }
                            eventView->setUserRecord("btagging_nominal",_btagWeightCalc.getEventWeight(jets,BWGHT::SYS::NOMINAL));
                            eventView->setUserRecord("btagging_bc_up",_btagWeightCalc.getEventWeight(jets,BWGHT::SYS::BC_UP));
                            eventView->setUserRecord("btagging_bc_down",_btagWeightCalc.getEventWeight(jets,BWGHT::SYS::BC_DOWN));
                            eventView->setUserRecord("btagging_l_up",_btagWeightCalc.getEventWeight(jets,BWGHT::SYS::L_UP));
                            eventView->setUserRecord("btagging_l_down",_btagWeightCalc.getEventWeight(jets,BWGHT::SYS::L_DOWN));
                            
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

PXL_MODULE_INIT(BTagReweighting)
PXL_PLUGIN_INIT
