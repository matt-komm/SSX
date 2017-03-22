#include "pxl/hep.hh"
#include "pxl/core.hh"
#include "pxl/xml.hh"
#include "pxl/core/macros.hh"
#include "pxl/core/PluginManager.hh"
#include "pxl/modules/Module.hh"
#include "pxl/modules/ModuleFactory.hh"
#include "pxl/modules/InputModule.hh"
#include "pxl/modules/OutputModule.hh"

#include <string>
#include <random>
#include <regex>
#include <unordered_map>

static pxl::Logger logger("SubAnalysis");


class SubAnalysis:
    public pxl::Module
{
    public:
        class ConnectorModule:
            public Module
        {
            private:
                pxl::Source* _exit;
            public:
                ConnectorModule(pxl::Source* exit):
                    _exit(exit)
                {
                }
                
                virtual bool analyse(pxl::Sink *sink)
                {
                    //std::cout<<"connecting events"<<std::endl;
                    _exit->setTargets(sink->get());
                    return _exit->processTargets();
                }
        };

    private:
        std::string _xmlFile;
        
        
        std::shared_ptr<pxl::Analysis> _subAnalysis;
        
        std::unordered_map<pxl::Sink*,pxl::InputModule*> _inputModules;
        std::unordered_map<std::string,std::shared_ptr<ConnectorModule>> _connectorOutputModules;
        
        std::vector<pxl::Module*> _initModules;
        
    public:
        SubAnalysis():
            Module(),
            _xmlFile(""),
            _subAnalysis(nullptr)
        {

        }

        ~SubAnalysis()
        {
        }

        // every Module needs a unique type
        static const std::string &getStaticType()
        {
            static std::string type ("SubAnalysis");
            return type;
        }

        // static and dynamic methods are needed
        const std::string &getType() const
        {
            return getStaticType();
        }
        
        virtual void initialize()
        {
            addOption("analysis file","",_xmlFile,pxl::OptionDescription::USAGE_FILE_OPEN);

            
            _subAnalysis.reset();
            _inputModules.clear();
            _connectorOutputModules.clear();
            _initModules.clear();
            

            
            getOption("analysis file",_xmlFile);
            _xmlFile = getAnalysis()->findFile(_xmlFile);
            
            logger(pxl::LOG_LEVEL_INFO,"Xml file: ",_xmlFile);
            
            pxl::AnalysisXmlImport analysisImporter;
            if (!analysisImporter.open(_xmlFile))
            {
                return;
            }
            _subAnalysis.reset(new pxl::Analysis());
            _subAnalysis->addSearchPath(_xmlFile.substr(0,_xmlFile.rfind("/")));
            logger(pxl::LOG_LEVEL_INFO,"Search path: ",_xmlFile.substr(0,_xmlFile.rfind("/")));
            analysisImporter.parseInto(_subAnalysis.get());
            analysisImporter.close();
            const std::vector<Module*>& moduleList = _subAnalysis->getModules();
            for (Module* module: moduleList)
            {
                //map only in/out modules which have not INGORE written in their name

                pxl::InputModule* posssibleEntryModule = dynamic_cast<pxl::InputModule*>(module);
                pxl::OutputModule* posssibleExitModule = dynamic_cast<pxl::OutputModule*>(module);
                if (posssibleEntryModule!=nullptr and (module->getName().find("IGNORE")==std::string::npos))
                {
                    pxl::Sink* sink = addSink(module->getName(),module->getName());
                    _inputModules[sink] = posssibleEntryModule;
                    
                }
                else if (posssibleExitModule!=nullptr and (module->getName().find("IGNORE")==std::string::npos))
                {
                    pxl::Source* outSource = addSource(module->getName(),module->getName());
                    _connectorOutputModules[module->getName()] = std::make_shared<ConnectorModule>(
                        outSource
                    );
                    module->getSink("in")->setModule(_connectorOutputModules[module->getName()].get());
                }

                else
                {
                    
                    _initModules.push_back(module);
                }
                
            }
            Module::initialize();
        }

        virtual bool isRunnable() const
        {
            // this module does not provide events, so return false
            return false;
        }

        virtual void beginJob() throw (std::runtime_error)
        {
            for (pxl::Module* module: _initModules)
            {
                module->beginJob();
            }
        }
        
        virtual void beginRun()
        {
            for (pxl::Module* module: _initModules)
            {
                module->beginRun();
                /*
                std::cout<<"Module: "<<module->getName()<<std::endl;
                const std::vector<pxl::OptionDescription>& opDesc = module->getOptionDescriptions();
                for (pxl::OptionDescription op: opDesc)
                {
                    if (op.type==pxl::OptionDescription::TYPE_STRING)
                    {
                        std::string value;
                        module->getOption(op.name,value);
                        std::cout<<"  "<<op.name<<": "<<value<<std::endl;
                    }
                    
                }
                */
            }
            
        }

        virtual bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                //std::cout<<"start sub module"<<std::endl;
                pxl::InputModule* entryModule = _inputModules[sink];
                pxl::Source* source = entryModule->getSource("out");
                source->setTargets(sink->get());
                bool success = source->processTargets();
                return success;
                
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
        
        virtual void endJob()
        {
            for (pxl::Module* module: _initModules)
            {
                module->endJob();
            }
        }
        
        virtual void endRun()
        {
            for (pxl::Module* module: _initModules)
            {
                module->endRun();
            }
        }

        virtual void shutdown() throw(std::runtime_error)
        {
            for (pxl::Module* module: _initModules)
            {
                module->shutdown();
            }
        }

        virtual void destroy() throw (std::runtime_error)
        {
            delete this;
        }
        
        virtual void setOption(const std::string &name, const std::string &value)
        {
	        Module::setOption(name, value);
	        if (name == "analysis file")
	        {
		        reload();
	        }
        }
};


PXL_MODULE_INIT(SubAnalysis)
PXL_PLUGIN_INIT
