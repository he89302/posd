#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>
#include <memory>
#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
#include "node_iterator.h"
#include "node_builder.h"
#include "node.h"
#include "subject.h"
#include "file.h"
#include "folder.h"
#include "observer.h"


void deepVisit(Node * node, wxTreeItemId treeId);
class TreeFrame : public wxFrame, public Observer
{
public:
  TreeFrame(const wxChar *title, int xpos, int ypos, int width, int height, Subject * fileSystem, Node * root):wxFrame((wxFrame *) nullptr, -1, title, wxPoint(xpos, ypos), wxSize(width, height)), _fileSystem(fileSystem), _root(root)
  {
    _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(100,200), wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_EDIT_LABELS );
    wxTreeItemId rootId = _tree->AddRoot(wxT("" + root->name() + "," + std::to_string(root->size())));
    deepVisit(root, rootId);
    _tree->ExpandAllChildren(rootId);
  }

  void update() {

  }


void OnEdit(wxTreeEvent& event)
{
    // std::string editLabel = std::string(event.GetLabel());
    // wxString s_text = wxGetTextFromUser(wxT("The new name"), wxT("Tree sample question"), s_text, this);
    // wxTreeItemId nowLabel = _tree->GetFocusedItem();
    // wxString str = _tree->GetItemText(nowLabel);
    // _tree->SetItemText(nowLabel, s_text);
    // std::cout<< std::string(str) << '\n';
    // char * editName = new char[editLabel.length()+1];
    // strcpy(editName, editLabel.c_str());
    // std::cout<< editName << '\n';
    wxTreeItemId chooseId = event.GetItem();
    //std::string oldLabel = std::string(_tree->GetItemText(chooseId));
    //std::string label = std::string(event.GetLabel());
    //char * editName = new char[label.length()+1];
    //strcpy(editName, label.c_str());
    Node * node = treeTable[chooseId];
    std::cout << node->path() << '\n';
    // std::string parentPath = "";
    // if(node->getParent() != nullptr) {
    //   parentPath = node->getParent()->path() + "/";
    // }
    // const char * oldPath = node->path();
    // const char * newPath;
}

void deepVisit(Node * node, wxTreeItemId treeId) {
  NodeIterator * it = node->createIterator();
  treeTable.insert(std::pair<wxTreeItemId, Node *>(treeId, node));
  for(it->first(); !it->isDone(); it->next()) {
    deepVisit(it->currentItem(), _tree->AppendItem(treeId, wxT("" + it->currentItem()->name() + ", " + std::to_string(it->currentItem()->size()))));
  }
}

  wxTreeCtrl *_tree;
private:
  DECLARE_EVENT_TABLE()
  Node * _root;
  Subject * _fileSystem;
  std::map<wxTreeItemId,Node *> treeTable;
};




BEGIN_EVENT_TABLE(TreeFrame, wxFrame)
  EVT_TREE_END_LABEL_EDIT (wxID_ANY, TreeFrame::OnEdit)
END_EVENT_TABLE()
#endif
