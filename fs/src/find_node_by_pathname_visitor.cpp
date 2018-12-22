#include "find_node_by_pathname_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_iterator.h"
#include <vector>
#include <memory>
#include <string>

FindNodeByPathnameVisitor::FindNodeByPathnameVisitor(std::vector<std::string>* pathnames):_pathnames(pathnames), object(nullptr), _layer(0) {}

bool travelPathIsDone(int layer, int pathLength) {
  if(layer >= pathLength) {
    return true;
  }else
    return false;
}

void FindNodeByPathnameVisitor::visitFolder(Folder * folder) {
  if(travelPathIsDone(_layer, _pathnames->size()))
    return;

  if(folder->name() == (*_pathnames)[_layer]) {
    if(_layer > 0)
      if(folder->getParent()->name() != (*_pathnames)[_layer-1])
        return;
      object = folder;
  } else if(folder->getParent() == object)
      object = nullptr;

  std::unique_ptr<NodeIterator>it(folder->createIterator());
    for(it->first(); !it->isDone(); it->next()) {
      _layer++;
      it->currentItem()->accept(this);
      _layer--;
    }
}

void FindNodeByPathnameVisitor::visitFile(File * file) {
  if(travelPathIsDone(_layer, _pathnames->size()))
    return;

  if(file->name() == (*_pathnames)[_layer]) {
    if(_layer > 0)
      if(file->getParent()->name() != (*_pathnames)[_layer-1])
        return;
      object = file;
  }
}

void FindNodeByPathnameVisitor::visitLink(Link * link) {
  if(travelPathIsDone(_layer, _pathnames->size()))
    return;

  if(link->name() == (*_pathnames)[_layer]) {
    if(_layer > 0)
      if(link->getParent()->name() != (*_pathnames)[_layer-1])
        return;
      object = link;
  }
}
