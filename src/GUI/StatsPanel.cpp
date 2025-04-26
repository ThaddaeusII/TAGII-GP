#include "StatsPanel.h"

#include "CustomEvents.h"

void StatsPanel::ClearStatsDisplay()
{
    popText->SetLabel(wxString::Format("Population size: "));
    genText->SetLabel(wxString::Format("Generations: %d", totalGenerations));
    bestFitnessText->SetLabel(wxString::Format("Best fitness: "));
    avgFitnessText->SetLabel(wxString::Format("Average fitness: "));
    bestProgramText->SetLabel(wxString::Format("Best program index: "));
    largestProgramSizeText->SetLabel(wxString::Format("Largest program size: "));
    smallestProgramSizeText->SetLabel(wxString::Format("Smallest program size: "));
    averageProgramSizeText->SetLabel(wxString::Format("Average program size: "));
}

void StatsPanel::UpdateStatsDisplay()
{
    GPSystem::GPStats stats = gp->getStats();
    popText->SetLabel(wxString::Format("Population size: %d", gp->getPopulationSize()));
    genText->SetLabel(wxString::Format("Generations: %d", totalGenerations));
    bestFitnessText->SetLabel(wxString::Format("Best fitness: %d", stats.bestFitness));
    avgFitnessText->SetLabel(wxString::Format("Average fitness: %0.3f", stats.avgFitness));
    bestProgramText->SetLabel(wxString::Format("Best program index: %d", stats.bestProgram));
    largestProgramSizeText->SetLabel(wxString::Format("Largest program size: %d", stats.largestProgramSize));
    smallestProgramSizeText->SetLabel(wxString::Format("Smallest program size: %d", stats.smallestProgramSize));
    averageProgramSizeText->SetLabel(wxString::Format("Average program size: %0.3f", stats.avgProgramSize));
}

void StatsPanel::UpdateGraph()
{
}

void StatsPanel::start(wxCommandEvent &event)
{
    ClearStatsDisplay();
}

void StatsPanel::step(wxCommandEvent &event)
{
    totalGenerations += 1;
    AddGenerationStats();
    
    genText->SetLabel(wxString::Format("Generations: %d", totalGenerations));
    genText->Refresh();
    genText->Update();
}

void StatsPanel::end(wxCommandEvent &event)
{
    UpdateStatsDisplay();
    UpdateGraph();
}

void StatsPanel::reset(wxCommandEvent &event)
{
    ClearStats();
    AddGenerationStats();
    UpdateStatsDisplay();
    UpdateGraph();
}

StatsPanel::StatsPanel(std::shared_ptr<GPSystem> gp,
                       wxWindow *parent,
                       wxWindowID id,
                       const wxPoint &pos,
                       const wxSize &size,
                       long style,
                       const wxString &name)
    : wxPanel(parent, id, pos, size, style, name), gp(gp)
{
    this->SetBackgroundColour(wxColour(40, 40, 40));
    this->SetForegroundColour(wxColour(200, 200, 200));

    popText = new wxStaticText(this, wxID_ANY, "");
    genText = new wxStaticText(this, wxID_ANY, "");
    bestFitnessText = new wxStaticText(this, wxID_ANY, "");
    avgFitnessText = new wxStaticText(this, wxID_ANY, "");
    bestProgramText = new wxStaticText(this, wxID_ANY, "");
    largestProgramSizeText = new wxStaticText(this, wxID_ANY, "");
    smallestProgramSizeText = new wxStaticText(this, wxID_ANY, "");
    averageProgramSizeText = new wxStaticText(this, wxID_ANY, "");
    ClearStatsDisplay();

    wxBoxSizer* statsSizer = new wxBoxSizer(wxVERTICAL);
    statsSizer->Add(popText, 0, wxALL, 5);
    statsSizer->Add(genText, 0, wxALL, 5);
    statsSizer->Add(bestFitnessText, 0, wxALL, 5);
    statsSizer->Add(avgFitnessText, 0, wxALL, 5);
    statsSizer->Add(bestProgramText, 0, wxALL, 5);
    statsSizer->Add(largestProgramSizeText, 0, wxALL, 5);
    statsSizer->Add(smallestProgramSizeText, 0, wxALL, 5);
    statsSizer->Add(averageProgramSizeText, 0, wxALL, 5);

    // Add GRAPHS !!!

    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(statsSizer, 0, wxEXPAND | wxALL, 5);

    SetSizer(mainSizer);

    // Add initial generation's stats
    totalGenerations = 0;
    AddGenerationStats();
    UpdateStatsDisplay();
    UpdateGraph();

    // Bind GPSystem events
    Bind(EVT_RUN_STARTED, &StatsPanel::start, this);
    Bind(EVT_RUN_STEP, &StatsPanel::step, this);
    Bind(EVT_RUN_ENDED, &StatsPanel::end, this);
    Bind(EVT_RUN_RESET, &StatsPanel::reset, this);
}

void StatsPanel::AddGenerationStats()
{
    // Update stat tracking with current generation's stats
    GPSystem::GPStats stats = gp->getStats();
    bestFitnessHistory.push_back(stats.bestFitness);
    avgFitnessHistory.push_back(stats.avgFitness);
    bestProgramHistory.push_back(stats.bestProgram);
    largestProgramSizeHistory.push_back(stats.largestProgramSize);
    smallestProgramSizeHistory.push_back(stats.smallestProgramSize);
    averageProgramSizeHistory.push_back(stats.avgProgramSize);
}

void StatsPanel::ClearStats()
{
    totalGenerations = 0;
    bestFitnessHistory.clear();
    avgFitnessHistory.clear();
    bestProgramHistory.clear();
    largestProgramSizeHistory.clear();
    smallestProgramSizeHistory.clear();
    averageProgramSizeHistory.clear();
}
