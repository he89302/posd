#ifndef FINDVISITOR
#define FINDVISITOR
#include <string>
#include "node_visitor.h"
class File;
class Folder;
class Link;

class FindVisitor:public NodeVisitor {
public:
  FindVisitor(std::string _nodeName);

  void visitFile(File * file);
  void visitFolder(Folder * folder);
  void visitLink(Link * link);

  std::string findResult() {
    return outputPath;
  }

private:
  std::string nodeName;
  std::string outputPath;
};
#endif
