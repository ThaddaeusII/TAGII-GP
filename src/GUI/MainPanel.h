#pragma once

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/notebook.h>

#include "StatsPanel.h"
#include "ProgramsPanel.h"
#include "EnvironmentPanel.h"

#include <memory>
#include "GPSystem.h"

class MainPanel : public wxPanel
{
private:
    wxGridSizer* mainSizer;
    wxNotebook* mainTabs;

    StatsPanel* statsTab;
    ProgramsPanel* programsTab;
    EnvironmentPanel* environmentTab;

public:
    MainPanel(std::shared_ptr<GPSystem> gp,
        wxWindow *parent, 
        wxWindowID id=wxID_ANY, 
        const wxPoint &pos=wxDefaultPosition, 
        const wxSize &size=wxDefaultSize, 
        long style=wxTAB_TRAVERSAL, 
        const wxString &name=wxPanelNameStr);
    StatsPanel* GetStatsPanel() { return statsTab; }
    ProgramsPanel* GetProgramsPanel() { return programsTab; }
    EnvironmentPanel* GetEnvironmentPanel() { return environmentTab; }
};