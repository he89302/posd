#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/findvisitor.h"
#include "../src/node_iterator.h"
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

TEST (Find, FileSearchItsSelf)
{
  Node * a_out = new File("./test_data/folder/a.out");
  FindVisitor * fv = new FindVisitor("a.out");
  a_out->accept(fv);
  ASSERT_EQ("a.out",fv->getContentPath());
}
TEST (Find, FileSearchNotItsSelf)
{
  Node * a_out = new File("./test_data/folder/a.out");
  FindVisitor * fv = new FindVisitor("b.out");
  a_out->accept(fv);
  ASSERT_EQ("",fv->getContentPath());
}
TEST (Find, FolderSearchItsSelf)
{
  Node * folder = new Folder("./test_data/folder");
  FindVisitor * fv = new FindVisitor("folder");
  folder->accept(fv);
  ASSERT_EQ("",fv->getContentPath());
}
TEST (Find, FolderSearchNotItsSelf)
{
  Node * folder = new Folder("./test_data/folder");
  FindVisitor * fv = new FindVisitor("test_data");
  folder->accept(fv);
  ASSERT_EQ("",fv->getContentPath());
}

TEST (Find, SearchFileInFolder)
{
  Node * folder = new Folder("./test_data/folder");
  Node * a_out = new File("./test_data/folder/a.out");
  folder->add(a_out);
  FindVisitor * fv = new FindVisitor("a.out");
  folder->accept(fv);
  ASSERT_EQ("./a.out", fv->getContentPath());
}

TEST (Find, SearchFolderInFolder)
{
  Node * test_data = new Folder ("./test_data");
  Node * folder = new Folder("./test_data/folder");
  test_data->add(folder);
  FindVisitor * fv = new FindVisitor("folder");
  test_data->accept(fv);
  ASSERT_EQ("./folder",fv->getContentPath());
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
  FindVisitor * fv = new FindVisitor("a.out");
  test_data->accept(fv);
  ASSERT_EQ("./a.out\n./folder/a.out\n./folder/folder/a.out",fv->getContentPath());
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
  FindVisitor * fv = new FindVisitor("folder");
  test_data->accept(fv);
  ASSERT_EQ("./folder\n./folder/folder",fv->getContentPath());
}

// TEST (FileSystemTest, Visitor)
// {
//   File * a_out = new File("./test_data/folder/a.out");
//   InfoContentVisitor * icv = new InfoContentVisitor();
//   a_out->accept1(icv);
//   ASSERT_EQ(8432, icv->getContentSize());
// }
//
// TEST (FolderSystemTest, Visitor)
// {
//   Folder * folder = new Folder("./test_data/folder");
//   File * a_out = new File("./test_data/folder/a.out");
//   InfoContentVisitor * icv = new InfoContentVisitor();
//   folder->add(a_out);
//   folder->accept1(icv);
//   ASSERT_EQ(8432, icv->getContentSize());
// }

  TEST (FolderSystemTest, Iterator) {
    Folder * test_data = new Folder("./test_data");
    Folder * folder = new Folder("./test_data/folder");
    File * a_out = new File("./test_data/folder/a.out");
    File * hello_cpp = new File("./test_data/hello.cpp");
    folder->add(a_out);
    test_data->add(folder);
    test_data->add(hello_cpp);
    NodeIterator * it = test_data->createIterator();
    it->first();
    ASSERT_EQ(96, it->currentItem()->size());
    it->next();
    ASSERT_EQ(83, it->currentItem()->size());
    it->next();
    ASSERT_TRUE(it->isDone());
    ASSERT_ANY_THROW(it->currentItem());
    ASSERT_ANY_THROW(it->next());
  }


#endif
