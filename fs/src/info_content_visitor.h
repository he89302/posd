#ifndef INFO_CONTENT_VISITOR_H
#define INFO_CONTENT_VISITOR_H
#include "node_visitor.h"
class File;
class Folder;

class InfoContentVisitor:public NodeVisitor {
public:
  InfoContentVisitor();

  void visitFile(File *);
  void visitFolder(Folder *);
  void visitLink(Link *);

  int getContentSize() {
    return _size;
  }

private:
  int _size;
};
#endif
