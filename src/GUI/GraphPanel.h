#pragma once

#include <wx/panel.h>
#include "mathplot.h"

#include <memory>
#include <vector>

#include "GPSystem.h"

class GraphPanel : public wxPanel
{
private:
    std::shared_ptr<GPSystem> gp;
    
public:
    GraphPanel(std::shared_ptr<GPSystem> gp,
        wxWindow *parent, 
        wxWindowID id=wxID_ANY, 
        const wxPoint &pos=wxDefaultPosition, 
        const wxSize &size=wxDefaultSize, 
        long style=wxTAB_TRAVERSAL, 
        const wxString &name=wxPanelNameStr);
};