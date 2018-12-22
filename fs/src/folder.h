#ifndef FOLDER_H
#define FOLDER_H

#include "node.h"
#include "node_visitor.h"
#include "find_visitor.h"
#include "node_iterator.h"
#include <sys/stat.h>
#include <cstddef>
#include <iostream>
#include <map>
#include <sys/stat.h>
#include <utility>
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
      return _it->second;
    }

  private:
    Folder * _folder;
    std::map<std::string, Node*>::iterator _it;
  };

  Folder(const char* path) : Node(path){
    if(lstat(path, &_st) == 0)
      if (!S_ISDIR(_st.st_mode)) {
                throw std::string("path of constructor does not correspond.");
            }
  }

  void add(Node *node) {
    std::string fileName = node->name();
    _children.insert(std::make_pair(fileName, node));
    node->setParent(this);
  }

  int numberOfChildren() const {
    return _children.size();
  }

  void accept(NodeVisitor * nv) {
    nv->visitFolder(this);
  }

  NodeIterator * createIterator() {
    return new FolderIterator(this);
  }

private:
  std::map<std::string, Node *> _children;
  struct stat _st;
};

#endif
