#ifndef  __EX_FIELD_FRAME_H__
#define  __EX_FIELD_FRAME_H__


// Define a new frame type 'ExFieldFrame'

class ExFieldFrame: public wxFrame
{

  public:
    ExFieldFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~ExFieldFrame();
	DECLARE_EVENT_TABLE()
};


#endif // __EX_FIELD_FRAME_H__

