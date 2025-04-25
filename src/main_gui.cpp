#include "Mainframe.h"
#include <wx/wx.h>

class GPApp : public wxApp {
public:
    virtual bool OnInit() override {
        Mainframe* frame = new Mainframe(nullptr);
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP(GPApp);