#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include "node.h"
#include "subject.h"
#include "node_iterator.h"
#include "node_builder.h"
#include <cstdio>

class FileSystem : public Subject {
public:
  FileSystem(Node * root) : _root(root) {
    NodeBuilder nb;
    const char * rootName = (_root->name()).c_str();
    nb.build(rootName);
    deepVisit(nb.getRoot());
  }



 void changeFileName(Node * node, std::string newNodeName) {
   char oldPath[1000];
   char newPath[1000];
   strcpy(oldPath, node->path().c_str());
   if(node->getParent() != nullptr) {
     strcpy(newPath, node->getParent()->path().c_str());
     strcat(newPath, "/");
     strcat(newPath, newNodeName.c_str());
   }else {
     strcpy(newPath, node->path().c_str());
   }

   if(std::rename(oldPath, newPath) < 0) {
     std::perror("Error renaming");
   }else
    std::cout << "OK" << '\n';
 }






private:
  Node * _root;

  void deepVisit(Node * node) {
    NodeIterator * it = node->createIterator();

    for(it->first(); !it->isDone(); it->next()) {
      //std::cout << it->currentItem()->path() << '\n';
      deepVisit(it->currentItem());
    }
 }
};
#endif
