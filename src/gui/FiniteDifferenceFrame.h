#ifndef  FINITE_DIFFERENCE_FRAME_H
#define  FINITE_DIFFERENCE_FRAME_H


// Define a new frame type 'FiniteDifferenceFrame
class FiniteDifferenceFrame: public wxFrame
{

  public:
    FiniteDifferenceFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnHelp(wxCommandEvent& event);   // public functions. 
    void OnFileMenuClose(wxCommandEvent& event);   // public functions. 
    void OnRectInRect(wxCommandEvent& event);
    void OnRectInCirc(wxCommandEvent& event);
    void OnCircInRect(wxCommandEvent& event);
    void OnCircInCirc(wxCommandEvent& event);
    void OnEdit(wxCommandEvent& event);
    void OnCut(wxCommandEvent& event);
    void OnPaste(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
       DECLARE_EVENT_TABLE()
};

#endif  // FINITE_DIFFERENCE_FRAME_H

