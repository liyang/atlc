// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include "EccentricCoaxFrame.h"
#include "resource.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "EccentricCoax.xpm"
#endif

BEGIN_EVENT_TABLE(EccentricCoaxFrame, wxFrame)
END_EVENT_TABLE()


// EccentricCoaxFrame frame constructor
EccentricCoaxFrame::EccentricCoaxFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  SetIcon(wxICON(EccentricCoax));
}

EccentricCoaxFrame::~EccentricCoaxFrame()
{
}

