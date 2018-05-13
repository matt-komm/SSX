#include "RootTree.hpp"

RootTree::RootTree(std::shared_ptr<TFile>& file, std::string name):
    _file(file),
    _count(0),
    _logger("Tree")
{
    _tree = new TTree(name.c_str(),name.c_str());
    _tree->SetDirectory(file.get());
    //_tree-> SetAutoFlush(-50000000);
    //_tree->SetAutoSave(-50000000); //50MB instead of default 300MB
    
    _tree->SetAutoFlush(5000);
    _tree->SetAutoSave(5000); //5000 events instead of default 300MB
}


void RootTree::fill()
{
    ++_count;
    _tree->Fill();
    resetVariables();
}

void RootTree::resetVariables()
{
    for (auto it = _variables.begin(); it!=_variables.end(); ++it)
    {
        //std::cout<<it->first<<": "<<it->second->isDirty()<<std::endl;
        it->second->reset();
    }
    //std::cout<<std::endl;
}

void RootTree::write()
{
    _tree->Write();
}

