// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include "RoundCoaxFrm.h"
#include "resource.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "coax.xpm"
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
END_EVENT_TABLE()


// RoundCoax frame constructor
RoundCoaxFrame::RoundCoaxFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  SetIcon(wxICON(coax));
  wxMenu *FileMenu = new wxMenu;  /* Left most menue */
  wxMenu *HelpMenu = new wxMenu;
  wxMenuBar *menuBar = new wxMenuBar;
  CreateStatusBar();
  SetStatusText( "Computer Zo using an exact analystical method" );
  FileMenu->Append( ID_Save, "&Save as Bitmap","Save Results to a text file"); //HACK, needs changing.  
  FileMenu->Append( ID_FileMenuClose, "&Close" , "Close this windows only");
  HelpMenu->Append( ID_Help, "&Help" , "Help");
  SetMenuBar( menuBar );
  menuBar->Append( FileMenu, "&File" );
  menuBar->Append( HelpMenu, "&Help" );
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
