#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "findvisitor.h"
#include "file.h"
#include "folder.h"
static int layer = 0;

FindVisitor::FindVisitor(std::string _nodeName):outputPath(""), nodeName(_nodeName) {}

void FindVisitor::visitFindFile(File * file) {
  std::string _path = file->name();
  std::size_t found = _path.find(nodeName);
  if(layer == 0) {
    if(found!=std::string::npos) {
      outputPath = file->name();
    }else {
      outputPath =  "";
    }
  }
}

void FindVisitor::visitFindFolder(Folder * folder) {
  bool isFound = false;
  if(layer == 0) {
    outputPath = "";
  }
  NodeIterator * it = folder->createIterator();
  for(it->first(); !it->isDone(); it->next()) {
    layer++;
    if(it->currentItem()->name() == nodeName) {
      outputPath.append(it->currentItem()->path());
      outputPath.append("\n");
    }
    it->currentItem()->accept(this);
    layer--;
  }

  if(layer == 0) {
    std::string parentsPath = folder->path();
    std::size_t found = parentsPath.find(".");
    parentsPath.assign(parentsPath.begin()+1, parentsPath.end());
    std::size_t position = outputPath.find(parentsPath);//紀錄"."之後目前父資料夾的路徑
    if(position != std::string::npos) {
      while(outputPath.find(parentsPath) != std::string::npos) {
        outputPath.erase(outputPath.begin()+position, outputPath.begin()+position+parentsPath.length());
        position = outputPath.find(parentsPath);
      }
      outputPath.assign(outputPath.begin(), outputPath.end()-1);
     }
    }
}
