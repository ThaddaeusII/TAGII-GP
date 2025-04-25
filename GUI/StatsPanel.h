#pragma once

#include <wx/panel.h>

#include <memory>
#include "GPSystem.h"

class StatsPanel : public wxPanel
{
private:
    std::shared_ptr<GPSystem> gp;

public:
    StatsPanel(std::shared_ptr<GPSystem> gp,
        wxWindow *parent, 
        wxWindowID id=wxID_ANY, 
        const wxPoint &pos=wxDefaultPosition, 
        const wxSize &size=wxDefaultSize, 
        long style=wxTAB_TRAVERSAL, 
        const wxString &name=wxPanelNameStr);
};