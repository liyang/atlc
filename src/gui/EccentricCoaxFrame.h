#ifndef  __ECCENTRIC_COAX_FRM_H__
#define  __ECCENTRIC_COAX_FRM_H__


// Define a new frame type 'EccentricCoaxFrame', which comes up when computing Z of coax. 

class EccentricCoaxFrame: public wxFrame
{

  public:
    EccentricCoaxFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~EccentricCoaxFrame();
	DECLARE_EVENT_TABLE()
};


#endif // __ECCENTRIC_COAX_FRM_H__

