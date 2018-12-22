#ifndef FIND_NODE_BY_PATHNAME_VISISTOR
#define FIND_NODE_BY_PATHNAME_VISISTOR
#include <vector>
#include <string>
#include "node_visitor.h"

class Node;
class Folder;
class File;
class Link;

class FindNodeByPathnameVisitor : public NodeVisitor{
  public:
      FindNodeByPathnameVisitor(std::vector<std::string>* pathnames);
      void visitFolder(Folder * folder);
      void visitFile(File * file);
      void visitLink(Link * link);

      Node * getNode() const {
        if(object != nullptr)
          return object;
        else
          return nullptr;
      }
      //return the Node object if the path indicate the node in the file system, and if not, return nullptr.

  private:
    Node * object;
    std::vector<std::string>* _pathnames;
    int _layer;
};

#endif
