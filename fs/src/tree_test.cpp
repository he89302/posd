#include <wx/wx.h>
#include "tree_test.h"
#include "tree_frame.h"
#include "node.h"
#include "node_builder.h"
#include "subject.h"
#include "file_system.h"

IMPLEMENT_APP(TreeTestApp)

bool TreeTestApp::OnInit()
{
  std::string tempArgv = std::string(wxTheApp->argv[1]);
  char * argv = new char[tempArgv.length() + 1];
  strcpy(argv, tempArgv.c_str());
  NodeBuilder nb;
  nb.build(argv);
  Node * root = nb.getRoot();
  Subject * fileSystem = new FileSystem(root);

  wxFrame *frame = new TreeFrame(wxT("***Tree Test***"), 100, 100, 600, 400,fileSystem, root);
  frame->Show(true);
  this->SetTopWindow(frame);
  return true;
}
