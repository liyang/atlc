#ifndef  __ATLC_FRM_H__
#define  __ATLC_FRM_H__

#include <wx/image.h>
#include <wx/wxhtml.h>
#include <wx/filesys.h>
#include <wx/fs_zip.h>
#include <wx/tipdlg.h>
#include <wx/html/helpctrl.h>

// Define a new frame type: this is going to be our main frame

class atlcFrame: public wxFrame
{
  public:
    atlcFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    // event handlers (these functions should _not_ be virtual)
    
    //File menue
    void OnOpen(wxCommandEvent& event);   // public functions. 
    void OnQuit(wxCommandEvent& event);   // public functions. 
    void OnClose(wxCloseEvent& event); // Note close is xwxCloseEvent, not wxCommandEvent

    //void OnSymStrip(wxCommandEvent& event);
    void OnCoupler(wxCommandEvent& event);

    //Tools menue
    void OnCalculateChecksum(wxCommandEvent& event);   // public functions. 

    // Calculate menue
    void OnFiniteDifference(wxCommandEvent& event);
    void OnRoundCoax(wxCommandEvent& event);
    void OnEccentricCoax(wxCommandEvent& event);
    void OnSquareCoax(wxCommandEvent& event);
    void OnStripline(wxCommandEvent& event);
    void OnCalculateCoupler(wxCommandEvent& event);

    //Help menue
    void OnAbout(wxCommandEvent& event);
    void OnHelp(wxCommandEvent& event);
    void OnShowTip(wxCommandEvent& event);

    // QUESTION - What is the OnClose one = when hitting button or top right?
    //void OnClose(wxCloseEvent& event);
    private:
      wxHtmlHelpController help;
	    
// Any class wishing to process wxWindows events must use this macro
  DECLARE_EVENT_TABLE()
};


#endif  //__ATLC_FRM_H__

