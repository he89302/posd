#ifndef FILE_H
#define FILE_H

#include "node.h"
#include "findvisitor.h"
//#include "info_content_visitor.h"
#include <string>

class File: public Node{
public:
  File(const char * path): Node(path){}

  std::string find(std::string nodeName) {

    std::string _path = name();
    std::size_t found = _path.find(nodeName);
    if(found!=std::string::npos) {
      return nodeName;
    }else {
      return "";
    }
    return name();
  }

  void accept(FindVisitor * fv) {
    fv->visitFindFile(this);
  }

};

#endif
