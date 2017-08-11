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
        WeightInfo* _ptr;
    public:
        WeightInfoContainer(WeightInfo* ptr):
            _ptr(ptr)
        {
        }
        
        WeightInfo* operator->()
        {
            return _ptr;
        }
        
        const WeightInfo* operator->() const
        {
            return _ptr;
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


const std::unordered_map<std::string,WeightInfoContainer> eventWeights80Xexcl = {
    {"DY1JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=33219691.0 eff=33219691.0 - 0.0 = 33219691.0
            33219691.0, //xsec from weight =  1.0  (matching eff = 0.00137931034483)
            725.0 // xsec for process 'DY1JetsToLL_M-10to50'
        )
    },
    {"DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=61629627.0 eff=61629627.0 - 0.0 = 61629627.0
            61629627.0, //xsec from weight =  1.0  (matching eff = 0.000984251968504)
            1016.0 // xsec for process 'DY1JetsToLL_M-50'
        )
    },
    {"DY2JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=19442927.0 eff=19442927.0 - 0.0 = 19442927.0
            19442927.0, //xsec from weight =  1.0  (matching eff = 0.00253485424588)
            394.5 // xsec for process 'DY2JetsToLL_M-10to50'
        )
    },
    {"DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=19970551.0 eff=19970551.0 - 0.0 = 19970551.0
            19970551.0, //xsec from weight =  1.0  (matching eff = 0.00302114803625)
            331.0 // xsec for process 'DY2JetsToLL_M-50'
        )
    },
    {"DY3JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=4531019.0 eff=4531019.0 - 0.0 = 4531019.0
            4531019.0, //xsec from weight =  1.0  (matching eff = 0.0103659168653)
            96.47 // xsec for process 'DY3JetsToLL_M-10to50'
        )
    },
    {"DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=5449236.0 eff=5449236.0 - 0.0 = 5449236.0
            5449236.0, //xsec from weight =  1.0  (matching eff = 0.0104166666667)
            96.0 // xsec for process 'DY3JetsToLL_M-50'
        )
    },
    {"DY4JetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=2087849.0 eff=2087849.0 - 0.0 = 2087849.0
            2087849.0, //xsec from weight =  1.0  (matching eff = 0.0287026406429)
            34.84 // xsec for process 'DY4JetsToLL_M-10to50'
        )
    },
    {"DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=4197868.0 eff=4197868.0 - 0.0 = 4197868.0
            4197868.0, //xsec from weight =  1.0  (matching eff = 0.0196078431373)
            51.0 // xsec for process 'DY4JetsToLL_M-50'
        )
    },
    {"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        new SimpleWeightInfo(
            //xtotal=34092958.0 eff=34092958.0 - 0.0 = 34092958.0
            34092958.0, //xsec from weight =  1.0  (matching eff = 5.37345513165e-05)
            18610.0 // xsec for process 'DYJetsToLL_M-10to50'
        )
    },
    {"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=43554876.0 eff=43554876.0 - 0.0 = 43554876.0
            43554876.0, //xsec from weight =  1.0  (matching eff = 0.000204290091931)
            4895.0 // xsec for process 'DYJetsToLL_M-50'
        )
    },
    {"QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=3566646.0 eff=3566646.0 - 0.0 = 3566646.0
            3566646.0, //xsec from weight =  1.0  (matching eff = 0.616812127415)
            1.6212392 // xsec for process 'QCD_Pt-1000toInf_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=40377565.0 eff=40377565.0 - 0.0 = 40377565.0
            40378025.1719, //xsec from weight =  1.00001139672  (matching eff = 1.58822723576e-05)
            62964.0 // xsec for process 'QCD_Pt-120to170_EMEnriched'
        )
    },
    {"QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=11288657.0 eff=11288657.0 - 0.0 = 11288657.0
            11288949.8359, //xsec from weight =  1.00002594072  (matching eff = 3.96985109342e-05)
            25190.51514 // xsec for process 'QCD_Pt-120to170_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=4141251.0 eff=4141251.0 - 0.0 = 4141251.0
            4141251.0, //xsec from weight =  1.0  (matching eff = 2.61809575423e-07)
            3819570.0 // xsec for process 'QCD_Pt-15to20_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=11540163.0 eff=11540163.0 - 0.0 = 11540163.0
            11540163.0, //xsec from weight =  1.0  (matching eff = 5.31632110579e-05)
            18810.0 // xsec for process 'QCD_Pt-170to300_EMEnriched'
        )
    },
    {"QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=19607777.0 eff=19607777.0 - 0.0 = 19607777.0
            19607777.0, //xsec from weight =  1.0  (matching eff = 0.000115546916806)
            8654.49315 // xsec for process 'QCD_Pt-170to300_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=9218954.0 eff=9218954.0 - 0.0 = 9218954.0
            9218958.0625, //xsec from weight =  1.00000044067  (matching eff = 1.86812612212e-07)
            5352960.0 // xsec for process 'QCD_Pt-20to30_EMEnriched'
        )
    },
    {"QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=30789588.0 eff=30789588.0 - 0.0 = 30789588.0
            30789969.4688, //xsec from weight =  1.00001238954  (matching eff = 3.37819380464e-07)
            2960198.4 // xsec for process 'QCD_Pt-20to30_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=24605508.0 eff=24605508.0 - 0.0 = 24605508.0
            24605508.0, //xsec from weight =  1.0  (matching eff = 0.00125415015531)
            797.35269 // xsec for process 'QCD_Pt-300to470_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=7373633.0 eff=7373633.0 - 0.0 = 7373633.0
            7373633.0, //xsec from weight =  1.0  (matching eff = 0.000740740740741)
            1350.0 // xsec for process 'QCD_Pt-300toInf_EMEnriched'
        )
    },
    {"QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=5710280.0 eff=5710280.0 - 0.0 = 5710280.0
            5710288.51562, //xsec from weight =  1.00000149128  (matching eff = 1.00725371805e-07)
            9928000.0 // xsec for process 'QCD_Pt-30to50_EMEnriched'
        )
    },
    {"QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=29252006.0 eff=29252006.0 - 0.0 = 29252006.0
            29252377.5, //xsec from weight =  1.00001269998  (matching eff = 6.0516185858e-07)
            1652471.46 // xsec for process 'QCD_Pt-30to50_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=9526325.0 eff=9526325.0 - 0.0 = 9526325.0
            9526360.625, //xsec from weight =  1.00000373964  (matching eff = 0.0126547334618)
            79.02211 // xsec for process 'QCD_Pt-470to600_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=19969074.0 eff=19969074.0 - 0.0 = 19969074.0
            19969074.0, //xsec from weight =  1.0  (matching eff = 3.45925003459e-07)
            2890800.0 // xsec for process 'QCD_Pt-50to80_EMEnriched'
        )
    },
    {"QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=18289390.0 eff=18289390.0 - 0.0 = 18289390.0
            18289390.0, //xsec from weight =  1.0  (matching eff = 2.28569286551e-06)
            437504.1 // xsec for process 'QCD_Pt-50to80_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8",
        new SimpleWeightInfo(
            //xtotal=9130791.0 eff=9130791.0 - 0.0 = 9130791.0
            9130791.0, //xsec from weight =  1.0  (matching eff = 0.0398482686318)
            25.0951932 // xsec for process 'QCD_Pt-600to800_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=9966149.0 eff=9966149.0 - 0.0 = 9966149.0
            9966149.15625, //xsec from weight =  1.00000001568  (matching eff = 0.21242373259)
            4.707572 // xsec for process 'QCD_Pt-800to1000_MuEnrichedPt5'
        )
    },
    {"QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=41853504.0 eff=41853504.0 - 0.0 = 41853504.0
            41859612.4688, //xsec from weight =  1.0001459488  (matching eff = 2.85755985372e-06)
            350000.0 // xsec for process 'QCD_Pt-80to120_EMEnriched'
        )
    },
    {"QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=8972682.0 eff=8972682.0 - 0.0 = 8972682.0
            8973547.23828, //xsec from weight =  1.00009643028  (matching eff = 9.43187649103e-06)
            106033.6648 // xsec for process 'QCD_Pt-80to120_MuEnrichedPt5'
        )
    },
    {"ST_t-channel_antitop_4f_hdampdown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3999346.0 eff=3999346.0 - 0.0 = 3999346.0
            3999346.0, //xsec from weight =  1.0  (matching eff = 0.012353304509)
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_hdampup_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=4000000.0 eff=4000000.0 - 0.0 = 4000000.0
            4000000.0, //xsec from weight =  1.0  (matching eff = 0.012353304509)
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp",
        new SimpleWeightInfo(
            //xtotal=3990259.0 eff=3990259.0 - 0.0 = 3990259.0
            3990259.0, //xsec from weight =  1.0  (matching eff = 0.012353304509)
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=38811017.0 eff=38811017.0 - 0.0 = 38811017.0
            38811017.0, //xsec from weight =  1.0  (matching eff = 0.012353304509)
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin",
        new SimpleWeightInfo(
            //xtotal=3928063.0 eff=3928063.0 - 0.0 = 3928063.0
            3928063.0, //xsec from weight =  1.0  (matching eff = 0.012353304509)
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_mtop1695_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3991785.0 eff=3991785.0 - 0.0 = 3991785.0
            3991785.0, //xsec from weight =  1.0  (matching eff = 0.012353304509)
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_mtop1755_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3994974.0 eff=3994974.0 - 0.0 = 3994974.0
            3994974.0, //xsec from weight =  1.0  (matching eff = 0.012353304509)
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_scaledown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3894778.0 eff=3894778.0 - 0.0 = 3894778.0
            3894778.0, //xsec from weight =  1.0  (matching eff = 0.012353304509)
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_antitop_4f_scaleup_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=3970546.0 eff=3970546.0 - 0.0 = 3970546.0
            3970546.0, //xsec from weight =  1.0  (matching eff = 0.012353304509)
            80.95 // xsec for process 'ST_t-channel_antitop_4f'
        )
    },
    {"ST_t-channel_top_4f_hdampdown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=6000000.0 eff=6000000.0 - 0.0 = 6000000.0
            6000000.0, //xsec from weight =  1.0  (matching eff = 0.00735186002059)
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_hdampup_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=6000000.0 eff=6000000.0 - 0.0 = 6000000.0
            6000000.0, //xsec from weight =  1.0  (matching eff = 0.00735186002059)
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-herwigpp",
        new SimpleWeightInfo(
            //xtotal=5887322.0 eff=5887322.0 - 0.0 = 5887322.0
            5887322.0, //xsec from weight =  1.0  (matching eff = 0.00735186002059)
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        new SimpleWeightInfo(
            //xtotal=67240808.0 eff=67240808.0 - 0.0 = 67240808.0
            67240808.0, //xsec from weight =  1.0  (matching eff = 0.00735186002059)
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_inclusiveDecays_TuneCUETP8M2T4_13TeV-powhegV2-madspin",
        new SimpleWeightInfo(
            //xtotal=5993676.0 eff=5993676.0 - 0.0 = 5993676.0
            5993676.0, //xsec from weight =  1.0  (matching eff = 0.00735186002059)
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_mtop1695_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=5988478.0 eff=5988478.0 - 0.0 = 5988478.0
            5988478.0, //xsec from weight =  1.0  (matching eff = 0.00735186002059)
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_mtop1755_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=5990049.0 eff=5990049.0 - 0.0 = 5990049.0
            5990049.0, //xsec from weight =  1.0  (matching eff = 0.00735186002059)
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_scaledown_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=5946672.0 eff=5946672.0 - 0.0 = 5946672.0
            5946672.0, //xsec from weight =  1.0  (matching eff = 0.00735186002059)
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_t-channel_top_4f_scaleup_inclusiveDecays_13TeV-powhegV2-madspin-pythia8",
        new SimpleWeightInfo(
            //xtotal=5709148.0 eff=5709148.0 - 0.0 = 5709148.0
            5709148.0, //xsec from weight =  1.0  (matching eff = 0.00735186002059)
            136.02 // xsec for process 'ST_t-channel_top_4f'
        )
    },
    {"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=6933094.0 eff=6933094.0 - 0.0 = 6933094.0
            6933094.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_antitop_5f_mtop1695_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=1000000.0 eff=1000000.0 - 0.0 = 1000000.0
            1000000.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_antitop_5f_mtop1755_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=999379.0 eff=999379.0 - 0.0 = 999379.0
            999379.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_antitop_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=999068.0 eff=999068.0 - 0.0 = 999068.0
            999068.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_antitop_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=1000000.0 eff=1000000.0 - 0.0 = 1000000.0
            1000000.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_antitop'
        )
    },
    {"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=6952830.0 eff=6952830.0 - 0.0 = 6952830.0
            6952830.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"ST_tW_top_5f_mtop1695_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=999488.0 eff=999488.0 - 0.0 = 999488.0
            999488.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"ST_tW_top_5f_mtop1755_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=997550.0 eff=997550.0 - 0.0 = 997550.0
            997550.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"ST_tW_top_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=993640.0 eff=993640.0 - 0.0 = 993640.0
            993640.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"ST_tW_top_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_ext",
        new SimpleWeightInfo(
            //xtotal=997880.0 eff=997880.0 - 0.0 = 997880.0
            997880.0, //xsec from weight =  1.0  (matching eff = 0.0280898876404)
            35.6 // xsec for process 'ST_tW_top'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-colourFlip-pythia8",
        new SimpleWeightInfo(
            //xtotal=11087535.0 eff=11087535.0 - 0.0 = 11087535.0
            11087535.0, //xsec from weight =  1.0  (matching eff = 0.00120226988554)
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-fsrdown-pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=29264084.0 eff=29264084.0 - 0.0 = 29264084.0
            29264084.0, //xsec from weight =  1.0  (matching eff = 0.00120226988554)
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-fsrup-pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=28062430.0 eff=28062430.0 - 0.0 = 28062430.0
            28062430.0, //xsec from weight =  1.0  (matching eff = 0.00120226988554)
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-isrdown-pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=29417010.0 eff=29417010.0 - 0.0 = 29417010.0
            29417010.0, //xsec from weight =  1.0  (matching eff = 0.00120226988554)
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-isrup-pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=58611096.0 eff=58611096.0 - 0.0 = 58611096.0
            58611096.0, //xsec from weight =  1.0  (matching eff = 0.00120226988554)
            831.76 // xsec for process 'TT'
        )
    },
    {"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
        new SimpleWeightInfo(
            //xtotal=76577327.0 eff=76577327.0 - 0.0 = 76577327.0
            76577327.0, //xsec from weight =  1.0  (matching eff = 0.00120226988554)
            831.76 // xsec for process 'TT'
        )
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //xtotal=23840185.0 eff=20079594.0 - 3760591.0 = 16319003.0
            3.6946726615e+12, //xsec from weight =  154976.677467  (matching eff = 2.51885242451)
            61526.7 // xsec for process 'WJetsToLNu'
        )
    },
    {"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=55190961.0 eff=55190961.0 - 0.0 = 55190961.0
            55190961.0, //xsec from weight =  1.0  (matching eff = 1.6253106375e-05)
            61526.7 // xsec for process 'WJetsToLNu'
        )
    },
    {"WToLNu_0J_13TeV-amcatnloFXFX-pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=46358101.0 eff=42018685.0 - 4339416.0 = 37679269.0
            2.69672599968e+12, //xsec from weight =  58171.623546  (matching eff = 1.17116214105)
            49670.0 // xsec for process 'WToLNu_0J_13TeV'
        )
    },
    {"WToLNu_1J_13TeV-amcatnloFXFX-pythia8",
        new SimpleWeightInfo(
            //xtotal=40250522.0 eff=29542656.0 - 10707866.0 = 18834790.0
            1.74928783117e+12, //xsec from weight =  43460.0036036  (matching eff = 5.25895493752)
            8264.0 // xsec for process 'WToLNu_1J_13TeV'
        )
    },
    {"WToLNu_2J_13TeV-amcatnloFXFX-pythia8_ext",
        new SimpleWeightInfo(
            //xtotal=47123857.0 eff=30460768.0 - 16663089.0 = 13797679.0
            9.78799391232e+11, //xsec from weight =  20770.7826469  (matching eff = 6.43855630717)
            3226.0 // xsec for process 'WToLNu_2J_13TeV'
        )
    }

    /*
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
    */
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
