#ifndef _OUTPUTSTORE_H_
#define _OUTPUTSTORE_H_

#include <pxl/core.hh>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include <TBranch.h>

#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>

#include "RootTree.hpp"


class OutputStore
{

    private:
        TFile* _file;
        std::unordered_map<std::string,std::shared_ptr<RootTree>> _treeMap;
        pxl::Logger _logger;
    public:
        OutputStore(std::string filename);
        ~OutputStore();
        RootTree* getTree(std::string treeName);
        void close();
};

#endif
