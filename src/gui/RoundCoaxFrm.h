#ifndef  __ROUND_COAX_FRM_H__
#define  __ROUND_COAX_FRM_H__


// Define a new frame type 'RoundCoaxFrame
class RoundCoaxFrame: public wxFrame
{

  public:
    RoundCoaxFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnHelp(wxCommandEvent& event);   // public functions. 
    void OnFileMenuClose(wxCommandEvent& event);   // public functions. 
    void OnClose(wxCloseEvent& event);
  
	DECLARE_EVENT_TABLE()
};


#endif  // __ROUND_COAX_FRM_H__

