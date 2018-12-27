#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>
#include <memory>
#include <fstream>
#include <cstring>
#include <map>
#include <cstdio>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include "node_iterator.h"
#include "node_builder.h"
#include "node.h"
#include "subject.h"
#include "observer.h"


void deepVisit(Node * node, wxTreeItemId treeId);
Node * findRootNode(Node * node);
class TreeFrame : public wxFrame, public Observer {
public:

  TreeFrame(const wxChar *title, int xpos, int ypos, int width, int height, Subject * fileSystem, Node * root)
  :wxFrame((wxFrame *) nullptr, -1, title, wxPoint(xpos, ypos), wxSize(width, height)), _fileSystem(fileSystem), _root(root) {
    _fileSystem->attach(this);
    _tree = new wxTreeCtrl(this, wxID_ANY, wxPoint(0,0), wxSize(200,400), wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_EDIT_LABELS );
    wxTreeItemId rootId = _tree->AddRoot(wxT("" + root->name() + "," + std::to_string(root->size())));
    deepVisit(root, rootId);
    _tree->ExpandAllChildren(rootId);
    _textCtrl = new wxTextCtrl(this, -1, _T("Welcom to POSD Editor"),
  		wxPoint(200, 0), wxSize(400, 300), wxTE_MULTILINE);
    _saveButton = new wxButton(this, -1, _T("Save"), wxPoint(200, 300), wxSize(400, 100), 0);
  }

  void OnEdit(wxTreeEvent& event) {
    event.Veto();
    chooseEditId = event.GetItem();
    int editTextChoose = wxMessageBox(wxT("label edit:" + event.GetLabel() + "--" + "old name was " + _tree->GetItemText(chooseEditId)), wxT("Confirm"), wxYES_NO | wxCANCEL, NULL, wxDefaultCoord, wxDefaultCoord);
    newLabel = std::string(event.GetLabel());
    chooseNode = treeTable[chooseEditId];
    oldNodePath = chooseNode->path();
    newTempNodePath = chooseNode->getParent()->path() + "/" + newLabel;
    if(editTextChoose == 2) {
      _fileSystem->changeFileName(chooseNode, newLabel);
      _fileSystem->notify();
      newLabel = "";
      oldNodePath = "";
    }
  }

  void OnTreeSelectionChanged(wxTreeEvent& event) {
    selectedNode = event.GetItem();
    int chooseValue = _fileSystem->isType((treeTable[selectedNode])->path());
    saveFileName = treeTable[selectedNode]->name();
    char line[1000000];
    std::fstream fin;
    if(chooseValue == 1 || chooseValue == 3) {
      _textCtrl->SetValue("The file is not displayed in the editor becase it uses an unsupported text encoding");
      _saveButton->Enable(false);
    }else if(chooseValue == 2) {
      context = "";
      _textCtrl->SetValue(context);
      if(_fileSystem->isContentBinary((treeTable[selectedNode])->path())) {
        _textCtrl->SetValue("The file is not displayed in the editor becase it uses an unsupported text encoding");
        _saveButton->Enable(false);
      }else {
        _saveButton->Enable(true);
        fin.open(treeTable[selectedNode]->path(), std::ios::in);
        while (fin.getline(line, sizeof(line), '\n')) {
          context = context + line + '\n';
        }
        _textCtrl->SetValue(context);
      }
    }
    event.Skip();
  }

  void OnSave(wxCommandEvent& event) {
     int saveChoose = wxMessageBox(wxT("Do you want save"), wxT("Save"), wxYES_NO | wxCANCEL, NULL, wxDefaultCoord, wxDefaultCoord);
     savePath = treeTable[selectedNode]->path();
     if(saveChoose == 2) {
       _fileSystem->notify();
     }
  }

private:
  DECLARE_EVENT_TABLE()
  std::map<wxTreeItemId,Node *> treeTable;
  wxTreeCtrl *_tree;
  wxTextCtrl * _textCtrl;
  wxButton *_saveButton;
  wxTreeItemId chooseEditId;
  wxTreeItemId selectedNode;
  Node * _root;
  Node * chooseNode;
  Subject * _fileSystem;
  std::string newLabel;
  std::string oldNodePath;
  std::string newTempNodePath;
  std::string context;
  std::string savePath;
  wxString saveFileName;

  void deepVisit(Node * node, wxTreeItemId treeId) {
    std::unique_ptr<NodeIterator> it(node->createIterator());
    treeTable.insert(std::pair<wxTreeItemId, Node *>(treeId, node));
    for(it->first(); !it->isDone(); it->next())
      deepVisit(it->currentItem(), _tree->AppendItem(treeId, wxT("" + it->currentItem()->name() + ", " + std::to_string(it->currentItem()->size()))));
  }

  void update() {
    if(newLabel != "") {
      char * newNodePath = new char[newTempNodePath.length() + 1];
      strcpy(newNodePath, newTempNodePath.c_str());
      chooseNode->updateNodePath(newNodePath);
      if(_fileSystem->isType(newTempNodePath))
          chooseNode->deepUpdate(chooseNode);
      newTempNodePath = "";
    }else
      saveFile();
     setTableOfContentName();
  }

  void saveFile() {
    std::fstream file;
    file.open(savePath, std::ios::out);
    file << _textCtrl->GetValue();
    file.close();
  }
  void setTableOfContentName() {
    std::string tempPressNodePath = treeTable[selectedNode]->path();
    char * pressNodePath = new char[tempPressNodePath.length() + 1];
    strcpy(pressNodePath, tempPressNodePath.c_str());
    int fileValue = _fileSystem->fileSize(pressNodePath);
    _tree->SetItemText(selectedNode, treeTable[selectedNode]->name() + ", " + to_string(fileValue));
  }
};

BEGIN_EVENT_TABLE(TreeFrame, wxFrame)
  EVT_TREE_END_LABEL_EDIT (wxID_ANY, TreeFrame::OnEdit)
  EVT_TREE_SEL_CHANGED(wxID_ANY, TreeFrame::OnTreeSelectionChanged)
  EVT_BUTTON(wxID_ANY, TreeFrame::OnSave)
END_EVENT_TABLE()
#endif
