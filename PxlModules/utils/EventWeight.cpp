#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <unordered_map>

static pxl::Logger logger("EventWeight");

struct FileInfo
{
    double nEvents;
    double crossSection;
};

const std::unordered_map<std::string,FileInfo> eventWeights80XwithHLT = {
    {"DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=38714374.0 eff=38714374.0 - 0.0 = 38714374.0
            38714374.0,
            725.0 // xsec for process 'DY1JetsToLL_M-10to50'
        }
    },
    {"DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=60515174.0 eff=60515174.0 - 0.0 = 60515174.0
            60515174.0,
            1016.0 // xsec for process 'DY1JetsToLL_M-50'
        }
    },
    {"DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=18854127.0 eff=18854127.0 - 0.0 = 18854127.0
            18854127.0,
            394.5 // xsec for process 'DY2JetsToLL_M-10to50'
        }
    },
    {"DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=19343351.0 eff=19343351.0 - 0.0 = 19343351.0
            19343351.0,
            331.0 // xsec for process 'DY2JetsToLL_M-50'
        }
    },
    {"DY3JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=4836197.0 eff=4836197.0 - 0.0 = 4836197.0
            4836197.0,
            96.47 // xsec for process 'DY3JetsToLL_M-10to50'
        }
    },
    {"DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=5567223.0 eff=5567223.0 - 0.0 = 5567223.0
            5567223.0,
            96.0 // xsec for process 'DY3JetsToLL_M-50'
        }
    },
    {"DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=4069868.0 eff=4069868.0 - 0.0 = 4069868.0
            4069868.0,
            51.0 // xsec for process 'DY4JetsToLL_M-50'
        }
    },
    {"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=34067778.0 eff=34067778.0 - 0.0 = 34067778.0
            34067778.0,
            18610.0 // xsec for process 'DYJetsToLL_M-10to50'
        }
    },
    {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",
        {
            //total=48120274.0 eff=48120274.0 - 0.0 = 48120274.0
            48120274.0,
            4895.0 // xsec for process 'DYJetsToLL_M-50'
        }
    },
    {"QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=3425846.0 eff=3425846.0 - 0.0 = 3425846.0
            3425846.0,
            1.6212392 // xsec for process 'QCD_Pt-1000toInf_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=11349340.0 eff=11349340.0 - 0.0 = 11349340.0
            11349340.0,
            25190.51514 // xsec for process 'QCD_Pt-120to170_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=4038851.0 eff=4038851.0 - 0.0 = 4038851.0
            4038851.0,
            3819570.0 // xsec for process 'QCD_Pt-15to20_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=18788577.0 eff=18788577.0 - 0.0 = 18788577.0
            18788577.0,
            8654.49315 // xsec for process 'QCD_Pt-170to300_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=30822357.0 eff=30822357.0 - 0.0 = 30822357.0
            30822357.0,
            24016704000 // xsec for process 'QCD_Pt-20to30_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        {
            //total=23875908.0 eff=23875908.0 - 0.0 = 23875908.0
            23875908.0,
            797.35269 // xsec for process 'QCD_Pt-300to470_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=28612006.0 eff=28612006.0 - 0.0 = 28612006.0
            28612006.0,
            1652471.46 // xsec for process 'QCD_Pt-30to50_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        {
            //total=9514864.0 eff=9514864.0 - 0.0 = 9514864.0
            9514864.0,
            79.02211 // xsec for process 'QCD_Pt-470to600_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=19397315.0 eff=19397315.0 - 0.0 = 19397315.0
            19397315.0,
            437504.1 // xsec for process 'QCD_Pt-50to80_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=8866800.0 eff=8866800.0 - 0.0 = 8866800.0
            8866800.0,
            25.0951932 // xsec for process 'QCD_Pt-600to800_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        {
            //total=9633349.0 eff=9633349.0 - 0.0 = 9633349.0
            9633349.0,
            4.707572 // xsec for process 'QCD_Pt-800to1000_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        {
            //total=9310844.0 eff=9310844.0 - 0.0 = 9310844.0
            9310844.0,
            106033.6648 // xsec for process 'QCD_Pt-80to120_MuEnrichedPt5'
        }
    },
    {"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        {
            //total=37070217.0 eff=37070217.0 - 0.0 = 37070217.0
            37070217.0,
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        }
    },
    {"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        {
            //total=64156008.0 eff=64156008.0 - 0.0 = 64156008.0
            64156008.0,
            136.02 // xsec for process 'ST_t-channel_top_4f'
        }
    },
    {"ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_ext",
        {
            //total=3179607.0 eff=3179607.0 - 0.0 = 3179607.0
            3179607.0,
            35.6 // xsec for process 'ST_tW_antitop'
        }
    },
    {"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        {
            //total=6625894.0 eff=6625894.0 - 0.0 = 6625894.0
            6625894.0,
            35.6 // xsec for process 'ST_tW_antitop'
        }
    },
    {"ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_ext",
        {
            //total=3179850.0 eff=3179850.0 - 0.0 = 3179850.0
            3179850.0,
            35.6 // xsec for process 'ST_tW_top'
        }
    },
    {"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        {
            //total=6607230.0 eff=6607230.0 - 0.0 = 6607230.0
            6607230.0,
            35.6 // xsec for process 'ST_tW_top'
        }
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
        {
            //total=75130141.0 eff=75130141.0 - 0.0 = 75130141.0
            75130141.0,
            831.76 // xsec for process 'TT'
        }
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        {
            //total=22785775.0 eff=19190819.0 - 3594956.0 = 15595863.0
            15595863.0,
            61526.7 // xsec for process 'WJetsToLNu'
        }
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",
        {
            //total=55656458.0 eff=55656458.0 - 0.0 = 55656458.0
            55656458.0,
            61526.7 // xsec for process 'WJetsToLNu'
        }
    },
    {"WToLNu_0J_13TeV-amcatnloFXFX-pythia8_ext",
        {
            //total=47746995.0 eff=43277564.0 - 4469431.0 = 38808133.0
            38808133.0,
            49670.0 // xsec for process 'WToLNu_0J_13TeV'
        }
    },
    {"WToLNu_1J_13TeV-amcatnloFXFX-pythia8",
        {
            //total=39434342.0 eff=28943204.0 - 10491138.0 = 18452066.0
            18452066.0,
            8264.0 // xsec for process 'WToLNu_1J_13TeV'
        }
    },
    {"WToLNu_2J_13TeV-amcatnloFXFX-pythia8_ext",
        {
            //total=49993843.0 eff=32315774.0 - 17678069.0 = 14637705.0
            14637705.0,
            2544.0 // xsec for process 'WToLNu_2J_13TeV'
        }
    }
};

const std::unordered_map<std::string,const std::unordered_map<std::string,FileInfo>> _eventWeightsPerEra =
{
    {"80XwithHLT",eventWeights80XwithHLT}
};

class EventWeight:
    public pxl::Module
{
    private:
        pxl::Source* _outputSource;
        std::string _processNameField;

        std::vector<std::string> _allowedPostfixes;
        
        std::vector<std::string> _processNameList;
        
        std::string _eraName;

    public:
    
        EventWeight():
            Module(),
            _processNameField("ProcessName"),
            _allowedPostfixes({"","_iso","_midiso","_antiiso"}),
            _eraName("80XwithHLT")
        {
            addSink("input", "input");
            _outputSource = addSource("output","output");
            
            addOption("name of process field","",_processNameField);
            
            addOption("EraName","",_eraName);
        }

        ~EventWeight()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("EventWeight");
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
            getOption("name of process field",_processNameField);
            getOption("EraName",_eraName);
            
            if (_eventWeightsPerEra.find(_eraName)==_eventWeightsPerEra.cend())
            {
                throw std::runtime_error("Event weight era not found: "+_eraName);
            }
            logger(pxl::LOG_LEVEL_INFO , "Event weights taken from '"+_eraName+"'");
            
            for (auto it = _eventWeightsPerEra.at(_eraName).cbegin(); it != _eventWeightsPerEra.at(_eraName).cend(); ++it)
            {
                _processNameList.push_back(it->first);
            }
            
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    
                    std::string processName = event->getUserRecord(_processNameField).toString();
                    std::string strippedProcessName = "";
                    for (std::string& possibleName: _processNameList)
                    {
                        //need to find the largest match here for the 'ext' samples
                        if ((possibleName.size()>strippedProcessName.size()) and std::equal(possibleName.begin(),possibleName.end(),processName.begin()))
                        {
                            strippedProcessName = possibleName;
                        }
                    }

                    if (strippedProcessName.size()>0)
                    {
	                    auto it = _eventWeightsPerEra.at(_eraName).find(strippedProcessName);
                        if (it!=_eventWeightsPerEra.at(_eraName).end())
                        {
	                        event->setUserRecord("mc_weight",1.0*it->second.crossSection/it->second.nEvents);
                        }
                    }
                    if (strippedProcessName.size()==0)
                    {
                        throw std::runtime_error("no event weight information available for process name '"+processName+"'");
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

PXL_MODULE_INIT(EventWeight)
PXL_PLUGIN_INIT
