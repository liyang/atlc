// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include <wx/textdlg.h>
#include <wx/stattext.h>
#include "RoundCoaxFrm.h"
#include "resource.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "RoundCoax.xpm"
#endif

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------



// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------

// the event tables connect the wxWindows events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(RoundCoaxFrame, wxFrame)
    EVT_MENU(ID_Help, RoundCoaxFrame::OnHelp)
    EVT_MENU(ID_FileMenuClose, RoundCoaxFrame::OnFileMenuClose)
    EVT_CLOSE(RoundCoaxFrame::OnClose) //QUESTION - What is This ???
    EVT_BUTTON(DIALOG_BTN, RoundCoaxFrame::OnClick)
END_EVENT_TABLE()


// RoundCoax frame constructor
RoundCoaxFrame::RoundCoaxFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  SetIcon(wxICON(RoundCoax));
  SetAutoLayout(TRUE);
  wxMenu *FileMenu = new wxMenu;  /* Left most menue */
  wxMenu *HelpMenu = new wxMenu;
  FileMenu->Append( ID_FileMenuClose, "&Close" , "Close");
  HelpMenu->Append( ID_Help, "&Help" , "Help");

  wxMenuBar *menuBar = new wxMenuBar;
  SetMenuBar( menuBar );
  menuBar->Append( FileMenu, "&File" );
  menuBar->Append( HelpMenu, "&Help" );

  CreateStatusBar();
  SetStatusText("Compute Zo using an exact analytical method" );

  RoundCoaxPanel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize,wxTAB_TRAVERSAL, "RoundCoaxPanel"); 
  wxFlexGridSizer *dialogSizer = new wxFlexGridSizer(3,2,5,5);
  dialogSizer-> Add ( new wxStaticText(this,-1,"Inner diameter (d)",wxPoint(100,100)), 0, wxALIGN_CENTRE_VERTICAL);
  dialogSizer-> Add ( new wxTextCtrl(this, 1), 0, wxALIGN_CENTRE_VERTICAL);
  dialogSizer-> Add ( new wxStaticText(this,-1,"Outer diameter (D)"), 0, wxALIGN_CENTRE_VERTICAL);
  dialogSizer-> Add ( new wxTextCtrl(this, 1),0, wxALIGN_CENTRE_VERTICAL);
  dialogSizer-> Add ( new wxStaticText(this,-1,"Relative permittivity (Er"), 0, wxALIGN_CENTRE_VERTICAL);
  dialogSizer-> Add ( new wxTextCtrl(this, 1), 0, wxALIGN_CENTRE_VERTICAL);
  SetSizer(dialogSizer);
  Layout();
}

void RoundCoaxFrame::OnHelp(wxCommandEvent& WXUNUSED(event))
{
  //help.Display("Main page");
}

// The following gets executed if the user closes by the box in the very top left.
void RoundCoaxFrame::OnClose(wxCloseEvent& event)
{
  event.Skip();   
//  delete
//  wxConfig::Set(NULL);
}

// The following gets executed if the user does File->Close on the Round Coax screen.
void RoundCoaxFrame::OnFileMenuClose(wxCommandEvent& event)
{
  wxWindow::Close(TRUE); //Force a closure, window can not resist 
}

void RoundCoaxFrame::OnClick(wxCommandEvent& WXUNUSED(event))
{
  wxMessageBox("Will now compute Zo", "Event", wxOK | wxICON_INFORMATION, this);
}
