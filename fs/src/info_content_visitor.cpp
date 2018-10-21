#include "info_content_visitor.h"
#include "file.h"
#include "folder.h"

InfoContentVisitor::InfoContentVisitor(): _size(0) {}

void InfoContentVisitor::visitFile(File * file) {
   _size+=file->size();
}

void InfoContentVisitor::visitFolder(Folder * folder) {
  for(int i=0;i < folder->numberOfChildren(); i++) {
    folder->_children[i]->accept(this);
  }
}
