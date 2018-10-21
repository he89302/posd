#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/info_content_visitor.h"
#include <string>


TEST (FileAdd, FileException) {
  Node * folder = new Folder("./test_data/folder");
  Node * a_out = new File("./test_data/folder/a.out");
  try {
    a_out->add(folder);
  }catch(const std::string &e) {
    EXPECT_EQ("unable to add", e);
  }

  try {
    a_out->numberOfChildren();
  }catch(const std::string &e1) {
    EXPECT_EQ("number of children: not applicable", e1);
  }
}

// TEST (FileSystemTest, InfoContent)
// {
//   Node * a_out = new File("./test_data/folder/a.out");
//   ASSERT_EQ(8432, a_out->infoContent());
//   Node * hello_cpp = new File("./test_data/hello.cpp");
//   ASSERT_EQ(83, hello_cpp->infoContent());
//   Node * folder = new Folder("./test_data/folder");
//   folder->add(a_out);
//   ASSERT_EQ(8432, folder->infoContent());
//   Node * test_data = new Folder("./test_data");
//   test_data->add(folder);
//   test_data->add(hello_cpp);
//   ASSERT_EQ(8515, test_data->infoContent());
// }

TEST (Find, FileSearchItsSelf)
{
  Node * a_out = new File("./test_data/folder/a.out");
  ASSERT_EQ("a.out",a_out->find("a.out"));
}
TEST (Find, FileSearchNotItsSelf)
{
  Node * a_out = new File("./test_data/folder/a.out");
  ASSERT_EQ("",a_out->find("b.out"));
}
TEST (Find, FolderSearchItsSelf)
{
  Node * folder = new Folder("./test_data/folder");
  ASSERT_EQ("",folder->find("folder"));
}
TEST (Find, FolderSearchNotItsSelf)
{
  Node * folder = new Folder("./test_data/folder");
  ASSERT_EQ("",folder->find("test_data"));
}

TEST (Find, SearchFileInFolder)
{
  Node * folder = new Folder("./test_data/folder");
  Node * a_out = new File("./test_data/folder/a.out");
  folder->add(a_out);
  ASSERT_EQ("./a.out",folder->find("a.out"));
}

TEST (Find, SearchFolderInFolder)
{
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder("./test_data/folder");
  test_data->add(folder);
  ASSERT_EQ("./folder",test_data->find("folder"));
}

TEST (Find, SearchSameFile)
{
  Node * test_data = new Folder ("./test_data");
  Node * folder1 = new Folder("./test_data/folder");
  Node * folder2 = new Folder("./test_data/folder/folder");
  Node * a_out1 = new Folder("./test_data/a.out");
  Node * a_out2 = new Folder("./test_data/folder/a.out");
  Node * a_out3 = new Folder("./test_data/folder/folder/a.out");
  folder2->add(a_out3);
  folder1->add(a_out2);
  folder1->add(folder2);
  test_data->add(a_out1);
  test_data->add(folder1);
  ASSERT_EQ("./a.out\n./folder/a.out\n./folder/folder/a.out",test_data->find("a.out"));
}

TEST (Find, SearchSameFolder)
{
  Node * test_data = new Folder ("./test_data");
  Node * folder1 = new Folder("./test_data/folder");
  Node * folder2 = new Folder("./test_data/folder/folder");
  Node * a_out1 = new Folder("./test_data/a.out");
  Node * a_out2 = new Folder("./test_data/folder/a.out");
  Node * a_out3 = new Folder("./test_data/folder/folder/a.out");
  folder2->add(a_out3);
  folder1->add(a_out2);
  folder1->add(folder2);
  test_data->add(a_out1);
  test_data->add(folder1);
  ASSERT_EQ("./folder\n./folder/folder",test_data->find("folder"));
}

TEST (FileSystemTest, Visitor)
{
  File * a_out = new File("./test_data/folder/a.out");
  InfoContentVisitor * icv = new InfoContentVisitor();
  a_out->accept(icv);
  ASSERT_EQ(8432, icv->getContentSize());
}

TEST (FolderSystemTest, Visitor)
{
  Folder * folder = new Folder("./test_data/folder");
  File * a_out = new File("./test_data/folder/a.out");
  InfoContentVisitor * icv = new InfoContentVisitor();
  folder->add(a_out);
  folder->accept(icv);
  ASSERT_EQ(8432, icv->getContentSize());
}


#endif
