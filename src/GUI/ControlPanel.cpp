#include "ControlPanel.h"

#include "CustomStaticLine.h"
#include "CustomEvents.h"

wxBEGIN_EVENT_TABLE(ControlPanel, wxPanel)
    EVT_BUTTON(1001, ControlPanel::OnRun)
    EVT_BUTTON(1002, ControlPanel::OnReset)
    EVT_BUTTON(1003, ControlPanel::OnSaveRun)
    EVT_BUTTON(1004, ControlPanel::OnLoadParams)
    EVT_BUTTON(1005, ControlPanel::OnSaveParams)
    EVT_BUTTON(1006, ControlPanel::OnLoadEnv)
    EVT_BUTTON(1007, ControlPanel::OnSaveEnv)
    EVT_BUTTON(1008, ControlPanel::OnSetParams)
    EVT_BUTTON(1009, ControlPanel::OnResetParams)
wxEND_EVENT_TABLE()

ControlPanel::ControlPanel(std::shared_ptr<GPSystem> gp,
    wxWindow *parent,
    wxWindowID id,
    const wxPoint &pos,
    const wxSize &size,
    long style,
    const wxString &name)
    : wxPanel(parent, id, pos, size, style, name), gp(gp)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create Buttons
    runButton = new wxButton(this, 1001, "Run");
    resetButton = new wxButton(this, 1002, "Reset");
    saveRunButton = new wxButton(this, 1003, "Save Run Data");
    loadParamsButton = new wxButton(this, 1004, "Load Params Config");
    saveParamsButton = new wxButton(this, 1005, "Save Params Config");
    loadEnvButton = new wxButton(this, 1006, "Load Environment");
    saveEnvButton = new wxButton(this, 1007, "Save Environment");
    setParamsButton = new wxButton(this, 1008, "Set");
    resetParamsButton = new wxButton(this, 1009, "Reset");

    // Create Configurable Parameters
    popSizeCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10000, gp->getPopulationSize());
    generationsCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 100000, gp->getGenerations());

    // Add to layout
    wxBoxSizer* runResetSizer = new wxBoxSizer(wxHORIZONTAL);
    runResetSizer->Add(runButton, 0, wxEXPAND|wxALL, 10);
    runResetSizer->Add(resetButton, 0, wxEXPAND|wxALL, 10);
    mainSizer->Add(runResetSizer, 0, wxEXPAND|wxLEFT|wxRIGHT, 10);
    mainSizer->Add(saveRunButton, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 10);

    mainSizer->Add(new CustomStaticLine(this, *wxLIGHT_GREY, 2), 0, wxEXPAND | wxALL, 5);

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Population Size:"), 0, wxTOP|wxLEFT, 10);
    mainSizer->Add(popSizeCtrl, 0, wxEXPAND|wxLEFT|wxRIGHT, 10);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Generations:"), 0, wxTOP|wxLEFT, 10);
    mainSizer->Add(generationsCtrl, 0, wxEXPAND|wxLEFT|wxRIGHT, 10);

    wxBoxSizer* setResetSizer = new wxBoxSizer(wxHORIZONTAL);
    setResetSizer->Add(setParamsButton, 0, wxEXPAND|wxALL, 10);
    setResetSizer->Add(resetParamsButton, 0, wxEXPAND|wxALL, 10);
    mainSizer->Add(setResetSizer, 0, wxEXPAND|wxLEFT|wxRIGHT, 10);
    
    mainSizer->Add(new CustomStaticLine(this, *wxLIGHT_GREY, 2), 0, wxEXPAND | wxALL, 5);

    mainSizer->Add(loadParamsButton, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 10);
    mainSizer->Add(saveParamsButton, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 10);

    mainSizer->Add(new CustomStaticLine(this, *wxLIGHT_GREY, 2), 0, wxEXPAND | wxALL, 5);

    mainSizer->Add(loadEnvButton, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 10);
    mainSizer->Add(saveEnvButton, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 10);

    SetSizer(mainSizer);
}

void ControlPanel::OnRun(wxCommandEvent& event)
{
    wxCommandEvent evt(EVT_RUN_STARTED);
    wxPostEvent(GetParent(), evt);
}

void ControlPanel::OnReset(wxCommandEvent &event)
{
    wxCommandEvent evt(EVT_RUN_RESET);
    wxPostEvent(GetParent(), evt);
}

void ControlPanel::OnSaveRun(wxCommandEvent& event)
{
}

void ControlPanel::OnLoadParams(wxCommandEvent& event)
{
}

void ControlPanel::OnSaveParams(wxCommandEvent& event)
{
}

void ControlPanel::OnLoadEnv(wxCommandEvent& event)
{
}

void ControlPanel::OnSaveEnv(wxCommandEvent& event)
{
}

void ControlPanel::OnSetParams(wxCommandEvent &event)
{
}

void ControlPanel::OnResetParams(wxCommandEvent &event)
{
}
