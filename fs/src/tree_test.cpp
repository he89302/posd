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
  NodeBuilder nb;
  nb.build("test_data");
  Node * root = nb.getRoot();
  Subject * fileSystem = new FileSystem(root);

  wxFrame *frame = new TreeFrame(wxT("***Tree Test***"), 100, 100, 300, 200,fileSystem, root);

  frame->Show(true);
  this->SetTopWindow(frame);
  return true;
}
