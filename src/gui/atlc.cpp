/*
checksum
 */

#include "wx/wx.h" 
#include <iostream.h>

class checksum
{
  private:
    unsigned short sum;
  public:
    unsigned short get_checksum(char *data, int length);
};

// Create a simple checksum for comparing files to the non GUI version. 
unsigned short checksum::get_checksum(char * data, int length)
{
  int counter;
  sum=0; // Will overflow to creat a checksum.
  for(counter = 0; counter < length; ++ counter)
    sum+=data[counter];
  return(sum);
} 

class atlcApp: public wxApp
{
    virtual bool OnInit();
};

// Derrive atlcFrame from the class wxFrame
class atlcFrame: public wxFrame
{
public:

    atlcFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    
    //File
    void OnOpen(wxCommandEvent& event);   // public functions. 
    void OnQuit(wxCommandEvent& event);   // public functions. 

    //Tools
    void OnRectInRect(wxCommandEvent& event);
    void OnCircInCirc(wxCommandEvent& event);
    void OnRectInCirc(wxCommandEvent& event);
    void OnCircInRect(wxCommandEvent& event);
    void OnSymStrip(wxCommandEvent& event);
    void OnCoupler(wxCommandEvent& event);

    // Calculate
    void OnFiniteDifference(wxCommandEvent& event);
    void OnExact(wxCommandEvent& event);

    //Help
    void OnAbout(wxCommandEvent& event);
    void OnHelp2(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Open = 1,
    ID_Quit = 2,
    ID_RectInRect = 3,
    ID_CircInCirc = 4,
    ID_RectInCirc = 5,
    ID_CircInRect = 6,
    ID_SymStrip = 7,
    ID_Coupler = 8,
    ID_FiniteDifference = 9,
    ID_Exact = 10,
    ID_Help2 = 11,
    ID_Options = 12,
    ID_About,
};

BEGIN_EVENT_TABLE(atlcFrame, wxFrame)
    EVT_MENU(ID_Open, atlcFrame::OnOpen)
    EVT_MENU(ID_Quit, atlcFrame::OnQuit)
    EVT_MENU(ID_About, atlcFrame::OnAbout)
END_EVENT_TABLE()

IMPLEMENT_APP(atlcApp)

bool atlcApp::OnInit()
{
    atlcFrame *frame = new atlcFrame("atlc",wxPoint(50,50),wxSize(600,440) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
} 

atlcFrame::atlcFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;  /* Left most menue */
    wxMenu *menuTools = new wxMenu;
    wxMenu *menuCalculate = new wxMenu;
    wxMenu *menuOptions = new wxMenu;
    wxMenu *menuHelp = new wxMenu;

    // File menue
    menuFile->Append( ID_Open, "&Open File" ); //HACK, needs changing.  
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, "E&xit" );
    
    // Tools menue
    menuTools->Append( ID_RectInRect, "&Rectangular conductor inside rectangular conductor");   
    menuTools->Append( ID_CircInCirc, "&Circular conductor inside circular conductor" );   
    menuTools->Append( ID_RectInCirc, "R&ectangular conductor inside circular conductor" );   
    menuTools->Append( ID_CircInRect, "C&ircular conductor inside rectangular conductor" );   
    menuTools->Append( ID_SymStrip,   "&Symmetrical Stripline" );   
    menuTools->AppendSeparator();
    menuTools->Append( ID_Coupler,    "&Edge on coupler" );   
    // Calculate menue
    menuCalculate->Append( ID_FiniteDifference,    "Calculate by finite difference" );   
    menuCalculate->Append( ID_Exact,    "Calculate exactly" );   
    
    // Options
    menuOptions->Append( ID_Options,    "&Options" );   

    // Help
    menuHelp->Append( ID_Help2, "&Help" ); //HACK, needs changing.  
    menuHelp->Append( ID_About, "&About" ); //HACK, needs changing.  

    wxMenuBar *menuBar = new wxMenuBar;
    SetMenuBar( menuBar );
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuTools, "&Tools" );
    menuBar->Append( menuCalculate, "&Calculate" );
    menuBar->Append( menuOptions, "&Options" );
    menuBar->Append( menuHelp, "&Help" );

    CreateStatusBar();
    SetStatusText( "atlc, the finite difference program for modelling transmission lines and couplers" );
}

void atlcFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void atlcFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
  unsigned short cksum;
  unsigned char *data;
  int length=100;
  data = new unsigned char (length);
  //cksum=checksum.get_checksum(data, length);
    wxMessageBox("The checksum is 0x12343\n\n Note - the checksum's will depend on the byte ordering of machines\n\
- don't try comparing PCs (little-endian) to Suns (big-endian).");
}

void atlcFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("This is atlc, which may be found at http://atlc.sourceforge.net\n\
atlc is used for finding the impedance of arbitary transmission lines and couplers.\n\n\
Copyright (C) 2002. Dr. David Kirkby PhD (G8WRB). e-mail drkirkby@ntlworld.com\n\n\
This may be copied and distribted under the terms of the GNU General Public Licence",
        "About atlc", wxOK | wxICON_INFORMATION, this);
}

void atlcFrame::OnRectInRect(wxCommandEvent& WXUNUSED(event))
{
}

void atlcFrame::OnCircInCirc(wxCommandEvent& WXUNUSED(event))
{
}

void atlcFrame::OnCoupler(wxCommandEvent& WXUNUSED(event))
{
}

void atlcFrame::OnHelp2(wxCommandEvent& WXUNUSED(event))
{
}
void atlcFrame::OnExact(wxCommandEvent& WXUNUSED(event))
{
}
void atlcFrame::OnFiniteDifference(wxCommandEvent& WXUNUSED(event))
{
}

