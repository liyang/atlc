#ifdef __GNUG__
#pragma implementation "help.cpp"
#pragma interface "help.cpp"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/image.h>
#include <wx/wxhtml.h>
#include <wx/filesys.h>
#include <wx/fs_zip.h>
//#include <wx/wx.h>
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

class atlc: public wxApp
{
  virtual bool OnInit();
};

// Derrive atlcFrame from the class wxFrame
// This is going to be our main frame. 
class atlcFrame: public wxFrame
{

  public:
    atlcFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    
    //File menue
    void OnOpen(wxCommandEvent& event);   // public functions. 
    void OnQuit(wxCommandEvent& event);   // public functions. 

    //Tools menue
    void OnRectInRect(wxCommandEvent& event);
    void OnCircInCirc(wxCommandEvent& event);
    void OnRectInCirc(wxCommandEvent& event);
    void OnCircInRect(wxCommandEvent& event);
    void OnSymStrip(wxCommandEvent& event);
    void OnCoupler(wxCommandEvent& event);

    // Calculate menue
    void OnFiniteDifference(wxCommandEvent& event);
    void OnExact(wxCommandEvent& event);

    // Calculate -> Exact
    //void OnSubCoax(wxCommandEvent& event);
    //void OnSubStripline(wxCommandEvent& event);

    //Help menue
    void OnAbout(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);

    private:
      wxHtmlHelpController help;
	    
// Any class wishing to process wxWindows events must use this macro
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
  ID_Help = 11,
  ID_Options = 12,
  ID_SubCoax=13,
  ID_SubStripline=14,
  ID_About
};

// ----------------------------------------------------------------------------
// event tables and other macros for wxWindows
// ----------------------------------------------------------------------------


  // the event tables connect the wxWindows events with the functions (event
  // handlers) which process them. It can be also done at run-time, but for the
  // simple menu events like this the static method is much simpler.
BEGIN_EVENT_TABLE(atlcFrame, wxFrame)
    EVT_MENU(ID_Open, atlcFrame::OnOpen)
    EVT_MENU(ID_Quit, atlcFrame::OnQuit)
    EVT_MENU(ID_RectInRect, atlcFrame::OnRectInRect)
    EVT_MENU(ID_Exact, atlcFrame::OnExact)
    EVT_MENU(ID_Help, atlcFrame::OnHelp)
    EVT_MENU(ID_About, atlcFrame::OnAbout)
    //EVT_MENU(ID_SubCoax, atlcFrame::OnSubCoax)
    //EVT_MENU(ID_SubStripline, atlcFrame::OnSubStripline)
    //EVT_CLOSE(wxClose::OnClose) //QUESTION - What is This ???
END_EVENT_TABLE()

  // Create a new application object: this macro will allow wxWindows to create
  // the application object during program execution (it's better than using a
  // static object for many reasons) and also declares the accessor function
  // wxGetApp() which will return the reference of the right type (i.e. MyApp and
  // not wxApp)

  IMPLEMENT_APP(atlc)

  // ============================================================================
  // implementation
  // ============================================================================

  // ----------------------------------------------------------------------------
  // the application class
  // ----------------------------------------------------------------------------
  // `Main program' equivalent: the program execution "starts" here

bool atlc::OnInit()
{
  wxInitAllImageHandlers();     // QUESTION - what does this do?
#if wxUSE_STREAMS && wxUSE_ZIPSTREAM && wxUSE_ZLIB 
wxFileSystem::AddHandler(new wxZipFSHandler); // QUESTION - what does this do?
#endif
  SetVendorName("wxWindows");
  SetAppName("atlc"); 

  // Create the main application window
  atlcFrame *frame = new atlcFrame("atlc",wxPoint(50,50),wxSize(600,440) );

  // Show it and tell the application that it's our main window
  // @@@ what does it do exactly, in fact? is it necessary here?
  frame->Show(TRUE);
  SetTopWindow(frame);
  // success: wxApp::OnRun() will be called which will enter the main message
  // loop and the application will run. If we returned FALSE here, the
  // application would exit immediately.
  return TRUE;
} 

// frame constructor
atlcFrame::atlcFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  // Create a menue bar. 
  wxMenu *menuFile = new wxMenu;  /* Left most menue */
  wxMenu *menuTools = new wxMenu;
  wxMenu *menuCalculate = new wxMenu;
  //wxMenu *menuSubExact = new wxMenu;
  wxMenu *menuOptions = new wxMenu;
  wxMenu *menuHelp = new wxMenu;

  // now append the freshly created menu to the menu bar...

  // File menue
  menuFile->Append( ID_Open, "&Open File","Open a bitmap"); //HACK, needs changing.  
  menuFile->AppendSeparator();
  menuFile->Append( ID_Quit, "E&xit" );
    
  // Tools menue
  menuTools->Append( ID_RectInRect,\
  "&Rectangular conductor inside rectangular conductor",\
  "Automatically generate a bitmap for a rectangular inner and rectangular outer conductors.");   
  menuTools->Append( ID_CircInCirc, "&Circular conductor inside circular conductor" );   
  menuTools->Append( ID_RectInCirc, "R&ectangular conductor inside circular conductor" );   
  menuTools->Append( ID_CircInRect, "C&ircular conductor inside rectangular conductor" );   
  menuTools->Append( ID_SymStrip,   "&Symmetrical Stripline" );   
  menuTools->AppendSeparator();
  menuTools->Append( ID_Coupler,    "&Edge on coupler" );   
  // Calculate menue

  // Define a sub menue of the Calculate menue. 
  //menuSubExact->Append( ID_SubCoax,    "&Coax" );   
  //menuSubExact->Append( ID_SubStripline,    "&Stripline" );   

  menuCalculate->Append( ID_FiniteDifference,    "&Calculate by finite difference",\
  "Calculate properties using an accurate, very general but slow technique.");   
menuCalculate->Append( ID_Exact, "&Exact",\
"Calculate properties using exact analytical methods, in the \
few cases these are known.");   
    
  // Options
  menuOptions->Append( ID_Options,    "&Options" );   

  // Help
  menuHelp->Append( ID_Help, "&Help" ); //HACK, needs changing.  
  menuHelp->Append( ID_About, "&About" ); //HACK, needs changing.  

  wxMenuBar *menuBar = new wxMenuBar;

  // ... and attach this menu bar to the frame
  SetMenuBar( menuBar );
  menuBar->Append( menuFile, "&File" );
  menuBar->Append( menuTools, "&Tools" );
  menuBar->Append( menuCalculate, "&Calculate" );
  menuBar->Append( menuOptions, "&Options" );
  menuBar->Append( menuHelp, "&Help" );
  //menuBar->Append( menuSubExact, "&Help" );

  CreateStatusBar();
  SetStatusText( "atlc, the finite difference program for modelling transmission lines and couplers" );

  // QUESTION - What the hell does the rest of this do ???
  help.UseConfig(wxConfig::Get());
  bool ret;
  help.SetTempDir(".");
  help.AddBook("helpfiles/testing.hhp");
  if (! ret)
    wxMessageBox("Failed adding book helpfiles/testing.hhp");
  ret = help.AddBook("helpfiles/another.hhp");
  if (! ret)
    wxMessageBox("Failed adding book helpfiles/another.hhp");
}

// event handlers
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

void atlcFrame::OnHelp(wxCommandEvent& WXUNUSED(event))
{
  help.Display("Main page");
}

void atlcFrame::OnExact(wxCommandEvent& WXUNUSED(event))
{

}

void atlcFrame::OnFiniteDifference(wxCommandEvent& WXUNUSED(event))
{
}
/*
void atlcFrame::OnSubCoax(wxCommandEvent& WXUNUSED(event))
{
}

void atlcFrame::OnSubStripline(wxCommandEvent& WXUNUSED(event))
{
}

void atlcFrame::OnClose(wxCommandEvent& WXUNUSED(event))
{
}

*/
