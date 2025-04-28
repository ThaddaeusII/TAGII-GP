#include "ControlPanel.h"

#include "CustomStaticLine.h"
#include "CustomEvents.h"
#include "PacmanEnvironment.h"

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
    mutationRateCtrl = new wxTextCtrl(this, wxID_ANY, wxString::Format("%.2f", gp->getMutationRate()));
    crossoverRateCtrl = new wxTextCtrl(this, wxID_ANY, wxString::Format("%.2f", gp->getCrossoverRate()));
    maxInstructionsCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, gp->getMaxInstructions());
    maxStepsCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10000, gp->getMaxSteps());

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
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Mutation Rate:"), 0, wxTOP|wxLEFT, 10);
    mainSizer->Add(mutationRateCtrl, 0, wxEXPAND|wxLEFT|wxRIGHT, 10);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Crossover Rate:"), 0, wxTOP|wxLEFT, 10);
    mainSizer->Add(crossoverRateCtrl, 0, wxEXPAND|wxLEFT|wxRIGHT, 10);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Max Instructions:"), 0, wxTOP|wxLEFT, 10);
    mainSizer->Add(maxInstructionsCtrl, 0, wxEXPAND|wxLEFT|wxRIGHT, 10);
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Max Steps:"), 0, wxTOP|wxLEFT, 10);
    mainSizer->Add(maxStepsCtrl, 0, wxEXPAND|wxLEFT|wxRIGHT, 10);

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
    wxCommandEvent evt(EVT_RUN_SAVE);
    wxPostEvent(GetParent(), evt);
}

void ControlPanel::OnLoadParams(wxCommandEvent& event)
{
}

void ControlPanel::OnSaveParams(wxCommandEvent& event)
{
    
}

void ControlPanel::OnLoadEnv(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open Environment file"), "", "",
                                "Environment files (*.env)|*.env|All files (*.*)|*.*",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString path = openFileDialog.GetPath();

    try {
        std::shared_ptr<PacmanEnvironment> env = std::make_shared<PacmanEnvironment>("Pacman");
        env->load(path.ToStdString());
        env->setMaxSteps(gp->getMaxSteps());
        gp->SetEnvironment(env);
        
        wxMessageBox("Environment loaded successfully!", "Success", wxOK | wxICON_INFORMATION);

        wxCommandEvent evt(EVT_RUN_RESET);
        wxPostEvent(GetParent(), evt);
    } catch (const std::exception& e) {
        wxMessageBox(wxString::Format("Failed to load environment: %s", e.what()), 
                        "Error", wxOK | wxICON_ERROR);
    }
}

void ControlPanel::OnSaveEnv(wxCommandEvent& event)
{
}

void ControlPanel::OnSetParams(wxCommandEvent &event)
{
    gp->setPopulationSize(popSizeCtrl->GetValue());
    gp->setGenerations(generationsCtrl->GetValue());

    double mutationRate;
    if (mutationRateCtrl->GetValue().ToDouble(&mutationRate))
        gp->setMutationRate(mutationRate);

    double crossoverRate;
    if (crossoverRateCtrl->GetValue().ToDouble(&crossoverRate))
        gp->setCrossoverRate(crossoverRate);

    gp->setMaxInstructions(maxInstructionsCtrl->GetValue());
    gp->setMaxSteps(maxStepsCtrl->GetValue());

    wxCommandEvent evt(EVT_RUN_RESET);
    wxPostEvent(GetParent(), evt);
}

void ControlPanel::OnResetParams(wxCommandEvent &event)
{
    popSizeCtrl->SetValue(gp->getPopulationSize());
    generationsCtrl->SetValue(gp->getGenerations());
    mutationRateCtrl->SetValue(wxString::Format("%.2f", gp->getMutationRate()));
    crossoverRateCtrl->SetValue(wxString::Format("%.2f", gp->getCrossoverRate()));
    maxInstructionsCtrl->SetValue(gp->getMaxInstructions());
    maxStepsCtrl->SetValue(gp->getMaxSteps());
}
