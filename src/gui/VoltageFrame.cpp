// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include "VoltageFrame.h"
#include "resource.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "icon.V.xpm"
#endif

BEGIN_EVENT_TABLE(VoltageFrame, wxFrame)
END_EVENT_TABLE()


// Voltage frame constructor
VoltageFrame::VoltageFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  SetIcon(wxICON(icon_V));
}

VoltageFrame::~VoltageFrame()
{

}

