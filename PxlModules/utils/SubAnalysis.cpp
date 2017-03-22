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
                    std::cout<<"connecting events"<<std::endl;
                    _exit->setTargets(sink->get());
                    return _exit->processTargets();
                }
        };

    private:
        std::string _xmlFile;
        
        pxl::Source* _outputSource;
        
        std::shared_ptr<pxl::Analysis> _subAnalysis;
        pxl::InputModule* _entryModule;
        pxl::OutputModule* _exitModule;
        
        std::shared_ptr<ConnectorModule> _connectorModule;
        
        std::vector<pxl::Module*> _initModules;
        
    public:
        SubAnalysis():
            Module(),
            _xmlFile(""),
            _subAnalysis(nullptr),
            _entryModule(nullptr),
            _exitModule(nullptr),
            _connectorModule(nullptr)
        {
            addSink("input", "input");
            _outputSource = addSource("output","output");
            
            addOption("analysis file","",_xmlFile,pxl::OptionDescription::USAGE_FILE_OPEN);
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
            getOption("analysis file",_xmlFile);
            pxl::AnalysisXmlImport analysisImporter;
            analysisImporter.open(_xmlFile);
            _subAnalysis.reset(new pxl::Analysis());
            analysisImporter.parseInto(_subAnalysis.get());
            analysisImporter.close();
            const std::vector<Module*>& moduleList = _subAnalysis->getModules();
            for (Module* module: moduleList)
            {
                pxl::InputModule* posssibleEntryModule = dynamic_cast<pxl::InputModule*>(module);
                pxl::OutputModule* posssibleExitModule = dynamic_cast<pxl::OutputModule*>(module);
                if (posssibleEntryModule!=nullptr)
                {
                    if (_entryModule!=nullptr)
                    {
                        throw std::runtime_error(getName()+": detected multiple InputModules in sub analysis '"+_xmlFile+"'.");
                    }
                    _entryModule = posssibleEntryModule;
                }
                else if (module->getName().find("EXIT")!=std::string::npos)
                {

                    if (posssibleExitModule!=nullptr)
                    {
                        if (_exitModule!=nullptr)
                        {
                            throw std::runtime_error(getName()+": detected multiple OutputModules in sub analysis '"+_xmlFile+"'.");
                        }
                        _exitModule = posssibleExitModule;
                    }
                }
                else
                {
                    module->beginJob();
                    _initModules.push_back(module);
                }
            }
            if (_entryModule==nullptr)
            {
                throw std::runtime_error(getName()+": detected no InputModule in sub analysis '"+_xmlFile+"'.");
            }
            if (_exitModule!=nullptr)
            {
                _connectorModule.reset(new ConnectorModule(_outputSource));
                pxl::Sink* sink = _exitModule->getSink("in");
                sink->setModule(_connectorModule.get());
            }
        }

        bool analyse(pxl::Sink *sink) throw (std::runtime_error)
        {
            try
            {
                std::cout<<"start sub module"<<std::endl;
                pxl::Source* source = _entryModule->getSource("out");
                source->setTargets(sink->get());
                bool success = source->processTargets();
                std::cout<<"end sub module"<<std::endl;
                return success;
                
               // pxl::Event *event  = dynamic_cast<pxl::Event*>(sink->get());
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
        
        void endJob()
        {
            for (pxl::Module* module: _initModules)
            {
                module->endJob();
            }
        }

        void shutdown() throw(std::runtime_error)
        {
            for (pxl::Module* module: _initModules)
            {
                module->shutdown();
            }
        }

        void destroy() throw (std::runtime_error)
        {
            delete this;
        }
};

PXL_MODULE_INIT(SubAnalysis)
PXL_PLUGIN_INIT
