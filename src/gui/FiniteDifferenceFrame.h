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

    void OnClick(wxCommandEvent& event);
    void OnViewExField(wxCommandEvent& event);
    void OnViewEyField(wxCommandEvent& event);
    void OnViewEField(wxCommandEvent& event);
    void OnViewVoltage(wxCommandEvent& event);
    void OnViewPermittivity(wxCommandEvent& event);
    void OnViewEnergy(wxCommandEvent& event);
    void OnView(wxCommandEvent& event);

  private:
    // Added Panel and button members.
    wxPanel *myPanel;
    wxTextCtrl *myTextCtrl;
    wxButton *myButton;
    DECLARE_EVENT_TABLE()
};

#endif  // FINITE_DIFFERENCE_FRAME_H

