#ifndef NODE_BUILDER_H
#define NODE_BUILDER_H
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "find_link_visitor.h"
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>


class NodeBuilder{
public:
  NodeBuilder() {

  }

  void build(const char * path) {
    struct stat _st;
    if(lstat(path, &_st) == 0) {
      if(S_ISREG(_st.st_mode))
        _root = new File(path);
      else if(S_ISLNK(_st.st_mode)) {
        _root = new Link(path);
      }
      else if (S_ISDIR(_st.st_mode)) {
        _root = new Folder(path);
        DIR * dir = opendir(path);
        if (dir == nullptr)
          throw std::string("open folder error");

        struct dirent * entry = nullptr;
        while ((entry = readdir(dir)) != nullptr) {
          if(std::string(entry->d_name) != "." &&
              std::string(entry->d_name) != ".."){
              std::string findLinkPath = std::string(path) + "/" + std::string(entry->d_name);
              char * pathName = new char[findLinkPath.length()+1];
              strcpy(pathName, findLinkPath.c_str());
              NodeBuilder nb;
              nb.build(pathName);
              _root->add(nb.getRoot());
            }
        }
      }
    }
  }


  Node * getRoot() {
    return _root;
  }

private:
  Node * _root;
};

#endif
