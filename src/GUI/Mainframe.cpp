#include "Mainframe.h"

#include "CustomEvents.h"

void Mainframe::OnTimer(wxTimerEvent &event)
{
    if (currentGeneration >= gp->getGenerations())
    {
        runTimer.Stop();

        wxCommandEvent end_evt(EVT_RUN_ENDED);
        wxPostEvent(mainPanel->GetStatsPanel(), end_evt);
        wxPostEvent(mainPanel->GetProgramsPanel(), end_evt);
        wxPostEvent(mainPanel->GetEnvironmentPanel(), end_evt);
        return;
    }

    gp->step();
    gp->calcStats();

    wxCommandEvent step_evt(EVT_RUN_STEP);
    wxPostEvent(mainPanel->GetStatsPanel(), step_evt);
    wxPostEvent(mainPanel->GetProgramsPanel(), step_evt);
    wxPostEvent(mainPanel->GetEnvironmentPanel(), step_evt);

    currentGeneration++;
}

void Mainframe::OnRun(wxCommandEvent &event)
{
    currentGeneration = 0;

    wxCommandEvent start_evt(EVT_RUN_STARTED);
    wxPostEvent(mainPanel->GetStatsPanel(), start_evt);
    wxPostEvent(mainPanel->GetProgramsPanel(), start_evt);
    wxPostEvent(mainPanel->GetEnvironmentPanel(), start_evt);

    runTimer.Start(1);
}

void Mainframe::OnReset(wxCommandEvent &event)
{
    gp->reset();

    // Run reset event
    wxCommandEvent reset_evt(EVT_RUN_RESET);
    wxPostEvent(mainPanel->GetStatsPanel(), reset_evt);
    wxPostEvent(mainPanel->GetProgramsPanel(), reset_evt);
    wxPostEvent(mainPanel->GetEnvironmentPanel(), reset_evt);
}

void Mainframe::OnSaveRun(wxCommandEvent &event)
{
    mainPanel->GetStatsPanel()->SaveStats("run.stats");
}

Mainframe::Mainframe(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : wxFrame(parent, id, title, pos, size, style), runTimer(this)
{
    // Initialize GPSystem
    gp = std::make_shared<GPSystem>();
    gp->calcStats();

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
    this->SetBackgroundColour(wxColour(40, 40, 40));
    this->SetForegroundColour(wxColour(200, 200, 200));

    // Setup main sizer
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

    // Control Panel | Main Panel
    mainSplitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	mainSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler(Mainframe::mainSplitterOnIdle), NULL, this );

    controlPanel = new ControlPanel(gp, mainSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    mainPanel = new MainPanel(gp, mainSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

    // Finish setup
	mainSplitter->SplitVertically(controlPanel, mainPanel, 203);
	mainSizer->Add(mainSplitter, 1, wxEXPAND, 5);

	this->SetSizer(mainSizer);
	this->Layout();
	this->Centre(wxBOTH);

    Bind(wxEVT_TIMER, &Mainframe::OnTimer, this);
    Bind(EVT_RUN_STARTED, &Mainframe::OnRun, this);
    Bind(EVT_RUN_RESET, &Mainframe::OnReset, this);
    Bind(EVT_RUN_SAVE, &Mainframe::OnSaveRun, this);
}

Mainframe::~Mainframe()
{
}

void Mainframe::mainSplitterOnIdle(wxIdleEvent &)
{
    mainSplitter->SetSashPosition(203);
	mainSplitter->Disconnect(wxEVT_IDLE, wxIdleEventHandler(Mainframe::mainSplitterOnIdle), NULL, this);
}