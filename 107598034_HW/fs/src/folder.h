#ifndef FOLDER_H
#define FOLDER_H

#include "node.h"
#include "findvisitor.h"
#include "node_iterator.h"
#include <sys/stat.h>
#include <cstddef>
#include <vector>
#include <string>


 class Folder:public Node{
public:
  class FolderIterator:public NodeIterator {
  public:
    FolderIterator(Folder * folder) : _folder(folder) {

    }

    void first() {
      _it = _folder->_children.begin();
    }

    void next() {
      if(isDone()) {
        throw std::string("moving past the end");
      }
      _it++;
    }

    bool isDone() {
      return _it == _folder->_children.end();
    }

    Node * currentItem() {
      if(isDone()) {
        throw std::string("no current item");
      }
      return *_it;
    }

  private:
    Folder * _folder;
    std::vector<Node*>::iterator _it;
  };

  Folder(const char* path):Node(path){}

  void add(Node *node) {
    _children.push_back(node);
  }

  int numberOfChildren() const {
    return _children.size();
  }

  void accept(FindVisitor * fv) {
    fv->visitFindFolder(this);
  }

  NodeIterator * createIterator() {
    return new FolderIterator(this);
  }

private:
  std::vector<Node *> _children;
};

#endif
