// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include "EFieldFrame.h"
#include "resource.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "icon.E.xpm"
#endif

BEGIN_EVENT_TABLE(EFieldFrame, wxFrame)
END_EVENT_TABLE()


// EField frame constructor
EFieldFrame::EFieldFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  SetIcon(wxICON(icon_E));
}

EFieldFrame::~EFieldFrame()
{

}

