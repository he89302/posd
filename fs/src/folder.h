#ifndef FOLDER_H
#define FOLDER_H

#include "node.h"
#include "info_content_visitor.h"
#include <sys/stat.h>
#include <cstddef>
#include <vector>
#include <string>
static int layer = 0;
static std::string foundPath = "";

 class Folder:public Node{
public:
  friend class InfoContentVisitor;

  Folder(const char* path):Node(path){}

  void add(Node *node) {
    _children.push_back(node);
  }

  int numberOfChildren() const {
    return _children.size();
  }

  // int infoContent() const {
  //   int sum = 0;
  //   for (int i = 0; i < _children.size(); i++)
  //   {
  //     sum += _children[i]->infoContent();
  //   }
  //   return sum;
  // }

  void collectFindPath(std::string nodeName) {
    for (int i = 0; i < _children.size(); i++) {
      layer++;
      if(_children[i]->name() == nodeName){
        foundPath.append(_children[i]->path());
        foundPath.append("\n");
      }
      _children[i]->find(nodeName);
      layer--;
    }
  }

  void eraseParentsPath(std::string parentsPath, std::size_t position) {
    while(foundPath.find(parentsPath) != std::string::npos) {
      foundPath.erase(foundPath.begin()+position, foundPath.begin()+position+parentsPath.length());
      position = foundPath.find(parentsPath);
    }
  }

  std::string find(std::string _nodeName) {
    std::string nodeName = _nodeName;
    bool isFound = false;

    if(layer == 0) {
      foundPath = "";
    }
    collectFindPath(nodeName);
    if(layer == 0) {
      std::string parentsPath = path();
      std::size_t found = parentsPath.find(".");
      parentsPath.assign(parentsPath.begin()+1, parentsPath.end());
      std::size_t position = foundPath.find(parentsPath);//紀錄"."之後目前父資料夾的路徑

      if(position == std::string::npos) {
        return "";
      }
      eraseParentsPath(parentsPath, position);
      foundPath.assign(foundPath.begin(), foundPath.end()-1);
     }
       return foundPath;
  }

  void accept(InfoContentVisitor * icv) {
    icv->visitFolder(this);
  }

private:
  std::vector<Node *> _children;
};

#endif
