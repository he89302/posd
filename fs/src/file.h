#ifndef FILE_H
#define FILE_H

#include "node.h"
#include "node_visitor.h"
#include "find_visitor.h"
#include "node_iterator.h"
#include "null_iterator.h"
#include <map>
#include <sys/stat.h>
#include <string>

class File : public Node{
public:
  File(const char * path) : Node(path){
    if(lstat(path, &_st) == 0)
      if (!S_ISREG(_st.st_mode)) {
                throw std::string("path of constructor does not correspond.");
            }
  }

  void accept(NodeVisitor * nv) {
    nv->visitFile(this);
  }

  NodeIterator * createIterator() {
    return new NullIterator(this);
  }

private:
  struct stat _st;
};

#endif
