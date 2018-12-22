#ifndef NODE_H
#define NODE_H
#include <sys/stat.h>
#include <string>
#include "node_iterator.h"
class NodeVisitor;

using namespace std;

class Node
{
public:
  Node(const char * path): _path(path), parentNode(nullptr){
    if(lstat(_path, &_st) != 0)
      throw std::string("error");
  }

  int size() const{
    return _st.st_size;
  }

  virtual NodeIterator * createIterator() {
    return nullptr;
  }

  virtual void accept(NodeVisitor * nv) = 0;

  virtual int infoContent() const
  {
    return size();
  }

  virtual void add(Node *node)
  {
    throw std::string("unable to add");
  }

  virtual int numberOfChildren() const
  {
    throw std::string("number of children: not applicable");
  }

  virtual  std::string name()
  {
      std::string getPath = _path;
      std::size_t found = getPath.find_last_of("/");
      return getPath.substr(found+1, getPath.length());
  }

  virtual std::string find(std::string nodeName) { return "";}

  virtual std::string path() {
    return _path;
  }

  virtual std::string parentName(std::string path) {
    std::string getPath = path;
    std::size_t found = getPath.find_first_of("/");
    return getPath.substr(0, found);
  }

  virtual Node * getParent() const{
    return parentNode;
 }

 virtual void setParent (Node * p){
    parentNode = p;
 }


  virtual ~Node() {

  }

private:
  const char * _path;
  struct stat _st;
  Node * parentNode;
};

#endif
