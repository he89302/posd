#include <sys/stat.h>
#include <iostream>
#include <memory>
#include "link.h"
#include "folder.h"
#include "file.h"
#include "node_iterator.h"
#include "find_link_visitor.h"

FindLinkVisitor::FindLinkVisitor() {}

void FindLinkVisitor::visitFile(File * file) {}

void FindLinkVisitor::visitFolder(Folder * folder) {
  std::unique_ptr<NodeIterator>it(folder->createIterator());
    for (it->first(); !it->isDone(); it->next()) {
      it->currentItem()->accept(this);
    }
}

void FindLinkVisitor::visitLink(Link * link) {
    links.push_back(link);
}
