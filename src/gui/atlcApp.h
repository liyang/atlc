#ifndef  __ATLC_APP_H__
#define  __ATLC_APP_H__

// Define a new application type, each program should derive a class from wxApp
class atlcApp : public wxApp
{

public:
    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();


};

#endif  // __ATLC_APP_H__
