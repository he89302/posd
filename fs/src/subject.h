#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <algorithm>
#include "observer.h"
class Node;

class Subject {
public:
  void attach(Observer * ob) {
    _observer.push_back(ob);
  }

  int getNumberOfObservers() {
    return _observer.size();
  }

  void detach(Observer * ob) {
    std::vector<Observer *>::iterator it;
    it = _observer.begin();
    for( ; it != _observer.end();) {
      if((*it) == ob)
        _observer.erase(it);
      else
       ++it;
    }
  }

  void notify() {
    std::vector<Observer *>::iterator _it;
    for(_it = _observer.begin(); _it != _observer.end(); _it++) {
      (*_it)->update();
    }
  }

  virtual void changeFileName(Node * node, std::string newLabel) = 0;

private:
  std::vector<Observer *> _observer;
};
#endif
