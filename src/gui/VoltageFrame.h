#ifndef  __VOLTAGE_FRAME_H__
#define  __VOLTAGE_FRAME_H__


// Define a new frame type 'VoltageFrame', which comes up when computing Z of coax. 

class VoltageFrame: public wxFrame
{

  public:
    VoltageFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~VoltageFrame();
	DECLARE_EVENT_TABLE()
};


#endif // __VOLTAGE_FRAME_H__

