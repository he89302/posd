#ifndef INFO_CONTENT_VISITOR
#define INFO_CONTENT_VISITOR
class File;
class Folder;

class InfoContentVisitor{
public:
  InfoContentVisitor();

  void visitFile(File * file);
  void visitFolder(Folder * folder);

  int getContentSize() {
    return _size;
  }

private:
  int _size;
};

#endif
