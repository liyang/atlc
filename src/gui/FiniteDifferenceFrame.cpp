//----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include "FiniteDifferenceFrame.h"
#include "resource.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "atlc.xpm"
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

BEGIN_EVENT_TABLE(FiniteDifferenceFrame, wxFrame)
    EVT_MENU(ID_FileMenuClose, FiniteDifferenceFrame::OnFileMenuClose)
    EVT_MENU(ID_Help, FiniteDifferenceFrame::OnHelp)
    EVT_MENU(ID_RectInRect, FiniteDifferenceFrame::OnRectInRect)
    EVT_MENU(ID_RectInCirc, FiniteDifferenceFrame::OnRectInCirc)
    EVT_MENU(ID_CircInCirc, FiniteDifferenceFrame::OnCircInCirc)
    EVT_MENU(ID_CircInRect, FiniteDifferenceFrame::OnCircInRect)
    EVT_MENU(ID_Cut, FiniteDifferenceFrame::OnCut)
    EVT_MENU(ID_Paste, FiniteDifferenceFrame::OnPaste)
    EVT_CLOSE(FiniteDifferenceFrame::OnClose) //QUESTION - What is This ???
END_EVENT_TABLE()


// FiniteDifference frame constructor
FiniteDifferenceFrame::FiniteDifferenceFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  // create a menu bar
  wxMenu *FileMenu = new wxMenu("", wxMENU_TEAROFF);  
  wxMenu *EditMenu = new wxMenu("", wxMENU_TEAROFF);  
  wxMenu *RunMenu = new wxMenu("", wxMENU_TEAROFF);  
  wxMenu *GenerateBitmapMenu = new wxMenu("", wxMENU_TEAROFF);
  wxMenu *HelpMenu = new wxMenu("", wxMENU_TEAROFF);

  // File menu
  FileMenu->Append( ID_Save, "&Save as Bitmap","Save Results to a text file");
  FileMenu->Append( ID_FileMenuClose, "&Close" , "Close this windows only");

  // Edit menu
  EditMenu->Append( ID_Cut, "&Cut","Cut some of the bitmap out"); 
  EditMenu->Append( ID_Paste, "&Paste","Paste"); 

  // Run menu
  RunMenu->Append( ID_RunFD, "&Run FD simulation","Run the finite difference simulation");

  // GenerateBitmap menue
  GenerateBitmapMenu->Append( ID_RectInRect, "&Rectangular conductor inside rectangular conductor" , "Generate rectinrect");
  GenerateBitmapMenu->Append( ID_CircInCirc, "&Circular conductor inside circular conductor" );   
  GenerateBitmapMenu->Append( ID_RectInCirc, "R&ectangular conductor inside circular conductor" );   
  GenerateBitmapMenu->Append( ID_CircInRect, "C&ircular conductor inside rectangular conductor" );   
  GenerateBitmapMenu->Append( ID_SymStrip,   "&Symmetrical Stripline" );   
  GenerateBitmapMenu->AppendSeparator();
  GenerateBitmapMenu->Append( ID_Coupler,    "&Edge on coupler" );   

  HelpMenu->Append( ID_Help, "&Help" , "Help");

  // now append the freshly created menu to the menu bar...
  wxMenuBar *menuBar = new wxMenuBar();

  menuBar->Append(FileMenu, "&File");
  menuBar->Append(EditMenu, "&Edit");
  menuBar->Append(GenerateBitmapMenu, "&Generate Bitmap");
  menuBar->Append(RunMenu, "&Run");
  menuBar->Append(HelpMenu, "&Help");
  SetMenuBar(menuBar);
  CreateStatusBar(1);
  SetStatusText("You must now get a bitmap");
}

void FiniteDifferenceFrame::OnHelp(wxCommandEvent& WXUNUSED(event))
{
}

// The following gets executed if the user closes by the box in the very top left.
void FiniteDifferenceFrame::OnClose(wxCloseEvent& event)
{
  event.Skip();   
}

void FiniteDifferenceFrame::OnCut(wxCommandEvent& event)
{
}

void FiniteDifferenceFrame::OnPaste(wxCommandEvent& event)
{
}

// The following gets executed if the user does File->Close
void FiniteDifferenceFrame::OnFileMenuClose(wxCommandEvent& event)
{
  wxWindow::Close(TRUE); //Force a closure, window can not resist 
}

void FiniteDifferenceFrame::OnRectInRect(wxCommandEvent& event)
{
}

void FiniteDifferenceFrame::OnCircInCirc(wxCommandEvent& event)
{
}

void FiniteDifferenceFrame::OnCircInRect(wxCommandEvent& event)
{
}

void FiniteDifferenceFrame::OnRectInCirc(wxCommandEvent& event)
{
}
