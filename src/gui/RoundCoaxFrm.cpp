// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include <wx/textdlg.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include "RoundCoaxFrm.h"
#include <math.h>
#include "atlcgui.h"
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

wxTextCtrl *idval, *odval, *erval, *Zoval, *Cval, *Lval, *vval, *vfval, *cutoffval;

// RoundCoax frame constructor
RoundCoaxFrame::RoundCoaxFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  int n1=0, n2=-2, n3=0;
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
  wxFlexGridSizer *dialogSizer = new wxFlexGridSizer(8,3,7,7);

  wxStaticText *id = new wxStaticText(RoundCoaxPanel,-1,"Inner diameter (d)",wxPoint(-1,-1));
  dialogSizer-> Add(id,1, wxEXPAND|wxALL,n1);
  idval = new wxTextCtrl(RoundCoaxPanel,-1,wxString("0.406"), wxPoint(-1,-1),wxSize(-1,-1),0,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (idval, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *foo = new wxStaticText(RoundCoaxPanel,-1,"mm",wxPoint(-1,-1));
  dialogSizer-> Add (foo, 1, wxEXPAND|wxALL,n3); 

  wxStaticText *od = new wxStaticText(RoundCoaxPanel,-1,"Outer diameter (D)",wxPoint(-1,-1));
  dialogSizer-> Add(od,1, wxEXPAND|wxALL,n1);
  odval = new wxTextCtrl(RoundCoaxPanel,-1,wxString("1.48"), wxPoint(-1,-1),wxSize(-1,-1),0,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (odval, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *foo2 = new wxStaticText(RoundCoaxPanel,-1,"mm",wxPoint(-1,-1));
  dialogSizer-> Add (foo2, 1, wxEXPAND|wxALL,n3); 

  wxStaticText *er = new wxStaticText(RoundCoaxPanel,-1,"Relative permittivity (Er)",wxPoint(-1,-1));
  dialogSizer-> Add(er,1, wxEXPAND|wxALL,n1);
  erval = new wxTextCtrl(RoundCoaxPanel,-1,wxString("2.26"), wxPoint(-1,-1),wxSize(-1,-1),0,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (erval, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *foo3 = new wxStaticText(RoundCoaxPanel,-1,"",wxPoint(-1,-1));
  dialogSizer-> Add (foo3, 1, wxEXPAND|wxALL,n3); 

  wxStaticText *impedance = new wxStaticText(RoundCoaxPanel,-1,"Impedance",wxPoint(-1,-1));
  dialogSizer-> Add(impedance,1, wxEXPAND|wxALL,n1);
  Zoval = new wxTextCtrl(RoundCoaxPanel,-1,wxString("***"), wxPoint(-1,-1),wxSize(-1,-1),wxTE_READONLY,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (Zoval, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *impedance_text = new wxStaticText(RoundCoaxPanel,-1,"Ohms",wxPoint(-1,-1));
  dialogSizer-> Add (impedance_text, 1, wxEXPAND|wxALL,n3); 

  wxStaticText *capacitance = new wxStaticText(RoundCoaxPanel,-1,"Capacitance per m",wxPoint(-1,-1));
  dialogSizer-> Add(capacitance,1, wxEXPAND|wxALL,n1);
  Cval = new wxTextCtrl(RoundCoaxPanel,-1,wxString("***"), wxPoint(-1,-1),wxSize(-1,-1),wxTE_READONLY,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (Cval, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *capacitance_text = new wxStaticText(RoundCoaxPanel,-1,"pF/m",wxPoint(-1,-1));
  dialogSizer-> Add (capacitance_text, 1, wxEXPAND|wxALL,n3); 

  wxStaticText *inductance = new wxStaticText(RoundCoaxPanel,-1,"Inductance per m",wxPoint(-1,-1));
  dialogSizer-> Add(inductance,1, wxEXPAND|wxALL,n1);
  Lval = new wxTextCtrl(RoundCoaxPanel,-1,wxString("***"), wxPoint(-1,-1),wxSize(-1,-1),wxTE_READONLY,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (Lval, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *inductance_text = new wxStaticText(RoundCoaxPanel,-1,"nH/m",wxPoint(-1,-1));
  dialogSizer-> Add (inductance_text, 1, wxEXPAND|wxALL,n3); 

  wxStaticText *velocity= new wxStaticText(RoundCoaxPanel,-1,"Velocity of propogation",wxPoint(-1,-1));
  dialogSizer-> Add(velocity,1, wxEXPAND|wxALL,n1);
  vval = new wxTextCtrl(RoundCoaxPanel,-1,wxString("***"), wxPoint(-1,-1),wxSize(-1,-1),wxTE_READONLY,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (vval, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *velocity_text = new wxStaticText(RoundCoaxPanel,-1,"m/s",wxPoint(-1,-1));
  dialogSizer-> Add (velocity_text, 1, wxEXPAND|wxALL,n3); 

  wxStaticText *velocity_factor= new wxStaticText(RoundCoaxPanel,-1,"Velocity factor",wxPoint(-1,-1));
  dialogSizer-> Add(velocity_factor,1, wxEXPAND|wxALL,n1);
  vfval = new wxTextCtrl(RoundCoaxPanel,-1,wxString("***"), wxPoint(-1,-1),wxSize(-1,-1),wxTE_READONLY,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (vfval, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *velocity_factor_text = new wxStaticText(RoundCoaxPanel,-1,"",wxPoint(-1,-1));
  dialogSizer-> Add (velocity_factor_text, 1, wxEXPAND|wxALL,n3); 

  wxStaticText *cutoff_frequency= new wxStaticText(RoundCoaxPanel,-1,"Cutoff frequency",wxPoint(-1,-1));
  dialogSizer-> Add(cutoff_frequency,1, wxEXPAND|wxALL,n1);
  cutoffval = new wxTextCtrl(RoundCoaxPanel,-1,wxString("***"), wxPoint(-1,-1),wxSize(-1,-1),wxTE_READONLY,wxTextValidator(wxFILTER_NUMERIC,NULL),wxString(""));
  dialogSizer-> Add (cutoffval, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *cutoff_frequency_text = new wxStaticText(RoundCoaxPanel,-1,"GHz",wxPoint(-1,-1));
  dialogSizer-> Add (cutoff_frequency_text, 1, wxEXPAND|wxALL,n3); 

  wxButton *erf = new wxButton(this, DIALOG_BTN, "Compute", wxPoint(-1,-1), wxSize(-1,-1), 0, wxDefaultValidator, "MyButton");
  dialogSizer-> Add(erf,1, wxEXPAND|wxALL,n1);
  wxStaticText *erf3 = new wxStaticText(RoundCoaxPanel,-1,"",wxPoint(-1,-1));
  dialogSizer-> Add (erf3, 1, wxEXPAND|wxALL,n2); 
  wxStaticText *foo4 = new wxStaticText(RoundCoaxPanel,-1,"",wxPoint(-1,-1));
  dialogSizer-> Add (foo4, 1, wxEXPAND|wxALL,n3); 

  RoundCoaxPanel->SetSizer(dialogSizer);
  dialogSizer->Fit(RoundCoaxPanel);
  wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
  topsizer->Add(dialogSizer,1,wxEXPAND|wxALL,n1);
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
  double Zo, id, od, Er, capacitance, inductance, velocity, velocity_factor;
  double cutoff_frequency, cutoff_wavelength;
  wxString inside, outside, er, f;

  inside = idval->GetValue();
  outside = odval->GetValue();
  er = erval->GetValue();

  inside.ToDouble(&id);
  outside.ToDouble(&od);
  er.ToDouble(&Er);
  if(Er < 1.0)
  {
    wxMessageBox("The relative permittivity Er must be >= 1.0", "Permittivity Error", wxOK | wxICON_ERROR, this);
    return;
  }
  if(od <= id)
  {
    wxMessageBox("The outer diamater must exceed the inner diamater", "Size Error", wxOK | wxICON_ERROR, this);
    return;
  }
  if(id <= 0.0 || od <= 0.0)
  {
    wxMessageBox("Both diameters must exceed 0.0", "Size Error", wxOK | wxICON_ERROR, this);
    return;
  }
  capacitance=Er*2*PI*VACUUM_PERMITTIVITY/log(od/id);
  inductance=log(od/id)*VACUUM_PERMEABILITY/(2*PI);
  Zo=sqrt(inductance/capacitance);

  f.Printf("%f",1e12*capacitance);
  Cval->SetValue(f);

  f.Printf("%f",1e9*inductance);
  Lval->SetValue(f);

  f.Printf("%f",Zo);
  Zoval->SetValue(f);

  velocity=VELOCITY_OF_LIGHT_IN_VACUUM/sqrt(Er);
  f.Printf("%f",velocity);
  vval->SetValue(f);

  velocity_factor=velocity/VELOCITY_OF_LIGHT_IN_VACUUM;
  f.Printf("%f",velocity_factor);
  vfval->SetValue(f);

  cutoff_wavelength=PI*(od-id);
  cutoff_frequency=300/cutoff_wavelength;
  f.Printf("%f", cutoff_frequency);
  cutoffval->SetValue(f);
}
