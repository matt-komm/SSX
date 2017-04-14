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


const std::unordered_map<std::string,WeightInfoContainer> eventWeights80Xexcl = {
    {"DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //total=39840774.0 eff=39840774.0 - 0.0 = 39840774.0
            39840774.0,
            725.0 // xsec for process 'DY1JetsToLL_M-10to50'
        )
    },
    {"DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //total=62627174.0 eff=62627174.0 - 0.0 = 62627174.0
            62627174.0,
            1016.0 // xsec for process 'DY1JetsToLL_M-50'
        )
    },
    {"DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //total=19442927.0 eff=19442927.0 - 0.0 = 19442927.0
            19442927.0,
            394.5 // xsec for process 'DY2JetsToLL_M-10to50'
        )
    },
    {"DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //total=19970551.0 eff=19970551.0 - 0.0 = 19970551.0
            19970551.0,
            331.0 // xsec for process 'DY2JetsToLL_M-50'
        )
    },
    {"DY3JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //total=4964197.0 eff=4964197.0 - 0.0 = 4964197.0
            4964197.0,
            96.47 // xsec for process 'DY3JetsToLL_M-10to50'
        )
    },
    {"DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //total=5856110.0 eff=5856110.0 - 0.0 = 5856110.0
            5856110.0,
            96.0 // xsec for process 'DY3JetsToLL_M-50'
        )
    },
    {"DY4JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //total=2087849.0 eff=2087849.0 - 0.0 = 2087849.0
            2087849.0,
            34.84 // xsec for process 'DY4JetsToLL_M-10to50'
        )
    },
    {"DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //total=4197868.0 eff=4197868.0 - 0.0 = 4197868.0
            4197868.0,
            51.0 // xsec for process 'DY4JetsToLL_M-50'
        )
    },
    {"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //total=35291566.0 eff=35291566.0 - 0.0 = 35291566.0
            35291566.0,
            18610.0 // xsec for process 'DYJetsToLL_M-10to50'
        )
    },
    {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",
        new SimpleWeightInfo(
            //total=49144274.0 eff=49144274.0 - 0.0 = 49144274.0
            49144274.0,
            4895.0 // xsec for process 'DYJetsToLL_M-50'
        )
    },
    {"QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=3566646.0 eff=3566646.0 - 0.0 = 3566646.0
            3566646.0,
            1.6212392 // xsec for process 'QCD_Pt-1000toInf_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //total=40964345.0 eff=40964345.0 - 0.0 = 40964345.0
            40964345.0,
            62964.0 // xsec for process 'QCD_Pt-120to170_EMEnriched'
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
    {"QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=11136483.0 eff=11136483.0 - 0.0 = 11136483.0
            11136483.0,
            18810.0 // xsec for process 'QCD_Pt-170to300_EMEnriched'
        )
    },
    {"QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=19607777.0 eff=19607777.0 - 0.0 = 19607777.0
            19607777.0,
            8654.49315 // xsec for process 'QCD_Pt-170to300_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=9218954.0 eff=9218954.0 - 0.0 = 9218954.0
            9218954.0,
            5352960.0 // xsec for process 'QCD_Pt-20to30_EMEnriched'
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
            //total=24605508.0 eff=24605508.0 - 0.0 = 24605508.0
            24605508.0,
            797.35269 // xsec for process 'QCD_Pt-300to470_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //total=7373633.0 eff=7373633.0 - 0.0 = 7373633.0
            7373633.0,
            1350.0 // xsec for process 'QCD_Pt-300toInf_EMEnriched'
        )
    },
    {"QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //total=6768384.0 eff=6768384.0 - 0.0 = 6768384.0
            6768384.0,
            9928000.0 // xsec for process 'QCD_Pt-30to50_EMEnriched'
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
    {"QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //total=22820109.0 eff=22820109.0 - 0.0 = 22820109.0
            22820109.0,
            2890800.0 // xsec for process 'QCD_Pt-50to80_EMEnriched'
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
    {"QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //total=39985821.0 eff=39985821.0 - 0.0 = 39985821.0
            39985821.0,
            350000.0 // xsec for process 'QCD_Pt-80to120_EMEnriched'
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
            //total=23712175.0 eff=19971756.0 - 3740419.0 = 16231337.0
            16231337.0,
            61526.7 // xsec for process 'WJetsToLNu'
        )
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",
        new SimpleWeightInfo(
            //total=57026058.0 eff=57026058.0 - 0.0 = 57026058.0
            57026058.0,
            61526.7 // xsec for process 'WJetsToLNu'
        )
    },
    {"WToLNu_0J_13TeV-amcatnloFXFX-pythia8_ext",
        new SimpleWeightInfo(
            //total=48648355.0 eff=44094225.0 - 4554130.0 = 39540095.0
            39540095.0,
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
            3226.0 // xsec for process 'WToLNu_2J_13TeV'
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

class EventWeight:
    public pxl::Module
{
    private:
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
            getOption("EraName",_eraName);
            
            if (_eventWeightsPerEra.find(_eraName)==_eventWeightsPerEra.cend())
            {
                throw std::runtime_error("Event weight era not found: "+_eraName);
            }
            logger(pxl::LOG_LEVEL_INFO , "Event weights taken from '"+_eraName+"'");
            
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
                    auto it = _eventWeightsPerEra.at(_eraName).find(processName);
                    if (it==_eventWeightsPerEra.at(_eraName).cend())
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

PXL_MODULE_INIT(EventWeight)
PXL_PLUGIN_INIT
