#ifndef NOCK_TREE_VIEW
#define NOCK_TREE_VIEW
#include "subject.h"


class MockTreeView : public Observer {
public:
  MockTreeView(Subject * subject) : _fileSystem(subject) {
    _fileSystem->attach(this);
    updateTimes = 0;
  }

  int getUpdateTimes() {
    return updateTimes;
  }

  void update() {
    updateTimes++;
  }

private:
  Subject * _fileSystem;
  int updateTimes;
};

#endif
