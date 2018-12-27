#ifndef LINK_H
#define LINK_H
#include "node.h"
#include "node_visitor.h"
#include "node_iterator.h"
#include "null_iterator.h"

class Link:public Node {
public:
  Link(const char * path, Node * node = nullptr) : Node(path), _source(node){
    if(lstat(path, &_st) == 0)
      if (!S_ISLNK(_st.st_mode)) {
                throw std::string("path of constructor does not correspond.");
            }
  }

  void  accept(NodeVisitor * nv) {
    nv->visitLink(this);
  }

  Node * getSource() {
    return _source;
  }

  NodeIterator * createIterator() {
    return new NullIterator(this);
  }

private:
  Node * _source;
  struct stat _st;
};
#endif
