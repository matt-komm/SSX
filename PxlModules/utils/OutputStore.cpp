#include "OutputStore.hpp"

OutputStore::OutputStore(const std::string& filename):
    _fileName(filename),
    _logger("OutputStore")
{
    _file.reset(new TFile(filename.c_str(),"RECREATE"));
}

RootTree* OutputStore::getTree(std::string treeName)
{
    if (!_file or !_file->IsOpen())
    {
        std::cout<<"Output file unexpectedly closed"<<std::endl;
        throw std::runtime_error("Output file unexpectedly closed");
    }
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
    _logger(pxl::LOG_LEVEL_INFO,"Closing file '",_fileName,"'");
    for (auto it = _treeMap.begin(); it != _treeMap.end(); ++it )
    {
        it->second->write();
        _logger(pxl::LOG_LEVEL_INFO,"Wrote tree '",it->first,"' with ",it->second->getEntries()," events");
    }
    
    _file->Close();
}



