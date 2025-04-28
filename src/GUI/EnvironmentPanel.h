#pragma once

#include <wx/panel.h>
#include <wx/timer.h>
#include <wx/button.h>
#include <wx/spinctrl.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>

#include <memory>
#include "GPSystem.h"

class EnvironmentPanel : public wxPanel
{
private:
    std::shared_ptr<GPSystem> gp;
    int programIndex = 0;

    wxTimer stepTimer;
    wxButton* startButton;
    wxButton* stopButton;
    wxButton* stepButton;
    wxButton* resetButton;
    wxSpinCtrl* programIndexCtrl;
    wxTextCtrl* envDisplay;
    wxTextCtrl* progDisplay;
    wxSplitterWindow* mainSplitter;
    wxPanel* leftPanel;
    wxPanel* rightPanel;

    // GP system events
    void start(wxCommandEvent& event);
    void step(wxCommandEvent& event);
    void end(wxCommandEvent& event);
    void reset(wxCommandEvent& event);
    
    // Program events
    void visualizeStart(wxCommandEvent &event);
    void visualizeStop(wxCommandEvent& event);
    void visualizeStep(wxCommandEvent& event);
    void visualizeReset(wxCommandEvent &event);
    void timerStep(wxTimerEvent& event);

    void onProgramIndexChange(wxSpinEvent& event);

    // Local reuse
    void programStep();
    void displayEnv();
    void displayProg();

public:
    EnvironmentPanel(std::shared_ptr<GPSystem> gp,
        wxWindow *parent, 
        wxWindowID id=wxID_ANY, 
        const wxPoint &pos=wxDefaultPosition, 
        const wxSize &size=wxDefaultSize, 
        long style=wxTAB_TRAVERSAL, 
        const wxString &name=wxPanelNameStr);

    void mainSplitterOnIdle(wxIdleEvent&);
};