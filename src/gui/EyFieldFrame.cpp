// For compilers that support precompilation, includes "wx/wx.h".
#if defined(__WXGTK__) || defined(__WXMOTIF__)
        #include "wx/wx.h"
#endif
#include "wx/wxprec.h"
#include "EyFieldFrame.h"
#include "resource.h"

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------
// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__)
    #include "icon.Ey.xpm"
#endif

BEGIN_EVENT_TABLE(EyFieldFrame, wxFrame)
END_EVENT_TABLE()


// EyField frame constructor
EyFieldFrame::EyFieldFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
  SetIcon(wxICON(icon_Ey));
}

EyFieldFrame::~EyFieldFrame()
{

}

