#ifndef  __ENERGY_FRAME_H__
#define  __ENERGY_FRAME_H__


// Define a new frame type 'EnergyFrame', which comes up when computing Z of coax. 

class EnergyFrame: public wxFrame
{

  public:
    EnergyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	virtual ~EnergyFrame();
	DECLARE_EVENT_TABLE()
};


#endif // __ENERGY_FRAME_H__

