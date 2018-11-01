#ifndef FINDVISITOR
#define FINDVISITOR
#include <string>
class File;
class Folder;

class FindVisitor {
public:
  FindVisitor(std::string _nodeName);

  void visitFindFile(File * file);
  void visitFindFolder(Folder * folder);

  std::string getContentPath() {
    return outputPath;
  }

private:
  std::string nodeName;
  std::string outputPath;
};
#endif
