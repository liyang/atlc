#ifndef  __EY_FIELD_FRAME_H__
#define  __EY_FIELD_FRAME_H__


// Define a new frame type 'EyFieldFrame'

class EyFieldFrame: public wxFrame
{

  public:
    EyFieldFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~EyFieldFrame();
	DECLARE_EVENT_TABLE()
};


#endif // __EY_FIELD_FRAME_H__

