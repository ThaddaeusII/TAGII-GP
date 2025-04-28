#include "EnvironmentPanel.h"

#include <sstream>

#include "CustomEvents.h"

void EnvironmentPanel::start(wxCommandEvent &event)
{
}

void EnvironmentPanel::step(wxCommandEvent &event)
{
}

void EnvironmentPanel::end(wxCommandEvent &event)
{
    auto evt = wxCommandEvent(wxEVT_BUTTON);
    visualizeReset(evt);
}

void EnvironmentPanel::reset(wxCommandEvent &event)
{
    auto evt = wxCommandEvent(wxEVT_BUTTON);
    visualizeReset(evt);
}

void EnvironmentPanel::visualizeStart(wxCommandEvent &event)
{
    Program* program = gp->getProgram(0);
    program->reset();

    displayEnv();

    if (!stepTimer.IsRunning())
    {
        stepTimer.Start(100);
    }
}

void EnvironmentPanel::visualizeStop(wxCommandEvent &event)
{
    stepTimer.Stop();
}

void EnvironmentPanel::visualizeStep(wxCommandEvent &event)
{
    programStep();
    displayEnv();
}

void EnvironmentPanel::visualizeReset(wxCommandEvent &event)
{
    Program* program = gp->getProgram(programIndex);
    program->reset();
    
    displayEnv();
    displayProg();

    stepTimer.Stop();
}

void EnvironmentPanel::timerStep(wxTimerEvent &event)
{
    programStep();
    displayEnv();
    wxYield();

    if (gp->getProgram(programIndex)->complete())
    {
        stepTimer.Stop();
    }
}

void EnvironmentPanel::onProgramIndexChange(wxSpinEvent &event)
{
    programIndex = event.GetValue();

    auto evt = wxCommandEvent(wxEVT_BUTTON);
    visualizeReset(evt);
}

void EnvironmentPanel::programStep()
{
    Program* program = gp->getProgram(programIndex);
    if (program->complete())
        return;
    if (!program->running())
        program->start();
    else
        program->step();
}

void EnvironmentPanel::displayEnv()
{
    Program* program = gp->getProgram(programIndex);
    envDisplay->Clear();

    std::ostringstream oss;
    oss << "Program: " << programIndex << std::endl;
    program->displayNextInstruction(oss);
    
    oss << std::endl;

    gp->displayEnvironment(oss);
    
    envDisplay->AppendText(oss.str());
}

void EnvironmentPanel::displayProg()
{
    Program* program = gp->getProgram(programIndex);
    progDisplay->Clear();
    std::ostringstream oss;
    oss << "Program: " << programIndex << std::endl;
    program->display(oss);
    progDisplay->AppendText(oss.str());
}

EnvironmentPanel::EnvironmentPanel(std::shared_ptr<GPSystem> gp,
                                   wxWindow *parent,
                                   wxWindowID id,
                                   const wxPoint &pos,
                                   const wxSize &size,
                                   long style,
                                   const wxString &name)
    : wxPanel(parent, id, pos, size, style, name), gp(gp), stepTimer(this)
{
    this->SetBackgroundColour(wxColour(40, 40, 40));
    this->SetForegroundColour(wxColour(200, 200, 200));

    wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* buttonSizer;
	buttonSizer = new wxBoxSizer(wxHORIZONTAL);

	startButton = new wxButton(this, wxID_ANY, "  Start  ", wxDefaultPosition, wxDefaultSize, 1);
	buttonSizer->Add(startButton, 0, wxALL, 5);

	stopButton = new wxButton(this, wxID_ANY, "  Stop  ", wxDefaultPosition, wxDefaultSize, 1);
	buttonSizer->Add(stopButton, 0, wxALL, 5);

	stepButton = new wxButton(this, wxID_ANY, "  Step  ", wxDefaultPosition, wxDefaultSize, 1);
	buttonSizer->Add(stepButton, 0, wxALL, 5);

	resetButton = new wxButton(this, wxID_ANY, "  Reset  ", wxDefaultPosition, wxDefaultSize, 1);
	buttonSizer->Add(resetButton, 0, wxALL, 5);

    programIndexCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, gp->getPopulationSize(), 0);
	buttonSizer->Add(programIndexCtrl, 0, wxALL, 5 );

	mainSizer->Add(buttonSizer, 1, wxEXPAND, 5);

	mainSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D);
    mainSplitter->SetSashGravity(0.5);
	mainSplitter->Connect(wxEVT_IDLE, wxIdleEventHandler(EnvironmentPanel::mainSplitterOnIdle), NULL, this);

	leftPanel = new wxPanel(mainSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* leftSizer;
	leftSizer = new wxBoxSizer(wxVERTICAL);

	envDisplay = new wxTextCtrl(leftPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_BESTWRAP);
	leftSizer->Add(envDisplay, 1, wxEXPAND, 5);

	leftPanel->SetSizer(leftSizer);
	leftPanel->Layout();
	leftSizer->Fit(leftPanel);
	rightPanel = new wxPanel(mainSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer* rightSizer;
	rightSizer = new wxBoxSizer(wxVERTICAL);

	progDisplay = new wxTextCtrl(rightPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_BESTWRAP);
	rightSizer->Add(progDisplay, 1, wxEXPAND, 5);

    wxFont monospaceFont(16, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    envDisplay->SetFont(monospaceFont);
    progDisplay->SetFont(monospaceFont);

	rightPanel->SetSizer(rightSizer);
	rightPanel->Layout();
	rightSizer->Fit(rightPanel);
	mainSplitter->SplitVertically(leftPanel, rightPanel, 0);
	mainSizer->Add(mainSplitter, 10, wxEXPAND, 5);

	this->SetSizer(mainSizer);
	this->Layout();

    // Bind GPSystem events
    Bind(EVT_RUN_STARTED, &EnvironmentPanel::start, this);
    Bind(EVT_RUN_STEP, &EnvironmentPanel::step, this);
    Bind(EVT_RUN_ENDED, &EnvironmentPanel::end, this);
    Bind(EVT_RUN_RESET, &EnvironmentPanel::reset, this);

    // Bind panel buttons and events
    startButton->Bind(wxEVT_BUTTON, &EnvironmentPanel::visualizeStart, this);
    stopButton->Bind(wxEVT_BUTTON, &EnvironmentPanel::visualizeStop, this);
    stepButton->Bind(wxEVT_BUTTON, &EnvironmentPanel::visualizeStep, this);
    resetButton->Bind(wxEVT_BUTTON, &EnvironmentPanel::visualizeReset, this);
    Bind(wxEVT_TIMER, &EnvironmentPanel::timerStep, this);
    programIndexCtrl->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(EnvironmentPanel::onProgramIndexChange), NULL, this);

    wxSpinEvent event(wxEVT_COMMAND_SPINCTRL_UPDATED);\
    onProgramIndexChange(event);
}

void EnvironmentPanel::mainSplitterOnIdle(wxIdleEvent &)
{
	mainSplitter->Disconnect(wxEVT_IDLE, wxIdleEventHandler(EnvironmentPanel::mainSplitterOnIdle), NULL, this);
}
