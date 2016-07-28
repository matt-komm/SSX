#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"

#include <string>
#include <unordered_map>
#include <tuple>
#include <iomanip>
#include <fstream>
#include <ctime>

static pxl::Logger logger("LumiInfo");


class LumiInfo:
    public pxl::Module
{
    private:
        pxl::Source* _outputSource;
        
        std::string _lumiInfoFileName;
        
        static std::vector<std::string> splitStr(const std::string& str, char c)
        {
            std::vector<std::string> res;
            auto last = str.cbegin();
            for (auto it = str.cbegin(); it < str.cend(); ++it)
            {
                if (*it==c)
                {
                    res.emplace_back(last,it);
                    last=it+1;
                }
            }
            res.emplace_back(last,str.cend());
            
            /*
            std::cout<<"splitting: "<<str<<std::endl;
            for (auto s: res)
            {
                std::cout<<s<<"|";
            }
            std::cout<<std::endl;
            */
            
            return res;
            
        }
        
        
        //run:fill,    ls,  time,              beamstatus,   E(GeV), delivered(/ub), recorded(/ub), avgpu, source
        //273158:4915, 3:3, 05/11/16 20:43:22, STABLE BEAMS, 6500,4  8357.445,       34.504,        25.1,  PXL
        struct InfoRecord
        {
            unsigned int fillNumber;
            float recordedLumi;
            float avgPu;
            unsigned char week; //1-52
            unsigned char weekDay; //0-6
            unsigned char hour; //0-23
            unsigned char minute; //0-59
            unsigned char sec; //0-59
        };
        
        static std::tuple<unsigned int, unsigned int, InfoRecord> parseLine(const std::string& str)
        {
            
            InfoRecord info;
            std::vector<std::string> splitLine = splitStr(str,',');
            if (splitLine.size()!=9) throw std::runtime_error("Cannot parse line: "+str);
            std::vector<std::string> runFillStr = splitStr(splitLine[0],':');
            if (runFillStr.size()!=2) throw std::runtime_error("Cannot parse run:fill info: "+splitLine[0]);
            unsigned int run;
            try
            {
                run = std::stoul(runFillStr[0]);
            } 
            catch (std::invalid_argument ex)
            {
                throw std::runtime_error("Cannot parse run to long: "+runFillStr[0]);
            }
            
            try
            {
                info.fillNumber = std::stoul(runFillStr[1]);
            } 
            catch (std::invalid_argument ex)
            {
                throw std::runtime_error("Cannot parse fill to long: "+runFillStr[1]);
            }
            
            std::vector<std::string> lumiStr = splitStr(splitLine[1],':');
            if (lumiStr.size()!=2) throw std::runtime_error("Cannot parse lumi:lumi info: "+splitLine[1]);
            unsigned int lumi;
            try
            {
                lumi = std::stoul(lumiStr[0]);
            } 
            catch (std::invalid_argument ex)
            {
                throw std::runtime_error("Cannot parse lumi to long: "+lumiStr[0]);
            }
            
            std::tm timeStruct = {};
            
            unsigned int month,day,year,hour,minute,sec;
            sscanf (splitLine[2].c_str(),"%02i/%02i/%02i %02i:%02i:%02i",&month,&day,&year,&hour,&minute,&sec);
            timeStruct.tm_mon=month-1;
            timeStruct.tm_mday=day-1;
            timeStruct.tm_year=(year+2000)-1900;
            timeStruct.tm_hour=hour;
            timeStruct.tm_min=minute;
            timeStruct.tm_sec=sec;
            /*
            std::stringstream ss;
            ss << splitLine[2];
            ss >> std::get_time(&timeStruct, "%m/%d/%y %H:%M:%S");
            
            */
            mktime(&timeStruct);
            
            info.weekDay = timeStruct.tm_wday;
            info.week = (timeStruct.tm_yday+6)/7;
            info.hour = timeStruct.tm_hour;
            info.minute = timeStruct.tm_min;
            info.sec = timeStruct.tm_sec;
            
            try
            {
                info.recordedLumi = std::stof(splitLine[6]);
            } 
            catch (std::invalid_argument ex)
            {
                throw std::runtime_error("Cannot parse recorded lumi to float: "+splitLine[6]);
            }
            
            try
            {
                info.avgPu = std::stof(splitLine[7]);
            } 
            catch (std::invalid_argument ex)
            {
                throw std::runtime_error("Cannot parse recorded avgPu to float: "+splitLine[7]);
            }
            
            std::tuple<unsigned int, unsigned int, InfoRecord> res(run,lumi,info);
            return res;
        }
        
        std::unordered_map<unsigned int,std::unordered_map<unsigned int,InfoRecord>> _infoByRunLumi;

    public:
    
        LumiInfo():
            Module(),
            _lumiInfoFileName("lumiInfo.csv")
            
        {
            addSink("input", "input");
            _outputSource = addSource("output","output");
            
            addOption("lumi info file","from brilcalc --byls",_lumiInfoFileName,pxl::OptionDescription::USAGE_FILE_OPEN);
            
        }

        ~LumiInfo()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("LumiInfo");
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
            getOption("lumi info file",_lumiInfoFileName);
            std::ifstream infile(_lumiInfoFileName);
            
            unsigned int readLines = 0;
            for( std::string line; getline( infile, line ); )
            {
                if (line[0]=='#')
                {
                    continue;
                }
                std::tuple<unsigned int, unsigned int, InfoRecord> parseResult = parseLine(line);
                _infoByRunLumi[std::get<0>(parseResult)][std::get<1>(parseResult)]=std::get<2>(parseResult);
                ++readLines;
            }
            logger(pxl::LOG_LEVEL_INFO , "Parsed "+std::to_string(readLines)+" lumi info entries!");
            
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
                if (event)
                {
                    if (event->getUserRecord("isRealData").asBool())
                    {
                        unsigned int runNumber = event->getUserRecord("Run").asUInt32();
                        unsigned int lumiBlock = event->getUserRecord("LuminosityBlock").asUInt32();
                        
                        auto findRun = _infoByRunLumi.find(runNumber);
                        if (findRun==_infoByRunLumi.cend())
                        {
                            logger(pxl::LOG_LEVEL_INFO ,"Run info not found: "+std::to_string(runNumber));
                        }
                        else
                        {
                            auto findLumi = findRun->second.find(lumiBlock);
                            if (findLumi==findRun->second.cend())
                            {
                                logger(pxl::LOG_LEVEL_INFO ,"Lumi "+std::to_string(lumiBlock)+" info not found for run "+std::to_string(runNumber));
                            }
                            else
                            {
                                event->setUserRecord("Fill",findLumi->second.fillNumber);
                                event->setUserRecord("recLumi",findLumi->second.recordedLumi);
                                event->setUserRecord("avgPU",findLumi->second.avgPu);
                                event->setUserRecord("Week",findLumi->second.week);
                                event->setUserRecord("Day",findLumi->second.weekDay);
                            }
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

PXL_MODULE_INIT(LumiInfo)
PXL_PLUGIN_INIT
