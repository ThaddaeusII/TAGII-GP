#pragma once

#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>

#include <memory>
#include "GPSystem.h"

class ControlPanel : public wxPanel
{
private:
    std::shared_ptr<GPSystem> gp;

    // Buttons
    wxButton* runButton;
    wxButton* resetButton;
    wxButton* saveRunButton;
    wxButton* loadParamsButton;
    wxButton* saveParamsButton;
    wxButton* loadEnvButton;
    wxButton* saveEnvButton;
    wxButton* setParamsButton;
    wxButton* resetParamsButton;

    // Configurable Parameters
    wxSpinCtrl* popSizeCtrl;
    wxSpinCtrl* generationsCtrl;

    // Event handlers
    void OnRun(wxCommandEvent& event);
    void OnReset(wxCommandEvent& event);
    void OnSaveRun(wxCommandEvent& event);
    void OnLoadParams(wxCommandEvent& event);
    void OnSaveParams(wxCommandEvent& event);
    void OnLoadEnv(wxCommandEvent& event);
    void OnSaveEnv(wxCommandEvent& event);
    void OnSetParams(wxCommandEvent& event);
    void OnResetParams(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();

public:
    ControlPanel(std::shared_ptr<GPSystem> gp,
        wxWindow *parent, 
        wxWindowID id=wxID_ANY, 
        const wxPoint &pos=wxDefaultPosition, 
        const wxSize &size=wxDefaultSize, 
        long style=wxTAB_TRAVERSAL, 
        const wxString &name=wxPanelNameStr);

};