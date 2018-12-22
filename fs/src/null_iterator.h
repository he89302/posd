#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include <string>
#include "node_iterator.h"
#include "file.h"

class NullIterator:public NodeIterator {
public:
  NullIterator(Node * file) : _file(file) {}

  void first() {

  }

  void next() {
  
  }

  bool isDone() {
    return true;
  }

  Node * currentItem() {
    return nullptr;
  }

private:
  Node * _file;
};

#endif
