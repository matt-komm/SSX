#include "tinyxml2.h"
#include "TMVA/Reader.h"
#include "argparse.h"

#include "TFile.h"
#include "TTree.h"
#include "TKey.h"
#include "TList.h"
#include "TLeaf.h"
#include "TObject.h"

#include "Variable.hpp"

#include <memory>
#include <vector>
#include <set>


class TreeAccess
{
    private:
        TTree* _tree;
        
        std::unordered_map<std::string,std::shared_ptr<Variable>> _variables;
        unsigned int _currentEntry;
    public:
        TreeAccess(TTree* tree):
            _tree(tree),
            _currentEntry(0)
        {
        }
        
        void getEntry(unsigned int i)
        {
            _currentEntry = i;
            _tree->GetEntry(_currentEntry);
        }
        
        float getVar(const std::string& name)
        {
            auto it = _variables.find(name);
            if (it==_variables.end())
            {
                TLeaf* leaf = _tree->GetLeaf(name.c_str());
                std::string leafType = leaf->GetTypeName();
                if (leafType=="Float_t")
                {
                    _variables[name]=std::shared_ptr<Variable>(new VariableTmpl<float>());
                }
                else if (leafType=="Int_t")
                {
                    _variables[name]=std::shared_ptr<Variable>(new VariableTmpl<float>());
                }
                else
                {
                    throw std::runtime_error("Unknown leaf type: "+std::string(leaf->GetTypeName()));
                }
                _tree->SetBranchAddress(name.c_str(),_variables[name]->getAddress());
                _tree->GetEntry(_currentEntry);
            }
            return _variables[name]->toFloat();
        }
        
        
};

class MVASetup
{
    private:
        std::string _fileName;
        std::string _methodName;
        std::vector<std::pair<std::string,std::shared_ptr<float>>> _variables;
        std::shared_ptr<TMVA::Reader> _reader;
        float _mvaOut;
    
    public:
        void setFileName(std::string fileName)
        {
            _fileName=fileName;
        }
        
        const std::string& getName() const
        {
            return _methodName;
        }
        
        void setMethodName(std::string methodName)
        {
            _methodName=methodName;
        }
    
        void addVariable(std::string exp)
        {
            _variables.emplace_back(std::make_pair(exp,std::shared_ptr<float>(new float(0))));
        }
        
        void initReader()
        {
            _reader.reset(new TMVA::Reader(""));
            for (std::pair<std::string,std::shared_ptr<float>>& varPair: _variables)
            {
                _reader->AddVariable(varPair.first,varPair.second.get());
            }
            _reader->BookMVA(_methodName,_fileName);
        }
        
        void setupBranch(TTree* outTree)
        {
            outTree->Branch(_methodName.substr(_methodName.find("::")+2).c_str(),&_mvaOut);
        }
        
        void process(TreeAccess* treeAccess)
        {
            for (unsigned int i = 0; i < _variables.size(); ++i)
            {
                *_variables[i].second = treeAccess->getVar(_variables[i].first);
            }
            _mvaOut = _reader->EvaluateMVA(_methodName.c_str());
        }
};

int main(int argc, const char** argv)
{
    using namespace tinyxml2;
    ArgumentParser parser;

    parser.addArgument("-f","--file",1,true);
    parser.addArgument("-i", '+');
    
    parser.addFinalArgument("output");

    parser.parse(argc, argv);
    
    std::vector<MVASetup> mvaSetups;
    
    std::string rootFile = parser.retrieve<std::string>("file");
    std::cout<<"root file: "<<rootFile<<std::endl;

    std::vector<std::string> inputs = parser.retrieve<std::vector<std::string>>("i");
    for (auto inputFile: inputs)
    {
        std::cout<<"reading: "<<inputFile<<std::endl;
        XMLDocument doc;
        
        MVASetup setup;
        setup.setFileName(inputFile);
        
	    doc.LoadFile(inputFile.c_str());
	    XMLElement* root = doc.RootElement();
	    
	    std::string methodName = root->Attribute("Method");
	    setup.setMethodName(methodName);
	    std::cout<<"\tMethod="<<methodName<<std::endl;
	    
	    
	    XMLElement* variableNode = root->FirstChildElement("Variables");
	    int nvar = std::atoi(variableNode->Attribute("NVar"));
	    std::cout<<"\tNvar="<<nvar<<std::endl;
	    
	    for (const XMLElement* varElem = variableNode->FirstChildElement("Variable"); varElem!=0; varElem=varElem->NextSiblingElement("Variable"))
	    {
	        std::string varExp = varElem->Attribute("Expression");
	        setup.addVariable(varExp);
	        std::cout<<"\tvar"<<varElem->Attribute("VarIndex")<<"="<<varExp<<std::endl;
	    }
	    mvaSetups.push_back(setup);
	    std::cout<<std::endl;
    }
    std::cout<<"read "<<mvaSetups.size()<<" mva setups"<<std::endl;
    
    std::string outFileName = parser.retrieve<std::string>("output");
    std::cout<<"write result to file: "<<outFileName<<std::endl;
    
    
    for (MVASetup& setup: mvaSetups)
    {
        setup.initReader();
    }
    
    TFile inputFile(rootFile.c_str());
    TFile outputFile(outFileName.c_str(),"RECREATE");
    TList* keyList = inputFile.GetListOfKeys();
    TIterator* it = keyList->MakeIterator();
    TObject* obj;
    std::set<std::string> keys;
    while(obj= it->Next())
    {
        keys.insert(((TKey*)obj)->GetName());
    }
    
    for (std::string key: keys)
    {
        std::cout<<"processing tree: "<<key<<std::endl;
        TTree treeOut(key.c_str(),key.c_str());
        treeOut.SetDirectory(&outputFile);
        
        TTree* treeIn = dynamic_cast<TTree*>(inputFile.Get(key.c_str()));
        if (!treeIn)
        {
            throw std::runtime_error("Cannot read input tree '"+key+"' from file '"+rootFile+"'"); 
        }
        
        for (MVASetup& setup: mvaSetups)
        {
            setup.setupBranch(&treeOut);
        }
        
        TreeAccess treeAccess(treeIn);
        for (unsigned int entry = 0; entry < treeIn->GetEntries(); ++entry)
        {
            treeAccess.getEntry(entry);
            for (MVASetup& setup: mvaSetups)
            {
                setup.process(&treeAccess);
            }
            treeOut.Fill();
        }
        treeOut.Write(key.c_str());
    }
    
    outputFile.Close();
    inputFile.Close();
    
    return 0;
}
