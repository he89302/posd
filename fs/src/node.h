#ifndef NODE_H
#define NODE_H
#include <sys/stat.h>
#include <string>
class InfoContentVisitor;

using namespace std;

class Node
{
public:
  Node(const char * path): _path(path){
    lstat(_path, &_st);
  }

  int size() const{
    return _st.st_size;
  }

  virtual void accept(InfoContentVisitor * icv) = 0;

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

  virtual std::string find(std::string nodeName)
  {
      return "";
  }

  virtual std::string path() {
    return _path;
  }

private:
  const char * _path;
  struct stat _st;
};

#endif
