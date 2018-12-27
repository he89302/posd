#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include "node.h"
#include "subject.h"
#include "node_iterator.h"
#include "node_builder.h"
#include <cstdio>
#include <sys/stat.h>
#include <fstream>

class FileSystem : public Subject {
public:
  FileSystem(Node * root) : _root(root) {
    NodeBuilder nb;
    const char * rootName = (_root->name()).c_str();
    nb.build(rootName);
    deepVisit(nb.getRoot());
  }

 void changeFileName(Node * node, std::string newNodeName) {
   char newPath[10000];
   char oldPath[10000];
   std::string oldTempPath = node->path();
   strcpy(oldPath, oldTempPath.c_str());
   if(node->getParent() != nullptr) {
     std::string newTempPath = node->getParent()->path();
     strcpy(newPath, newTempPath.c_str());
     strcat(newPath, "/");
     strcat(newPath, newNodeName.c_str());
   }else {
     strcpy(newPath, newNodeName.c_str());
   }
   std::rename(oldPath, newPath);
 }

 bool isContentBinary(std::string path) {
   int c;
   std::ifstream is(path);
   while ((c = is.get()) != EOF && c <= 127);
   return c != EOF;
 }

 int isType(std::string path) {
   const char * _path = path.c_str();
   if(lstat(_path, &_st) == 0) {
     if(S_ISLNK(_st.st_mode))
      return 1;
      else if(S_ISREG(_st.st_mode))
         return 2;
      else if(S_ISDIR(_st.st_mode))
         return 3;
   }
 }

 int fileSize(const char * filePath) {
   if(lstat(filePath, &_st) == 0) {
     return _st.st_size;
   }
 }

private:
  Node * _root;
  struct stat _st;
  void deepVisit(Node * node) {
    NodeIterator * it = node->createIterator();
    for(it->first(); !it->isDone(); it->next()) {
      deepVisit(it->currentItem());
    }
 }
};
#endif
