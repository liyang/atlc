// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include "wx/panel.h"
#include "wx/gdicmn.h"
#include <wx/toolbar.h>
#include "atlcFrm.h"
#include "RoundCoaxFrm.h"
#include "FiniteDifferenceFrame.h"
#include "EccentricCoaxFrame.h"
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

BEGIN_EVENT_TABLE(atlcFrame, wxFrame)
    EVT_MENU(ID_Open, atlcFrame::OnOpen)
    EVT_MENU(ID_Quit, atlcFrame::OnQuit)
    EVT_MENU(ID_Help, atlcFrame::OnHelp)
    EVT_MENU(ID_About, atlcFrame::OnAbout)
    EVT_MENU(ID_RoundCoax, atlcFrame::OnRoundCoax)
    EVT_MENU(ID_EccentricCoax, atlcFrame::OnEccentricCoax)
    EVT_MENU(ID_SquareCoax, atlcFrame::OnSquareCoax)
    EVT_MENU(ID_Stripline, atlcFrame::OnStripline)
    EVT_MENU(ID_CalculateChecksum, atlcFrame::OnCalculateChecksum)
    EVT_MENU(ID_FiniteDifference, atlcFrame::OnFiniteDifference)
    EVT_MENU(ID_ShowTip, atlcFrame::OnShowTip)
    EVT_CLOSE(atlcFrame::OnClose) //QUESTION - What is This ???
END_EVENT_TABLE()

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
  
atlcFrame::atlcFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  // set the frame icon
  SetIcon(wxICON(atlc));

  // create a menu bar
  wxMenu *FileMenu = new wxMenu("", wxMENU_TEAROFF);
  wxMenu *ToolsMenu = new wxMenu("", wxMENU_TEAROFF);
  wxMenu *CalculateMenu = new wxMenu("", wxMENU_TEAROFF);
  wxMenu *OptionsMenu = new wxMenu("", wxMENU_TEAROFF);
  wxMenu *HelpMenu = new wxMenu("", wxMENU_TEAROFF);

  // Tools menue
  ToolsMenu->Append( ID_CalculateChecksum, "&Calculate a checksum","Generate a 16-bit checksum for comparing files");

  // Calculate menue. 
  CalculateMenu->Append( ID_FiniteDifference,    "&Finite difference (numerical)",\
  "Calculate properties using an accurate, very general but slow numerical technique.");   
  CalculateMenu->AppendSeparator();
  CalculateMenu->Append( ID_RoundCoax, "&Coaxial cable","Calculate properties standard round coaxial cable");   
  CalculateMenu->Append( ID_EccentricCoax, "&Eccentric Coaxial cable (exact)","Calculate properties eccentric coaxial cable");   
  CalculateMenu->Append( ID_SquareCoax, "&Coaxial (square outer, round inner)","Calculate properties coaxial cable with a square outer (exact??)");   
  CalculateMenu->Append( ID_Stripline, "&Edge on stripline (exact)","Calculate properties of thin edge-on conductors between groundplanes");   
  CalculateMenu->Append( ID_Stripline, "&Edge on stripline coupler (exact)","Calculate properties of two thin edge-on conductors.");   

  // Options menue
  OptionsMenu->Append( ID_Options,    "&Options" );   

  // Help menu
  wxMenu *helpMenu = new wxMenu;
  //helpMenu->Append(Minimal_About, "&About...\tCtrl-A", "Show about dialog");
  HelpMenu->Append(ID_About, "&About...\tCtrl-A", "Show about dialog");
  HelpMenu->Append( ID_ShowTip, "&Tip of the day" ); 
  HelpMenu->Append( ID_Help, "&Help" ); 

  //FileMenu->Append(Minimal_Quit, "E&xit\tAlt-X", "Quit this program");
  FileMenu->Append(ID_Quit, "E&xit\tAlt-X", "Quit this program");

  // now append the freshly created menu to the menu bar...
  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(FileMenu, "&File");
  menuBar->Append(ToolsMenu, "&Tools");
  menuBar->Append(CalculateMenu, "&Calculate");
  menuBar->Append(OptionsMenu, "&Options");
  menuBar->Append(HelpMenu, "&Help");

  // ... and attach this menu bar to the frame
  SetMenuBar(menuBar);

  // create a status bar just for fun (by default with 1 pane only)
  CreateStatusBar(1);
  wxBitmap *myBitmap = new wxBitmap("coax-toolbar.bmp",wxBITMAP_TYPE_BMP);
  if(myBitmap->Ok() != TRUE)
  {
    wxMessageDialog *msg = new wxMessageDialog(this, "bitmap NOT loaded !!!!", "Error", wxICON_HAND,wxDefaultPosition);
    msg->ShowModal();
  }
  wxToolBar *myToolBar = new wxToolBar(this,-1,wxPoint(-1,-1), wxSize(-1,-1), wxTB_HORIZONTAL, "foo");
  myToolBar->AddTool(-1, *myBitmap , "foo", "lots of foos");
  myToolBar->Realize();
  SetStatusText("Ready");
}
  


// event handlers

void atlcFrame::OnClose(wxCloseEvent& event)
{
  // Close the help frame; this will cause the config data to
  // get written.
  if ( help.GetFrame() ) // returns NULL if no help frame active
    help.GetFrame()->Close(TRUE);
  // now we can safely delete the config pointer
  event.Skip();   
  delete
  wxConfig::Set(NULL);
  exit(1);
}

void atlcFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // TRUE is to force the frame to close
    Close(TRUE);
}

void atlcFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog dialog(this, "Testing open file dialog", "", "", "*.bmp", 0);
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString info;
        info.Printf(_T("Full file name: %s\n")
                    _T("Path: %s\n")
                    _T("Name: %s"),
                    dialog.GetPath().c_str(),
                    dialog.GetDirectory().c_str(),
                    dialog.GetFilename().c_str());
        wxMessageDialog dialog2(this, info, "Selected file");
        dialog2.ShowModal();
    }
}

void atlcFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("This is atlc, which may be found at http://atlc.sourceforge.net\n\
atlc is used for finding the impedance of arbitary transmission lines and couplers.\n\n\
Copyright (C) 2002. Dr. David Kirkby PhD (G8WRB). e-mail drkirkby@ntlworld.com\n\n\
This may be copied and distribted under the terms of the GNU General Public Licence",
        "About atlc", wxOK | wxICON_INFORMATION, this);
}

void atlcFrame::OnCoupler(wxCommandEvent& WXUNUSED(event))
{
}

void atlcFrame::OnHelp(wxCommandEvent& WXUNUSED(event))
{
  help.Display("Main page");
}

void atlcFrame::OnFiniteDifference(wxCommandEvent& WXUNUSED(event))
{

  FiniteDifferenceFrame *frame = new FiniteDifferenceFrame("Use a Finite Difference numerical method",wxPoint(50,50),wxSize(500,300) );
  SetAutoLayout(TRUE);
  // Make a panel with a message
  //wxPanel *panel = new wxPanel(frame, -1, wxPoint(0,0),wxSize(100,100),wxTAB_TRAVERSAL,"foo");
  //wxPanel *panel = new wxPanel(atlcFrame, -1, wxPoint(0,0),wxSize(100,100),wxTAB_TRAVERSAL,"foo");
  //frame->Show(TRUE);

  //panel->SetLabelPosition(wxHORIZONTAL) ;
  //wxMessageBox *msg = new wxMessageBox(panel, "Hello, this is a minimal wxWindows program!", 5, 5);
  //wxMessageBox(panel, "Hello, this is a minimal wxWindows program!", 5, 5);

  // Show the frame
  //frame->Show(TRUE);
  //wxTextEntryDialog(panel, "hello", "Please enter text", "foo", wxOK, wxDefaultPosition);
  //panel->Show(TRUE);
  frame->Show(TRUE);
  //exit(1);
  
  // Return the main frame window
}

void atlcFrame::OnRoundCoax(wxCommandEvent& WXUNUSED(event))
{
  // Create the window for the standard round coax. 
  RoundCoaxFrame *frame = new RoundCoaxFrame("Standard Round Coaxial Cable",wxPoint(0,5),wxSize(500,500) );
  SetAutoLayout(TRUE); 
  frame->Show(TRUE);
}

void atlcFrame::OnStripline(wxCommandEvent& WXUNUSED(event))
{
}

void atlcFrame::OnSquareCoax(wxCommandEvent& WXUNUSED(event))
{
}

void atlcFrame::OnEccentricCoax(wxCommandEvent& WXUNUSED(event))
{
  EccentricCoaxFrame *frame = new EccentricCoaxFrame("Eccentric Coax",wxPoint(50,50),wxSize(500,300) );

  frame->Show(TRUE);
}
void atlcFrame::OnCalculateChecksum(wxCommandEvent& WXUNUSED(event))
{
  unsigned short cksum;
  unsigned char *data;
  int length=100;
  data = new unsigned char (length);
  //cksum=checksum.get_checksum(data, length);
    wxMessageBox("The checksum is 0x12343\n\n Note - the checksum's will depend on the byte ordering of machines\n\
- don't try comparing PCs (little-endian) to Suns (big-endian).");
}

void atlcFrame::OnShowTip(wxCommandEvent& event)
{
#if wxUSE_STARTUP_TIPS
    static size_t s_index = (size_t)-1;

    if ( s_index == (size_t)-1 )
    {
        srand(time(NULL));

        // this is completely bogus, we don't know how many lines are there
        // in the file, but who cares, it's a demo only...
        s_index = 13; // rand() % 13;
    }

    wxTipProvider *tipProvider = wxCreateFileTipProvider("tips.txt", s_index);

    bool showAtStartup = wxShowTip(this, tipProvider);
/*
    if ( showAtStartup )
    {
        wxMessageBox("Will show tips on startup", "Tips dialog",
                     wxOK | wxICON_INFORMATION, this);
    }
*/
    s_index = tipProvider->GetCurrentTip();
    delete tipProvider;
#endif // wxUSE_STARTUP_TIPS
}
