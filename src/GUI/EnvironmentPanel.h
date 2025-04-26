#pragma once

#include <wx/panel.h>

#include <memory>
#include "GPSystem.h"

class EnvironmentPanel : public wxPanel
{
private:
    std::shared_ptr<GPSystem> gp;

    void start(wxCommandEvent& event);
    void step(wxCommandEvent& event);
    void end(wxCommandEvent& event);
    void reset(wxCommandEvent& event);
    
public:
    EnvironmentPanel(std::shared_ptr<GPSystem> gp,
        wxWindow *parent, 
        wxWindowID id=wxID_ANY, 
        const wxPoint &pos=wxDefaultPosition, 
        const wxSize &size=wxDefaultSize, 
        long style=wxTAB_TRAVERSAL, 
        const wxString &name=wxPanelNameStr);
};