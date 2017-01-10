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

const std::unordered_map<std::string,FileInfo> eventWeights80Xv1 = {
    {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        {
            //total=28696958.0 eff=23968195.0 - 4728763.0 = 19239432.0
            19239432,
            1921.8*3 
        }
    },
    {"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        {
            //total=30915886.0 eff=26706311.0 - 4209575.0 = 22496736.0
            22496736,
            18610.0
        }
    },
    {"QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=22093630.0 eff=22093630.0 - 0 = 22093630.0
            22093630.0,
            866600000 * 0.00044
        }
    },
    
    {"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        {
            //total=19825855.0 eff=19825855.0 - 0 = 19825855.0
            19825855.0,
            80.95
        }
    },
    {"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        {
            //total=32243692.0 eff=32243692.0 - 0 = 32243692.0
            32243692.0,
            136.02
        }
    },
    
    {"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        {
            //total=985000.0 eff=985000.0 - 0 = 985000.0
            985000.0,
            35.6 //from MCM
        }
    },
    
    {"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        {
            //total=998400.0 eff=998400.0 - 0 = 998400.0
            998400.0,
            35.6
        }
    },
    
    {"TT_TuneCUETP8M1_13TeV-powheg-pythia8_ext",
        {
            //total=182123200.0 eff=182123200.0 - 0 = 182123200.0
            182123200.0,
            831.76
        }
    },
    
    {"WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        {
            //total=9908534.0 eff=8341457.0 - 1567077.0 = 6774380.0
            6774380.0,
            20508.9*3
        }
    },
    
    {"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=28210360.0 eff=28210360.0 - .0 = 28210360.0
            28210360.0,
            20508.9*3
        }
    }
};
//total= eff= - 0 = 

const std::unordered_map<std::string,FileInfo> eventWeights80XwithHLT = {
    {"DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        {
            //total=15857985.0 eff=12912008.0 - 2945977.0 = 9966031.0
            9966031.0,
            725.0 // xsec for process 'DY1JetsToLL_M-10to50'
        }
    },
    {"DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=36265419.0 eff=36265419.0 - 0.0 = 36265419.0
            36265419.0,
            725.0 // xsec for process 'DY1JetsToLL_M-10to50'
        }
    },
    {"DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        {
            //total=41924360.0 eff=26273281.0 - 15651079.0 = 10622202.0
            10622202.0,
            394.5 // xsec for process 'DY2JetsToLL_M-10to50'
        }
    },
    {"DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=18925170.0 eff=18925170.0 - 0.0 = 18925170.0
            18925170.0,
            394.5 // xsec for process 'DY2JetsToLL_M-10to50'
        }
    },
    {"DY3JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=4885667.0 eff=4885667.0 - 0.0 = 4885667.0
            4885667.0,
            96.47 // xsec for process 'DY3JetsToLL_M-10to50'
        }
    },
    {"DY4JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        {
            //total=2093405.0 eff=2093405.0 - 0.0 = 2093405.0
            2093405.0,
            34.84 // xsec for process 'DY4JetsToLL_M-10to50'
        }
    },
    {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        {
            //total=104113466.0 eff=86986430.0 - 17127036.0 = 69859394.0
            69859394.0,
            4895.0 // xsec for process 'DYJetsToLL_M-50'
        }
    },
    {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",
        {
            //total=91350867.0 eff=91350867.0 - 0.0 = 91350867.0
            91350867.0,
            4895.0 // xsec for process 'DYJetsToLL_M-50'
        }
    },
    {"QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=3884666.0 eff=3884666.0 - 0.0 = 3884666.0
            3884666.0,
            1.6212392 // xsec for process 'QCD_Pt-1000toInf_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=7925929.0 eff=7925929.0 - 0.0 = 7925929.0
            7925929.0,
            25190.51514 // xsec for process 'QCD_Pt-120to170_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=4617630.0 eff=4617630.0 - 0.0 = 4617630.0
            4617630.0,
            3819570.0 // xsec for process 'QCD_Pt-15to20_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        {
            //total=8693138.0 eff=8693138.0 - 0.0 = 8693138.0
            8693138.0,
            8654.49315 // xsec for process 'QCD_Pt-170to300_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=31516731.0 eff=31516731.0 - 0.0 = 31516731.0
            31516731.0,
            24016704000 // xsec for process 'QCD_Pt-20to30_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-20toInf_MuEnrichedPt15_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=22093630.0 eff=22093630.0 - 0.0 = 22093630.0
            22093630.0,
            381304.0 // xsec for process 'QCD_Pt-20toInf_MuEnrichedPt15'
        }
    },
    {"QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        {
            //total=16174442.0 eff=16174442.0 - 0.0 = 16174442.0
            16174442.0,
            797.35269 // xsec for process 'QCD_Pt-300to470_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=28343259.0 eff=28343259.0 - 0.0 = 28343259.0
            28343259.0,
            1652471.46 // xsec for process 'QCD_Pt-30to50_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        {
            //total=5927876.0 eff=5927876.0 - 0.0 = 5927876.0
            5927876.0,
            79.02211 // xsec for process 'QCD_Pt-470to600_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=20383957.0 eff=20383957.0 - 0.0 = 20383957.0
            20383957.0,
            437504.1 // xsec for process 'QCD_Pt-50to80_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        {
            //total=5868022.0 eff=5868022.0 - 0.0 = 5868022.0
            5868022.0,
            25.0951932 // xsec for process 'QCD_Pt-600to800_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        {
            //total=5571419.0 eff=5571419.0 - 0.0 = 5571419.0
            5571419.0,
            4.707572 // xsec for process 'QCD_Pt-800to1000_MuEnrichedPt5'
        }
    },
    {"QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        {
            //total=13856755.0 eff=13856755.0 - 0.0 = 13856755.0
            13856755.0,
            106033.6648 // xsec for process 'QCD_Pt-80to120_MuEnrichedPt5'
        }
    },
    {"ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_ext",
        {
            //total=16713374.0 eff=10155978.0 - 6557396.0 = 3598582.0
            3598582.0,
            70.688826 // xsec for process 'ST_t-channel_4f_leptonDecays'
        }
    },
    {"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        {
            //total=985000.0 eff=985000.0 - 0.0 = 985000.0
            985000.0,
            35.6 // xsec for process 'ST_tW_antitop'
        }
    },
    {"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        {
            //total=998400.0 eff=998400.0 - 0.0 = 998400.0
            998400.0,
            35.6 // xsec for process 'ST_tW_top'
        }
    },
    {"ST_tWll_5f_LO_13TeV-MadGraph-pythia8",
        {
            //total=50000.0 eff=50000.0 - 0.0 = 50000.0
            50000.0,
            7.557569568 // xsec for process 'ST_tWll'
        }
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
        {
            //total=69303446.0 eff=69303446.0 - 0.0 = 69303446.0
            69303446.0,
            831.76 // xsec for process 'TT'
        }
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_ext",
        {
            //total=47502020.0 eff=40057650.0 - 7444370.0 = 32613280.0
            32613280.0,
            61526.7 // xsec for process 'WJetsToLNu'
        }
    },
    {"WW_TuneCUETP8M1_13TeV-pythia8",
        {
            //total=993214.0 eff=993214.0 - 0.0 = 993214.0
            993214.0,
            63.7 // xsec for process 'WW'
        }
    },
    {"WZ_TuneCUETP8M1_13TeV-pythia8",
        {
            //total=1000000.0 eff=1000000.0 - 0.0 = 1000000.0
            1000000.0,
            47.13 // xsec for process 'WZ'
        }
    },
    {"ZZ_TuneCUETP8M1_13TeV-pythia8",
        {
            //total=989312.0 eff=989312.0 - 0.0 = 989312.0
            989312.0,
            16.523 // xsec for process 'ZZ'
        }
    }
};

const std::unordered_map<std::string,const std::unordered_map<std::string,FileInfo>> _eventWeightsPerEra =
{
    {"80Xv1",eventWeights80Xv1},
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
