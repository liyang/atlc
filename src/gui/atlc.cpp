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

class ChecksumApp: public wxApp
{
    virtual bool OnInit();
};

// Derrive ChecksumFrame from the class wxFrame
class ChecksumFrame: public wxFrame
{
public:

    ChecksumFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void OnOpen(wxCommandEvent& event);   // public functions. 
    void OnQuit(wxCommandEvent& event);   // public functions. 
    void OnAbout(wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Open = 1,
    ID_Quit = 2,
    ID_About,
};

BEGIN_EVENT_TABLE(ChecksumFrame, wxFrame)
    EVT_MENU(ID_Open, ChecksumFrame::OnOpen)
    EVT_MENU(ID_Quit, ChecksumFrame::OnQuit)
    EVT_MENU(ID_About, ChecksumFrame::OnAbout)
END_EVENT_TABLE()

IMPLEMENT_APP(ChecksumApp)

bool ChecksumApp::OnInit()
{
    ChecksumFrame *frame = new ChecksumFrame("checksum",wxPoint(50,50),wxSize(600,440) );
    //ChecksumFrame *frame = new ChecksumFrame("checksum",wxPoint(50,50),wxSize(600,440) );
    frame->Show(TRUE);
    SetTopWindow(frame);
    return TRUE;
} 

ChecksumFrame::ChecksumFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;

    menuFile->Append( ID_Open, "&Open File" ); //HACK, needs changing.  
    menuFile->Append( ID_About, "&About..." );
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, "E&xit" );

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( "atlc, the finite difference program for modelling transmission lines and couplers" );
}

void ChecksumFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(TRUE);
}

void ChecksumFrame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
  unsigned short cksum;
  unsigned char *data;
  int length=100;
  data = new unsigned char (length);
  //cksum=checksum.get_checksum(data, length);
    wxMessageBox("The checksum is 0x12343\n\n Note - the checksum's will depend on the byte ordering of machines\n\
- don't try comparing PCs (little-endian) to Suns (big-endian).");
}

void ChecksumFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox("This is atlc, which may be found at http://atlc.sourceforge.net\n\
atlc is used for finding the impedance of arbitary transmission lines and couplers.\n\n\
Copyright (C) 2002. Dr. David Kirkby PhD (G8WRB). e-mail drkirkby@ntlworld.com\n\n\
This may be copied and distribted under the terms of the GNU General Public Licence",
        "About atlc", wxOK | wxICON_INFORMATION, this);
}

