#ifndef  __PERMITTIVITY_FRAME_H__
#define  __PERMITTIVITY_FRAME_H__


// Define a new frame type 'PermittivityFrame' for displaying a permittivity map.

class PermittivityFrame: public wxFrame
{

  public:
    PermittivityFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~PermittivityFrame();
	DECLARE_EVENT_TABLE()
};


#endif // __PERMITTIVITY_FRAME_H__

