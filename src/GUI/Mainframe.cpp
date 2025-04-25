#include "Mainframe.h"

Mainframe::Mainframe(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style)
    : wxFrame(parent, id, title, pos, size, style)
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
	mainSplitter->Connect( wxEVT_IDLE, wxIdleEventHandler( Mainframe::mainSplitterOnIdle ), NULL, this );

    controlPanel = new ControlPanel(gp, mainSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    mainPanel = new MainPanel(gp, mainSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);

    // Finish setup
	mainSplitter->SplitVertically(controlPanel, mainPanel, 203);
	mainSizer->Add(mainSplitter, 1, wxEXPAND, 5);

	this->SetSizer(mainSizer);
	this->Layout();
	this->Centre( wxBOTH );
}

Mainframe::~Mainframe()
{
}

void Mainframe::mainSplitterOnIdle(wxIdleEvent &)
{
    mainSplitter->SetSashPosition(203);
	mainSplitter->Disconnect(wxEVT_IDLE, wxIdleEventHandler(Mainframe::mainSplitterOnIdle), NULL, this);
}