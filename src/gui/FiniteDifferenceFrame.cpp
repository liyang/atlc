//----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/textctrl.h>
#include "wx/wxprec.h"
#include "wx/image.h"
#include "wx/file.h"
#include "wx/wxprec.h"
#include "FiniteDifferenceFrame.h"
#include "ExFieldFrame.h"
#include "EyFieldFrame.h"
#include "EFieldFrame.h"
#include "VoltageFrame.h"
#include "PermittivityFrame.h"
#include "EnergyFrame.h"
#include "resource.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "FiniteDifference.xpm"
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
    EVT_MENU(ID_ViewExField, FiniteDifferenceFrame::OnViewExField)
    EVT_MENU(ID_ViewEyField, FiniteDifferenceFrame::OnViewEyField)
    EVT_MENU(ID_ViewEField, FiniteDifferenceFrame::OnViewEField)
    EVT_MENU(ID_ViewVoltage, FiniteDifferenceFrame::OnViewVoltage)
    EVT_MENU(ID_ViewEnergy, FiniteDifferenceFrame::OnViewEnergy)
    EVT_MENU(ID_ViewPermittivity, FiniteDifferenceFrame::OnViewPermittivity)
    EVT_MENU(ID_Paste, FiniteDifferenceFrame::OnPaste)
    EVT_CLOSE(FiniteDifferenceFrame::OnClose) //QUESTION - What is This ???
    EVT_BUTTON(DIALOG_BTN, FiniteDifferenceFrame::OnClick)
END_EVENT_TABLE()

// FiniteDifference frame constructor
FiniteDifferenceFrame::FiniteDifferenceFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  SetIcon(wxICON(FiniteDifference));
  // create a menu bar
  wxMenu *FileMenu = new wxMenu("", wxMENU_TEAROFF);  
  wxMenu *EditMenu = new wxMenu("", wxMENU_TEAROFF);  
  wxMenu *ViewMenu = new wxMenu("", wxMENU_TEAROFF);  
  wxMenu *RunMenu = new wxMenu("", wxMENU_TEAROFF);  
  wxMenu *GenerateBitmapMenu = new wxMenu("", wxMENU_TEAROFF);
  wxMenu *HelpMenu = new wxMenu("", wxMENU_TEAROFF);

  // File menu
  FileMenu->Append( ID_Save, "&Save as Bitmap","Save Results to a text file");
  FileMenu->Append( ID_FileMenuClose, "&Close" , "Close this windows only");

  // Edit menu
  EditMenu->Append( ID_Cut, "&Cut","Cut some of the bitmap out"); 
  EditMenu->Append( ID_Paste, "&Paste","Paste"); 

  // View menu
  ViewMenu->Append( ID_ViewExField, "E-field in &x-direction","E-field in x-direction shown on a gray scale"); 
  ViewMenu->Append( ID_ViewEyField, "E-field in &y-direction","E-field in y-direction shown on a gray scale"); 
  ViewMenu->Append( ID_ViewEField, "&Magnitude of E","Magnitude of E-field shown on a gray scale."); 
  ViewMenu->Append( ID_ViewVoltage, "&Voltage","Voltage shown on a gray scale."); 
  ViewMenu->Append( ID_ViewPermittivity, "&Permittivity","Permittivity shown on gray scale - coundutors coloured"); 
  ViewMenu->Append( ID_ViewEnergy, "&Energy","Energy shown on gray scale"); 

  // Run menu
  RunMenu->Append( ID_RunFD, "&Run FD simulation","Run the finite difference simulation");

  // GenerateBitmap menue
  GenerateBitmapMenu->Append( ID_RectInRect, "&Rectangular conductor inside rectangular conductor" , "Quickly generate a bitmap for one rectangular conductor inside another.");
  GenerateBitmapMenu->Append( ID_CircInCirc, "&Circular conductor inside circular conductor" ,"Quickly generate a bitmap for one circular conductor inside another");   
  GenerateBitmapMenu->Append( ID_RectInCirc, "R&ectangular conductor inside circular conductor" ,"Quickly generate a bitmap for a rectangular conductor inside a circular one");   
  GenerateBitmapMenu->Append( ID_CircInRect, "C&ircular conductor inside rectangular conductor","Quickly generate a bitmap for a circular conductor inside a rectangular one." );   
  GenerateBitmapMenu->Append( ID_SymStrip,   "&Symmetrical Stripline" ,"Quickly generate a bitmap for a stripline between parallel groundplanes");   
  GenerateBitmapMenu->AppendSeparator();
  GenerateBitmapMenu->Append( ID_Coupler,    "&Coupler (rectangular conductors)" ,"Quickly generate a bitmap for a coupler with rectangular conductors");   

  HelpMenu->Append( ID_Help, "&Help" , "Help");

  // now append the freshly created menu to the menu bar...
  wxMenuBar *menuBar = new wxMenuBar();

  menuBar->Append(FileMenu, "&File");
  menuBar->Append(EditMenu, "&Edit");
  menuBar->Append(GenerateBitmapMenu, "&Generate Bitmap");
  menuBar->Append(ViewMenu, "&View");
  menuBar->Append(RunMenu, "&Run");
  menuBar->Append(HelpMenu, "&Help");
  SetMenuBar(menuBar);
  CreateStatusBar(1);
  SetStatusText("You must now get a bitmap");
  //wxImage image("twin-wire3.bmp");

  // Initalize the panel and button members.

  myPanel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize,wxTAB_TRAVERSAL, "MyPanel"); 
								
  wxPoint myPoint(20, 30);
  wxSize mySize(-1,-1);
  myButton = new wxButton(this, DIALOG_BTN, "Start FD Simulation", 
  myPoint, mySize, 0, wxDefaultValidator, "MyButton");
  myPanel->SetDefaultItem(myButton);

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
  //TextFrame *frame = new TextFrame("Simple Text Editor", 100, 100, 400, 300);
  //frame->Show(TRUE);

  // Make a panel with a message
  //wxPanel *panel = new wxPanel(frame, 0, 0, 400, 400);

  //panel->SetLabelPosition(wxHORIZONTAL) ;
  //wxMessage *msg = new wxMessage(panel, "Hello, this is a minimal wxWindows program!", 5, 5);

  // Show the frame
  //frame->Show(TRUE);
  
  // Return the main frame window
}

void FiniteDifferenceFrame::OnPaste(wxCommandEvent& event)
{
  //wxPanel(this,100,"panel", (-1,-1), (500,600));
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
  wxMessageBox("Note, there is an exact analytical result\n\
for a geometry of one circular conductor inside another -\n\
even when they are not coaxial (i.e. centres offset). Hence\n\
you may prefer to select 'Elliptical Coax' from the main atlc\n\
menu and not use this menue to generate a bitmap, so it\n\
may subsequently be calcualted using the finite difference\n\
method.\n\nThis option is used so the finite difference and\n\
analytical methods can be compared, but it not the most\n\ 
accurate, or the fastest way, of analysing such a stucture","Warning for circular conductors", wxCANCEL | wxOK | wxICON_EXCLAMATION);
}

void FiniteDifferenceFrame::OnCircInRect(wxCommandEvent& event)
{
}

void FiniteDifferenceFrame::OnRectInCirc(wxCommandEvent& event)
{
}

void FiniteDifferenceFrame::OnClick(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox("Clicked!", "Event", wxOK | wxICON_INFORMATION, this);
}
void FiniteDifferenceFrame::OnViewExField(wxCommandEvent& WXUNUSED(event))
{
ExFieldFrame *frame = new ExFieldFrame("Ex     x-directed electric field",wxPoint(0,5),wxSize(500,500));
frame->Show(TRUE);
}

void FiniteDifferenceFrame::OnViewEyField(wxCommandEvent& WXUNUSED(event))
{
EyFieldFrame *frame = new EyFieldFrame("Ey     y-directed electric field",wxPoint(0,5),wxSize(500,500));
frame->Show(TRUE);
}

void FiniteDifferenceFrame::OnViewEField(wxCommandEvent& WXUNUSED(event))
{
EFieldFrame *frame = new EFieldFrame("E     Electric field",wxPoint(0,5),wxSize(500,500));
frame->Show(TRUE);
}

void FiniteDifferenceFrame::OnViewVoltage(wxCommandEvent& WXUNUSED(event))
{
VoltageFrame *frame = new VoltageFrame("V     Voltage",wxPoint(0,5),wxSize(500,500));
frame->Show(TRUE);
}
void FiniteDifferenceFrame::OnViewPermittivity(wxCommandEvent& WXUNUSED(event))
{
PermittivityFrame *frame = new PermittivityFrame("Er    Permittivity",wxPoint(0,5),wxSize(500,500));
frame->Show(TRUE);
}
void FiniteDifferenceFrame::OnViewEnergy(wxCommandEvent& WXUNUSED(event))
{
EnergyFrame *frame = new EnergyFrame("Energy",wxPoint(0,5),wxSize(500,500));
frame->Show(TRUE);
}
