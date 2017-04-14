#include "OutputStore.hpp"

OutputStore::OutputStore(std::string filename):
    _logger("OutputStore")
{
    _file = new TFile(filename.c_str(),"RECREATE");
}

RootTree* OutputStore::getTree(std::string treeName)
{
    auto elem = _treeMap.find(treeName.c_str());
    if (elem==_treeMap.end())
    {
        _logger(pxl::LOG_LEVEL_DEBUG,"create new tree: ",treeName);
        _treeMap[treeName].reset(new RootTree(_file, treeName));
        return _treeMap[treeName].get();
    } else {
        return elem->second.get();
    }
}

void OutputStore::close()
{
    _file->cd();
    for (auto it = _treeMap.begin(); it != _treeMap.end(); ++it )
    {
        it->second->write();
    }
    _file->Close();
}



