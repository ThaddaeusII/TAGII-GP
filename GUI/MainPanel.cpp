#include "MainPanel.h"

MainPanel::MainPanel(std::shared_ptr<GPSystem> gp,
    wxWindow *parent,
    wxWindowID id,
    const wxPoint &pos,
    const wxSize &size,
    long style,
    const wxString &name)
    : wxPanel(parent, id, pos, size, style, name)
{
    // Initialize main sizer / notebook for holding main tabs
    mainSizer = new wxGridSizer(0, 1, 0, 0);
	mainTabs = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

    // Add each of the main pages (panels)
    statsTab = new StatsPanel(gp, mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    mainTabs->AddPage(statsTab, "Statistics", false);
    
    programsTab = new ProgramsPanel(gp, mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    mainTabs->AddPage(programsTab, "Programs", false);
    
    environmentTab = new EnvironmentPanel(gp, mainTabs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    mainTabs->AddPage(environmentTab, "Environment", false);

    // Finish setting up
    mainSizer->Add(mainTabs, 1, wxEXPAND | wxALL, 5 );
	this->SetSizer(mainSizer);
	this->Layout();
	mainSizer->Fit(this);
}
