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

wxTextCtrl *idval, *odval, *erval;

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
  wxStaticText *id = new wxStaticText(RoundCoaxPanel,-1,"Inner diameter (d)",wxPoint(-1,-1));
  dialogSizer-> Add(id,1, wxEXPAND|wxALL,10);
  idval = new wxTextCtrl(RoundCoaxPanel,-1,wxString(""), wxPoint(-1,-1),wxSize(-1,-1),0,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (idval, 1, wxEXPAND|wxALL,10); 
  wxStaticText *od = new wxStaticText(RoundCoaxPanel,-1,"Outer diameter (D)",wxPoint(-1,-1));
  dialogSizer-> Add(od,1, wxEXPAND|wxALL,10);
  odval = new wxTextCtrl(RoundCoaxPanel,-1,wxString(""), wxPoint(-1,-1),wxSize(-1,-1),0,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (odval, 1, wxEXPAND|wxALL,10); 
  wxStaticText *er = new wxStaticText(RoundCoaxPanel,-1,"Relative permittivity (Er)",wxPoint(-1,-1));
  dialogSizer-> Add(er,1, wxEXPAND|wxALL,10);
  erval = new wxTextCtrl(RoundCoaxPanel,-1,wxString(""), wxPoint(-1,-1),wxSize(-1,-1),0,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (erval, 1, wxEXPAND|wxALL,10); 
  RoundCoaxPanel->SetSizer(dialogSizer);
  dialogSizer->Fit(RoundCoaxPanel);
  wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
  topsizer->Add(dialogSizer,1,wxEXPAND|wxALL,5);
  SetSizer(topsizer);
  topsizer->Fit(this);
  topsizer->SetSizeHints(this); 
  Layout();
  Refresh();
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
