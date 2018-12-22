#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H
#include <string>
class File;
class Folder;
class Link;

class NodeVisitor {
public:
  virtual void visitFile(File *) = 0;
  virtual void visitFolder(Folder *) = 0;
  virtual void visitLink(Link *) = 0;
  virtual std::string findResult() {
    return "";
  }
  virtual int getContentSize() {
    return 0;
  }
  virtual ~ NodeVisitor() {

  }
};

#endif
