#ifndef  __E_FIELD_FRAME_H__
#define  __E_FIELD_FRAME_H__


// Define a new frame type 'EFieldFrame', which comes up when computing Z of coax. 

class EFieldFrame: public wxFrame
{

  public:
    EFieldFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~EFieldFrame();
	DECLARE_EVENT_TABLE()
};


#endif // __E_FIELD_FRAME_H__

