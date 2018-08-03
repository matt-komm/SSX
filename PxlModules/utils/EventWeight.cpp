#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <unordered_map>

static pxl::Logger logger("EventWeight");

class WeightInfo
{
    public:

        virtual double getWeight(const pxl::Event* event) const = 0;
};

class WeightInfoContainer
{
    protected:
        std::shared_ptr<WeightInfo> _ptr;
    public:
        WeightInfoContainer(WeightInfo* ptr):
            _ptr(ptr)
        {
        }
        
        WeightInfo* operator->()
        {
            return _ptr.get();
        }
        
        const WeightInfo* operator->() const
        {
            return _ptr.get();
        }
        
        ~WeightInfoContainer()
        {
            //This will segfault; most likly sth wrong with (static?) memory allocation in
            //the weight list below ... shared_ptr does not help either
            //So live with this memleak atm
            /*
            if (_ptr)
            {
                delete _ptr;
            }
            */
        }
};

class SimpleWeightInfo:
    public WeightInfo
{
    public:
        double _nEvents;
        double _crossSection;
        
        SimpleWeightInfo(double nEvents, double crossSection):
            _nEvents(nEvents),
            _crossSection(crossSection)
        {
        }
        
        virtual double getWeight(const pxl::Event*) const
        {
            return _crossSection/_nEvents;
        }
};

class WeightPerPartonInfo:
    public WeightInfo
{
    public:
        std::vector<double> _weightsPerParton;
        
        WeightPerPartonInfo(std::vector<double> weightsPerParton):
            _weightsPerParton(weightsPerParton)
        {
        }
        
        ~WeightPerPartonInfo()
        {
            _weightsPerParton.clear();
        }
        
        virtual double getWeight(const pxl::Event* ev) const
        {
            int index = -1;
            if (ev->hasUserRecord("nparton"))
            {
                index = ev->getUserRecord("nparton").toInt64();
            }
            else
            {
                throw std::runtime_error("Cannot find 'nparton' field for event "+ev->getUserRecord("ProcessName").toString());
            }
            if (index<0)
            {
                throw std::runtime_error("'nparton' field should not be negative (="+std::to_string(index)+") for event "+ev->getUserRecord("ProcessName").toString());
            }
            if (index>=_weightsPerParton.size())
            {
                index = _weightsPerParton.size()-1;
            }
            return _weightsPerParton[index];
        }
};



/*

WeightPerPartonInfo* drellYanM50 = new WeightPerPartonInfo({
    0.1205*0.001,
    0.0163*0.001,
    0.0167*0.001,
    0.0173*0.001,
    0.0135*0.001,
    0.1205*0.001
});

WeightPerPartonInfo* drellYanM10to50 = new WeightPerPartonInfo({
    0.5273*0.001,
    0.0204*0.001,
    0.0226*0.001,
    0.0217*0.001,
    0.0187*0.001,
    0.5273*0.001
});

const std::unordered_map<std::string,WeightInfoContainer> eventWeights80XwithHLT = {


    {"DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        drellYanM10to50
    },
    {"DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        drellYanM50
    },
    {"DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        drellYanM10to50
    },
    {"DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        drellYanM50
    },
    {"DY3JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        drellYanM10to50
    },
    {"DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        drellYanM50
    },
    {"DY4JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        drellYanM10to50
    },
    {"DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        drellYanM50
    },
    {"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        drellYanM10to50
    },
    {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",
        drellYanM50
    },
    {"QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=3566646.0 eff=3566646.0 - 0.0 = 3566646.0
            3566646.0,
            1.6212392 // xsec for process 'QCD_Pt-1000toInf_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=11938140.0 eff=11938140.0 - 0.0 = 11938140.0
            11938140.0,
            25190.51514 // xsec for process 'QCD_Pt-120to170_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=4141251.0 eff=4141251.0 - 0.0 = 4141251.0
            4141251.0,
            3819570.0 // xsec for process 'QCD_Pt-15to20_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=19607777.0 eff=19607777.0 - 0.0 = 19607777.0
            19607777.0,
            8654.49315 // xsec for process 'QCD_Pt-170to300_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=31475157.0 eff=31475157.0 - 0.0 = 31475157.0
            31475157.0,
            2960198.4 // xsec for process 'QCD_Pt-20to30_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //total=24127643.0 eff=24127643.0 - 0.0 = 24127643.0
            24127643.0,
            797.35269 // xsec for process 'QCD_Pt-300to470_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=29252006.0 eff=29252006.0 - 0.0 = 29252006.0
            29252006.0,
            1652471.46 // xsec for process 'QCD_Pt-30to50_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //total=9847664.0 eff=9847664.0 - 0.0 = 9847664.0
            9847664.0,
            79.02211 // xsec for process 'QCD_Pt-470to600_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=19806915.0 eff=19806915.0 - 0.0 = 19806915.0
            19806915.0,
            437504.1 // xsec for process 'QCD_Pt-50to80_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=9756853.0 eff=9756853.0 - 0.0 = 9756853.0
            9756853.0,
            25.0951932 // xsec for process 'QCD_Pt-600to800_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //total=9966149.0 eff=9966149.0 - 0.0 = 9966149.0
            9966149.0,
            4.707572 // xsec for process 'QCD_Pt-800to1000_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //total=9797244.0 eff=9797244.0 - 0.0 = 9797244.0
            9797244.0,
            106033.6648 // xsec for process 'QCD_Pt-80to120_MuEnrichedPt5'
        )
    },
    {"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //total=38811017.0 eff=38811017.0 - 0.0 = 38811017.0
            38811017.0,
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //total=67240808.0 eff=67240808.0 - 0.0 = 67240808.0
            67240808.0,
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_tW_antitop_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //total=3256407.0 eff=3256407.0 - 0.0 = 3256407.0
            3256407.0,
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //total=6933094.0 eff=6933094.0 - 0.0 = 6933094.0
            6933094.0,
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_top_5f_NoFullyHadronicDecays_13TeV-powheg_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //total=3256650.0 eff=3256650.0 - 0.0 = 3256650.0
            3256650.0,
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //total=6952830.0 eff=6952830.0 - 0.0 = 6952830.0
            6952830.0,
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
        new SimpleWeightInfo(
            //total=77229341.0 eff=77229341.0 - 0.0 = 77229341.0
            77229341.0,
            831.76 // xsec for process 'TT'
        )
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //total=23141980.0 eff=19491569.0 - 3650411.0 = 15841158.0
            15841158.0,
            61526.7 // xsec for process 'WJetsToLNu'
        )
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",
        new SimpleWeightInfo(
            //total=56526888.0 eff=56526888.0 - 0.0 = 56526888.0
            56526888.0,
            61526.7 // xsec for process 'WJetsToLNu'
        )
    },
    {"WToLNu_0J_13TeV-amcatnloFXFX-pythia8_ext",
        new SimpleWeightInfo(
            //total=49142195.0 eff=44541889.0 - 4600306.0 = 39941583.0
            39941583.0,
            49670.0 // xsec for process 'WToLNu_0J_13TeV'
        )
    },
    {"WToLNu_1J_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //total=40739942.0 eff=29901704.0 - 10838238.0 = 19063466.0
            19063466.0,
            8264.0 // xsec for process 'WToLNu_1J_13TeV'
        )
    },
    {"WToLNu_2J_13TeV-amcatnloFXFX-pythia8_ext",
        new SimpleWeightInfo(
            //total=53135013.0 eff=34346729.0 - 18788284.0 = 15558445.0
            15558445.0,
            2544.0 // xsec for process 'WToLNu_2J_13TeV'
        )
    },
    {"WW_TuneCUETP8M1_13TeV-pythia8_ext",
        new SimpleWeightInfo(
            //total=6987124.0 eff=6987124.0 - 0.0 = 6987124.0
            6987124.0,
            63.7 // xsec for process 'WW'
        )
    },
    {"WZ_TuneCUETP8M1_13TeV-pythia8_ext",
        new SimpleWeightInfo(
            //total=2995828.0 eff=2995828.0 - 0.0 = 2995828.0
            2995828.0,
            47.13 // xsec for process 'WZ'
        )
    },
    {"ZZ_TuneCUETP8M1_13TeV-pythia8_ext",
        new SimpleWeightInfo(
            //total=998034.0 eff=998034.0 - 0.0 = 998034.0
            998034.0,
            16.523 // xsec for process 'ZZ'
        )
    },
    {"bTag_B2bX_t_13TeV",
        new SimpleWeightInfo(
            //total=21000.0 eff=21000.0 - 0.0 = 21000.0
            21000.0,
            0.130 //WARNING, xsec not found
        )
    },
};

const std::unordered_map<std::string,const std::unordered_map<std::string,WeightInfoContainer>> _eventWeightsPerEra =
{
    {"80XwithHLT",eventWeights80XwithHLT},
    {"80Xexcl",eventWeights80Xexcl}
};
*/
class EventWeight:
    public pxl::Module
{
    private:
        const static std::unordered_map<std::string,WeightInfoContainer> _eventWeights;
    
        pxl::Source* _outputSource;
        std::string _processNameField;

        std::vector<std::string> _allowedPostfixes;
        
        std::vector<std::string> _processNameList;
        
        std::string _eraName;
        std::string _weightName;

    public:
    
        EventWeight():
            Module(),
            _processNameField("ProcessName"),
            _allowedPostfixes({"","_iso","_midiso","_antiiso"}),
            _eraName("80Xexcl"),
            _weightName("mcweight")
        {
            addSink("input", "input");
            _outputSource = addSource("output","output");
            
            addOption("name of process field","",_processNameField);
            
            addOption("EraName","",_eraName);
            addOption("weightname","",_weightName);
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
            /*
            getOption("EraName",_eraName);
            
            if (_eventWeightsPerEra.find(_eraName)==_eventWeightsPerEra.cend())
            {
                throw std::runtime_error("Event weight era not found: "+_eraName);
            }
            logger(pxl::LOG_LEVEL_INFO , "Event weights taken from '"+_eraName+"'");
            */
            getOption("weightname",_weightName);
            
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    std::string processName = event->getUserRecord(_processNameField).toString();
                    auto it = _eventWeights.find(processName);
                    if (it==_eventWeights.cend())
                    {
                        throw std::runtime_error("no event weight information available for process name '"+processName+"' in era '"+_eraName+"'");
                    }
                    else
                    {
                        event->setUserRecord(_weightName,1.0*it->second->getWeight(event));
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

const std::unordered_map<std::string,WeightInfoContainer> EventWeight::_eventWeights = {
    {"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //xtotal=40381391.0 eff=34852843.0 - 5528548.0 = 29324295.0
            1.20912947725e+12, //xsec from weight =  29942.7396458
            18610.0 // xsec for process 'DYJetsToLL_M-10to50'
        )
    },
    {"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=35291566.0 eff=35291566.0 - 0.0 = 35291566.0
            35291566.0, //xsec from weight =  1.0
            18610.0 // xsec for process 'DYJetsToLL_M-10to50'
        )
    },
    {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //xtotal=122055388.0 eff=101982201.0 - 20073187.0 = 81909014.0
            1.92573953018e+12, //xsec from weight =  15777.5872227
            4895.0 // xsec for process 'DYJetsToLL_M-50'
        )
    },
    {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=49144274.0 eff=49144274.0 - 0.0 = 49144274.0
            49144274.0, //xsec from weight =  1.0
            4895.0 // xsec for process 'DYJetsToLL_M-50'
        )
    },
    {"QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=3566646.0 eff=3566646.0 - 0.0 = 3566646.0
            3566646.0, //xsec from weight =  1.0
            1.6212392 // xsec for process 'QCD_Pt-1000toInf_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=41954035.0 eff=41954035.0 - 0.0 = 41954035.0
            41954512.3281, //xsec from weight =  1.00001137741
            62964.0 // xsec for process 'QCD_Pt-120to170_EMEnriched'
        )
    },
    {"QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=11938140.0 eff=11938140.0 - 0.0 = 11938140.0
            11938449.7109, //xsec from weight =  1.00002594298
            25190.51514 // xsec for process 'QCD_Pt-120to170_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=4141251.0 eff=4141251.0 - 0.0 = 4141251.0
            4141251.0, //xsec from weight =  1.0
            3819570.0 // xsec for process 'QCD_Pt-15to20_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=11540163.0 eff=11540163.0 - 0.0 = 11540163.0
            11540163.0, //xsec from weight =  1.0
            18810.0 // xsec for process 'QCD_Pt-170to300_EMEnriched'
        )
    },
    {"QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=19607777.0 eff=19607777.0 - 0.0 = 19607777.0
            19607777.0, //xsec from weight =  1.0
            8654.49315 // xsec for process 'QCD_Pt-170to300_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=9218954.0 eff=9218954.0 - 0.0 = 9218954.0
            9218958.0625, //xsec from weight =  1.00000044067
            5352960.0 // xsec for process 'QCD_Pt-20to30_EMEnriched'
        )
    },
    {"QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=31475157.0 eff=31475157.0 - 0.0 = 31475157.0
            31475545.9688, //xsec from weight =  1.00001235796
            2960198.4 // xsec for process 'QCD_Pt-20to30_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=24605508.0 eff=24605508.0 - 0.0 = 24605508.0
            24605508.0, //xsec from weight =  1.0
            797.35269 // xsec for process 'QCD_Pt-300to470_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=7373633.0 eff=7373633.0 - 0.0 = 7373633.0
            7373633.0, //xsec from weight =  1.0
            1350.0 // xsec for process 'QCD_Pt-300toInf_EMEnriched'
        )
    },
    {"QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=6768384.0 eff=6768384.0 - 0.0 = 6768384.0
            6768393.70312, //xsec from weight =  1.0000014336
            9928000.0 // xsec for process 'QCD_Pt-30to50_EMEnriched'
        )
    },
    {"QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=29252006.0 eff=29252006.0 - 0.0 = 29252006.0
            29252377.5, //xsec from weight =  1.00001269998
            1652471.46 // xsec for process 'QCD_Pt-30to50_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=9847664.0 eff=9847664.0 - 0.0 = 9847664.0
            9847701.0625, //xsec from weight =  1.00000376358
            79.02211 // xsec for process 'QCD_Pt-470to600_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=23474171.0 eff=23474171.0 - 0.0 = 23474171.0
            23474171.0, //xsec from weight =  1.0
            2890800.0 // xsec for process 'QCD_Pt-50to80_EMEnriched'
        )
    },
    {"QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=19806915.0 eff=19806915.0 - 0.0 = 19806915.0
            19806915.0, //xsec from weight =  1.0
            437504.1 // xsec for process 'QCD_Pt-50to80_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=9756853.0 eff=9756853.0 - 0.0 = 9756853.0
            9756853.0, //xsec from weight =  1.0
            25.0951932 // xsec for process 'QCD_Pt-600to800_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=9966149.0 eff=9966149.0 - 0.0 = 9966149.0
            9966149.15625, //xsec from weight =  1.00000001568
            4.707572 // xsec for process 'QCD_Pt-800to1000_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=41853504.0 eff=41853504.0 - 0.0 = 41853504.0
            41859612.4688, //xsec from weight =  1.0001459488
            350000.0 // xsec for process 'QCD_Pt-80to120_EMEnriched'
        )
    },
    {"QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=9797244.0 eff=9797244.0 - 0.0 = 9797244.0
            9798187.48828, //xsec from weight =  1.0000963014
            106033.6648 // xsec for process 'QCD_Pt-80to120_MuEnrichedPt5'
        )
    },
    {"ST_t-channel_antitop_4f_hdampdown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3999346.0 eff=3999346.0 - 0.0 = 3999346.0
            3999346.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_hdampup_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=4000000.0 eff=4000000.0 - 0.0 = 4000000.0
            4000000.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp",
        new SimpleWeightInfo(
            //xtotal=3990259.0 eff=3990259.0 - 0.0 = 3990259.0
            3990259.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=38593260.0 eff=38593260.0 - 0.0 = 38593260.0
            38593260.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin",
        new SimpleWeightInfo(
            //xtotal=3928063.0 eff=3928063.0 - 0.0 = 3928063.0
            3928063.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_mtop1715_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3961753.0 eff=3961753.0 - 0.0 = 3961753.0
            3961753.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_mtop1735_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3984536.0 eff=3984536.0 - 0.0 = 3984536.0
            3984536.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_scaledown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3894778.0 eff=3894778.0 - 0.0 = 3894778.0
            3894778.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_scaleup_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3970546.0 eff=3970546.0 - 0.0 = 3970546.0
            3970546.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_eleDecays_13TeV-comphep-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=604020.0 eff=604020.0 - 0.0 = 604020.0
            604020.0, //xsec from weight =  1.0
            70.688826 // xsec for process 'ST_t-channel_eleDecays_13TeV-comphep'
        )
    },
    {"ST_t-channel_muDecays_13TeV-comphep-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=603449.0 eff=603449.0 - 0.0 = 603449.0
            603449.0, //xsec from weight =  1.0
            70.688826 // xsec for process 'ST_t-channel_muDecays_13TeV-comphep'
        )
    },
    {"ST_t-channel_tauDecays_13TeV-comphep-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=603483.0 eff=603483.0 - 0.0 = 603483.0
            603483.0, //xsec from weight =  1.0
            70.688826 // xsec for process 'ST_t-channel_tauDecays_13TeV-comphep'
        )
    },
    {"ST_t-channel_top_4f_hdampdown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=6000000.0 eff=6000000.0 - 0.0 = 6000000.0
            6000000.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_hdampup_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=6000000.0 eff=6000000.0 - 0.0 = 6000000.0
            6000000.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp",
        new SimpleWeightInfo(
            //xtotal=5887322.0 eff=5887322.0 - 0.0 = 5887322.0
            5887322.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=67240808.0 eff=67240808.0 - 0.0 = 67240808.0
            67240808.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin",
        new SimpleWeightInfo(
            //xtotal=5993676.0 eff=5993676.0 - 0.0 = 5993676.0
            5993676.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_mtop1715_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=5981826.0 eff=5981826.0 - 0.0 = 5981826.0
            5981826.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_mtop1735_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=5970340.0 eff=5970340.0 - 0.0 = 5970340.0
            5970340.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_scaledown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=5946672.0 eff=5946672.0 - 0.0 = 5946672.0
            5946672.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_scaleup_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=5709148.0 eff=5709148.0 - 0.0 = 5709148.0
            5709148.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=6933094.0 eff=6933094.0 - 0.0 = 6933094.0
            6933094.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_antitop_5f_mtop1695_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=1000000.0 eff=1000000.0 - 0.0 = 1000000.0
            1000000.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_antitop_5f_mtop1755_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=999379.0 eff=999379.0 - 0.0 = 999379.0
            999379.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_antitop_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=999068.0 eff=999068.0 - 0.0 = 999068.0
            999068.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_antitop_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=1000000.0 eff=1000000.0 - 0.0 = 1000000.0
            1000000.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=6952830.0 eff=6952830.0 - 0.0 = 6952830.0
            6952830.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"ST_tW_top_5f_mtop1695_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=999488.0 eff=999488.0 - 0.0 = 999488.0
            999488.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"ST_tW_top_5f_mtop1755_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=997550.0 eff=997550.0 - 0.0 = 997550.0
            997550.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"ST_tW_top_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=993640.0 eff=993640.0 - 0.0 = 993640.0
            993640.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"ST_tW_top_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=997880.0 eff=997880.0 - 0.0 = 997880.0
            997880.0, //xsec from weight =  1.0
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-fsrdown-pythia8",
        new SimpleWeightInfo(
            //xtotal=155991586.0 eff=155991586.0 - 0.0 = 155991586.0
            155991586.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-fsrup-pythia8",
        new SimpleWeightInfo(
            //xtotal=152617579.0 eff=152617579.0 - 0.0 = 152617579.0
            152617579.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-isrdown-pythia8",
        new SimpleWeightInfo(
            //xtotal=149762990.0 eff=149762990.0 - 0.0 = 149762990.0
            149762990.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-isrup-pythia8",
        new SimpleWeightInfo(
            //xtotal=156070511.0 eff=156070511.0 - 0.0 = 156070511.0
            156070511.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
        new SimpleWeightInfo(
            //xtotal=77081156.0 eff=77081156.0 - 0.0 = 77081156.0
            77081156.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_mtop1715_13TeV-powheg-pythia8",
        new SimpleWeightInfo(
            //xtotal=79486546.0 eff=79486546.0 - 0.0 = 79486546.0
            79486546.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_mtop1735_13TeV-powheg-pythia8",
        new SimpleWeightInfo(
            //xtotal=79278928.0 eff=79278928.0 - 0.0 = 79278928.0
            79278928.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4down_13TeV-powheg-pythia8",
        new SimpleWeightInfo(
            //xtotal=58338240.0 eff=58338240.0 - 0.0 = 58338240.0
            58338240.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4up_13TeV-powheg-pythia8",
        new SimpleWeightInfo(
            //xtotal=58953660.0 eff=58953660.0 - 0.0 = 58953660.0
            58953660.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_hdampDOWN_TuneCUETP8M2T4_13TeV-powheg-pythia8",
        new SimpleWeightInfo(
            //xtotal=58163976.0 eff=58163976.0 - 0.0 = 58163976.0
            58163976.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_hdampUP_TuneCUETP8M2T4_13TeV-powheg-pythia8",
        new SimpleWeightInfo(
            //xtotal=58858606.0 eff=58858606.0 - 0.0 = 58858606.0
            58858606.0, //xsec from weight =  1.0
            831.76 // xsec for process 'TT'
        )
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //xtotal=23712175.0 eff=19971756.0 - 3740419.0 = 16231337.0
            3.67487479808e+12, //xsec from weight =  154978.39393
            61526.7 // xsec for process 'WJetsToLNu'
        )
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=57026058.0 eff=57026058.0 - 0.0 = 57026058.0
            57026058.0, //xsec from weight =  1.0
            61526.7 // xsec for process 'WJetsToLNu'
        )
    },
    {"WToLNu_0J_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //xtotal=98083988.0 eff=88895269.0 - 9188719.0 = 79706550.0
            5.70074820256e+12, //xsec from weight =  58121.0890666
            49670.0 // xsec for process 'WToLNu_0J_13TeV'
        )
    },
    {"WToLNu_1J_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //xtotal=179688638.0 eff=131887800.0 - 47800838.0 = 84086962.0
            7.80839207795e+12, //xsec from weight =  43455.1241796
            8264.0 // xsec for process 'WToLNu_1J_13TeV'
        )
    },
    {"WToLNu_2J_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //xtotal=258502250.0 eff=166986744.0 - 91515506.0 = 75471238.0
            5.68821104143e+12, //xsec from weight =  22004.4933513
            3226.0 // xsec for process 'WToLNu_2J_13TeV'
        )
    },
    
    
    
    //gen only
    {"ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-herwigpp_TuneEE5C",
        new SimpleWeightInfo(
            //xtotal=19299964.0 eff=12519100.0 - 6780864.0 = 5738236.0
            1299149749.22, //xsec from weight =  67.3135840678
            70.688826 // xsec for process 'ST_t-channel_4f_leptonDecays'
        )
    },
    {"ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=19938230.0 eff=12117204.0 - 7821026.0 = 4296178.0
            1341440559.5, //xsec from weight =  67.2798217043
            70.688826 // xsec for process 'ST_t-channel_4f_leptonDecays'
        )
    },
    {"ST_t-channel_5f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1_GEN_v180731",
        new SimpleWeightInfo(
            //xtotal=1960000.0 eff=1350088.0 - 609912.0 = 740176.0
            536338.46875, //xsec from weight =  0.273642075893
            70.688826 // xsec for process 'ST_t-channel_5f_leptonDecays'
        )
    }
    /* these are also fully available - see above
    {"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp",
        new SimpleWeightInfo(
            //xtotal=3990259.0 eff=3990259.0 - 0.0 = 3990259.0
            3990259.0, //xsec from weight =  1.0
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp",
        new SimpleWeightInfo(
            //xtotal=5887322.0 eff=5887322.0 - 0.0 = 5887322.0
            5887322.0, //xsec from weight =  1.0
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    */
};


PXL_MODULE_INIT(EventWeight)
PXL_PLUGIN_INIT
