// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include "PermittivityFrame.h"
#include "resource.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "icon.Er.xpm"
#endif

BEGIN_EVENT_TABLE(PermittivityFrame, wxFrame)
END_EVENT_TABLE()


// Permittivity frame constructor
PermittivityFrame::PermittivityFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  SetIcon(wxICON(icon_Er));
}

PermittivityFrame::~PermittivityFrame()
{

}

