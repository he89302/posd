#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include "node.h"
#include "subject.h"
#include "node_iterator.h"
#include "node_builder.h"

class FileSystem : public Subject {
public:
  FileSystem(Node * root) : _root(root) {
    NodeBuilder nb;
    const char * rootName = (_root->name()).c_str();
    nb.build(rootName);
    deepVisit(nb.getRoot());
  }

  void deepVisit(Node * node) {
    NodeIterator * it = node->createIterator();

    for(it->first(); !it->isDone(); it->next()) {
      std::cout << it->currentItem()->name() << '\n';
      deepVisit(it->currentItem());
    }
 }






private:
  Node * _root;
};
#endif
