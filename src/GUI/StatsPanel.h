#pragma once

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

#include <memory>
#include <vector>

#include "GPSystem.h"

class StatsPanel : public wxPanel
{
private:
    std::shared_ptr<GPSystem> gp;

    int totalGenerations = 0;

    wxStaticText* popText;
    wxStaticText* genText;
    wxStaticText* bestFitnessText;
    wxStaticText* avgFitnessText;
    wxStaticText* bestProgramText;
    wxStaticText* largestProgramSizeText;
    wxStaticText* smallestProgramSizeText;
    wxStaticText* averageProgramSizeText;
    
    wxBoxSizer* mainSizer;

    std::vector<int> bestFitnessHistory;
    std::vector<double> avgFitnessHistory;
    std::vector<int> bestProgramHistory;
    std::vector<int> largestProgramSizeHistory;
    std::vector<int> smallestProgramSizeHistory;
    std::vector<double> averageProgramSizeHistory;

    void ClearStatsDisplay();
    void UpdateStatsDisplay();
    void UpdateGraph();

    void start(wxCommandEvent& event);
    void step(wxCommandEvent& event);
    void end(wxCommandEvent& event);
    void reset(wxCommandEvent& event);

public:
    StatsPanel(std::shared_ptr<GPSystem> gp,
        wxWindow *parent, 
        wxWindowID id=wxID_ANY, 
        const wxPoint &pos=wxDefaultPosition, 
        const wxSize &size=wxDefaultSize, 
        long style=wxTAB_TRAVERSAL, 
        const wxString &name=wxPanelNameStr);

    void AddGenerationStats();
    void ClearStats();
};