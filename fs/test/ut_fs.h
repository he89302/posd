#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include <memory>
#include "../src/folder.h"
#include "../src/file.h"
#include "../src/link.h"
#include "../src/node_visitor.h"
#include "../src/find_visitor.h"
#include "../src/find_link_visitor.h"
#include "../src/info_content_visitor.h"
#include "../src/node_iterator.h"
#include "../src/null_iterator.h"
#include "../src/node_builder.h"
#include "../src/find_node_by_pathname_visitor.h"
#include <string>
#include <iostream>

TEST (MiscTest, lstatOnFolder)
{
  const char * path = "./test_data";
  struct stat st;
  ASSERT_EQ(0, lstat(path, &st));
  ASSERT_EQ(true, S_ISDIR(st.st_mode));
  ASSERT_EQ(false, S_ISREG(st.st_mode));
  ASSERT_EQ(false, S_ISLNK(st.st_mode));
}

class FileSystemTest: public ::testing::Test
{
protected:
  void SetUp() override
  {
    test_data = new Folder ("./test_data");
    folder = new Folder("./test_data/folder");
    hello_cpp = new File("./test_data/hello.cpp");
    a_out = new File("./test_data/folder/a.out");
    hello = new Link("./test_data/hello", a_out);
    folder->add(a_out);
    test_data->add(folder);
    test_data->add(hello);
    test_data->add(hello_cpp);
  }

  void TearDown() override
  {
    delete a_out;
    delete hello_cpp;
    delete hello;
    delete folder;
    delete test_data;
  }

  Node * test_data;
  Node * folder;
  Node * hello_cpp;
  Node * a_out;
  Node * hello;

};

TEST_F (FileSystemTest, FileException) {
  try {

  }catch(const std::string &e) {
    EXPECT_EQ("unable to add", e);
  }

  try {
    a_out->numberOfChildren();
  }catch(const std::string &e1) {
    EXPECT_EQ("number of children: not applicable", e1);
  }
}

TEST_F (FileSystemTest, FileSearchItsSelf) {
  NodeVisitor * fv = new FindVisitor("a.out");
  a_out->accept(fv);
  ASSERT_EQ("a.out",fv->findResult());
}

TEST_F (FileSystemTest, FileSearchNotItsSelf) {
  NodeVisitor * fv = new FindVisitor("b.out");
  a_out->accept(fv);
  ASSERT_EQ("",fv->findResult());
}

TEST_F (FileSystemTest, FolderSearchItsSelf) {
  NodeVisitor * fv = new FindVisitor("folder");
  folder->accept(fv);
  ASSERT_EQ("",fv->findResult());
}

TEST_F (FileSystemTest, FolderSearchNotItsSelf) {
  NodeVisitor * fv = new FindVisitor("test_data");
  folder->accept(fv);
  ASSERT_EQ("",fv->findResult());
}

TEST_F (FileSystemTest, SearchFileInFolder) {
  NodeVisitor * fv = new FindVisitor("a.out");
  folder->accept(fv);
  ASSERT_EQ("./a.out", fv->findResult());
}

TEST_F (FileSystemTest, SearchFolderInFolder) {
  NodeVisitor * fv = new FindVisitor("folder");
  test_data->accept(fv);
  ASSERT_EQ("./folder",fv->findResult());
}

TEST_F (FileSystemTest, SearchSameFile) {
  NodeVisitor * fv = new FindVisitor("a.out");
  test_data->accept(fv);
  ASSERT_EQ("./folder/a.out",fv->findResult());
}

TEST_F (FileSystemTest, SearchSameFolder) {
  NodeVisitor * fv = new FindVisitor("folder");
  test_data->accept(fv);
  ASSERT_EQ("./folder",fv->findResult());
}
//
// TEST_F (FileSystemTest, FileVisitor) {
//   NodeVisitor * icv = new InfoContentVisitor();
//   a_out->accept(icv);
//   ASSERT_EQ(8432, icv->getContentSize());
// }
//
// TEST_F (FileSystemTest, FolderVisitor) {
//   NodeVisitor * icv = new InfoContentVisitor();
//   folder->accept(icv);
//   ASSERT_EQ(8432, icv->getContentSize());
// }
//
// TEST_F (FileSystemTest, Iterator) {
//   std::unique_ptr<NodeIterator>it(test_data->createIterator());
//   it->first();
//   ASSERT_EQ(96, it->currentItem()->size());
//   it->next();
//   ASSERT_EQ(12, it->currentItem()->size());
//   it->next();
//   ASSERT_EQ(83, it->currentItem()->size());
//   it->next();
//   ASSERT_TRUE(it->isDone());
//   ASSERT_ANY_THROW(it->currentItem());
//   ASSERT_ANY_THROW(it->next());
// }

TEST_F (FileSystemTest, NullIterator) {
  std::unique_ptr<NodeIterator>it(hello_cpp->createIterator());
  ASSERT_TRUE(it->isDone());
  ASSERT_ANY_THROW(it->currentItem());
  ASSERT_ANY_THROW(it->first());
  ASSERT_ANY_THROW(it->next());
}

// TEST_F (FileSystemTest, Size)
// {
//   ASSERT_EQ(160,test_data->size());
//   ASSERT_EQ(96, folder->size());
//   ASSERT_EQ(83, hello_cpp->size());
//   ASSERT_EQ(8432, a_out->size());
//   ASSERT_EQ(12, hello->size());
//   ASSERT_EQ(8432, dynamic_cast<Link *>(hello)->getSource()->size());
//   ASSERT_EQ(3, test_data->numberOfChildren());
// }

// TEST_F (FileSystemTest, Visitor) {
//   InfoContentVisitor * icv10 = new InfoContentVisitor();
//   hello->accept(icv10);
//   ASSERT_EQ(8432,icv10->getContentSize());
// }

// TEST_F (FileSystemTest, NodeBuilderOnFile) {
//   NodeBuilder nb;
//   nb.build("test_data/hello.cpp");
//   ASSERT_EQ(83, nb.getRoot()->size());
// }
//
// TEST_F (FileSystemTest, NodeBuilderOnLink) {
//   NodeBuilder nb;
//   nb.build("test_data/hello");
//   ASSERT_EQ(12, nb.getRoot()->size());
// }
//
TEST_F (FileSystemTest, NodeBuilderOnFolder) {
  NodeBuilder nb;
  nb.build("./test_data");
  ASSERT_EQ(4096, nb.getRoot()->size());
  std::unique_ptr<NodeIterator> it(nb.getRoot()->createIterator());
  it->first();
  ASSERT_EQ(4096, it->currentItem()->size());
  //std::cout<< it->currentItem()->name() << std::endl;
  it->next();
  ASSERT_EQ(12, it->currentItem()->size());
  std::cout<< it->currentItem()->name() << std::endl;
  it->next();
  ASSERT_EQ(83, it->currentItem()->size());
  std::cout<< it->currentItem()->name() << std::endl;
  it->next();
  ASSERT_TRUE(it->isDone());
}
//
// TEST (SystemTest, NodeTypeError)
// {
//   ASSERT_ANY_THROW(new File("./test_data/folder"));//Do not indicate the file path.
//   ASSERT_ANY_THROW(new Folder("./test_data/hello"));//Do not indicate the Folder path.
//   ASSERT_ANY_THROW(new Link("./test_data/hello.cpp"));//Do not indicate the Link path.
// }
//
// TEST_F (FileSystemTest, FindLinkVisitor) {
//   NodeBuilder nb;
//   nb.build("test_data");
//   FindLinkVisitor * flv = new FindLinkVisitor();
//   nb.getRoot()->accept(flv);
//   ASSERT_EQ(1, flv->getLinks().size());
// }
//
// TEST(NodeBuilder, file) {
//   NodeBuilder nb;
//   nb.build("makefile");
//   ASSERT_EQ(1096, nb.getRoot()->size());
// }
//
// TEST_F (FileSystemTest, ClassBuilderOnFile) {
//   NodeBuilder nb;
//   nb.build("test_data/hello.cpp");
//   ASSERT_EQ(83, nb.getRoot()->size());
//
//   nb.build("test_data/hello");
//   ASSERT_EQ(12, nb.getRoot()->size());
//   // ASSERT_EQ(8432, dynamic_cast<Link *>(nb.getRoot())->getSource()->size());
//
//   nb.build("test_data/folder");
//   ASSERT_EQ(96, nb.getRoot()->size());
//
//   std::unique_ptr<NodeIterator> it(nb.getRoot()->createIterator());
//   it->first();
//   // ASSERT_TRUE(it->isDone());
//   ASSERT_EQ(8432, it->currentItem()->size());
//
//   it->next();
//   ASSERT_TRUE(it->isDone());
//
//   nb.build("test_data");
//   ASSERT_EQ(160, nb.getRoot()->size());
//   std::unique_ptr<NodeIterator> it1(nb.getRoot()->createIterator());
//   it1->first();
//   ASSERT_EQ(96, it1->currentItem()->size());
//   it1->next();
//   ASSERT_EQ(12, it1->currentItem()->size());
//   it1->next();
//   ASSERT_EQ(83, it1->currentItem()->size());
//   it1->next();
//   ASSERT_TRUE(it1->isDone());
// }

TEST_F (FileSystemTest, FindNodeByPathnameVisitorLink) {
  std::vector<std::string>* names = new std::vector<std::string>{std::string("hello")};
  FindNodeByPathnameVisitor * fv = new FindNodeByPathnameVisitor(names);
  hello->accept(fv);
  ASSERT_EQ(hello, fv->getNode());
}

TEST_F (FileSystemTest, FindNodeByPathnameVisitorFile) {
  std::vector<std::string>* names = new std::vector<std::string>{std::string("a.out")};
  FindNodeByPathnameVisitor * fv = new FindNodeByPathnameVisitor(names);
  a_out->accept(fv);
  ASSERT_EQ(a_out, fv->getNode());
}

TEST_F (FileSystemTest, TestSetParent) {
  ASSERT_EQ(test_data, folder->getParent());
  ASSERT_EQ(test_data, hello->getParent());
  ASSERT_EQ(test_data, hello_cpp->getParent());
}

TEST_F (FileSystemTest, FileInFolder) {
      std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("folder"), std::string("a.out")};
      FindNodeByPathnameVisitor * fv = new FindNodeByPathnameVisitor(names);
      test_data->accept(fv);
      ASSERT_EQ(a_out, fv->getNode());
}


TEST_F (FileSystemTest, nonExistingFileInFileSystem) {
      std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("helloWorld")};
      FindNodeByPathnameVisitor * fv = new FindNodeByPathnameVisitor(names);
      test_data->accept(fv);
      ASSERT_EQ(nullptr, fv->getNode());
}

TEST_F (FileSystemTest, LinkInFolder){
      std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("hello")};
      FindNodeByPathnameVisitor * fv = new FindNodeByPathnameVisitor(names);
      test_data->accept(fv);
      ASSERT_EQ(hello, fv->getNode());
}

TEST (FindNodeByPathnameVisitor, Link){
      Node * hello = new Link("./test_data/hello");
      std::vector<std::string>* names = new std::vector<std::string>{std::string("hello")};
      FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
      hello->accept(fv);
      ASSERT_EQ(hello, fv->getNode());
}
TEST (FindNodeByPathnameVisitor, LinkInFolder){
      Node * test_data = new Folder ("./test_data");
      Node * hello = new Link("./test_data/hello");
      test_data->add(hello);
      std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("hello")};
      FindNodeByPathnameVisitor *fv = new FindNodeByPathnameVisitor (names);
      test_data->accept(fv);
      ASSERT_EQ(hello, fv->getNode());
}

TEST_F (FileSystemTest, FolderInFolder){
      std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data"), std::string("folder")};
      FindNodeByPathnameVisitor * fv = new FindNodeByPathnameVisitor(names);
      test_data->accept(fv);
      ASSERT_EQ(folder, fv->getNode());
}

TEST_F (FileSystemTest, NodeFolder){
      std::vector<std::string>* names = new std::vector<std::string>{std::string("test_data")};
      FindNodeByPathnameVisitor * fv = new FindNodeByPathnameVisitor(names);
      test_data->accept(fv);
      ASSERT_EQ(test_data, fv->getNode());
}

TEST_F (FileSystemTest, OberservProtocol) {
  Subject * fileSystem = new FileSystem(test_data);
  Observer * mockTreeView = new MockTreeView(fileSystem);
  ASSERT_EQ(1, fileSystem->getNumberOfObservers());
  fileSystem->notify();
  ASSERT_EQ(1,dynamic_cast<MockTreeView *> (mockTreeView)->getUpdateTimes());

  fileSystem->detach(mockTreeView);
  ASSERT_EQ(0, fileSystem->getNumberOfObservers());
}

#endif
