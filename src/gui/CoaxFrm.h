#ifndef  __COAX_FRM_H__
#define  __COAX_FRM_H__


// Define a new frame type 'CoaxFrame', which comes up when computing Z of coax. 

class CoaxFrame: public wxFrame
{

  public:
    CoaxFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~CoaxFrame();
	DECLARE_EVENT_TABLE()
};


#endif // __COAX_FRM_H__

