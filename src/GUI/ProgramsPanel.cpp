#include "ProgramsPanel.h"

#include <wx/stattext.h>
#include <wx/itemattr.h>

#include <iostream>
#include <iomanip>

#include "CustomEvents.h"

void ProgramsPanel::OnSearch(wxCommandEvent &evt)
{
    // Check if searched index is correct
    wxString query = searchBox->GetValue().Lower();
    int val;
    if(!query.ToInt(&val))
        return;

    // Ensure val is in range
    int popSize = gp->getPopulationSize();
    if (val < 0 || val >= popSize)
        return;

    // Center around val, but clamp within bounds
    int halfWindow = MAX_PROGRAMS_LISTED / 2;
    int start = std::max(0, val - halfWindow);
    int end = start + MAX_PROGRAMS_LISTED;

    // If at the end, shift window back
    if (end > popSize) {
        end = popSize;
        start = std::max(0, end - MAX_PROGRAMS_LISTED);
    }

    programList->DeleteAllItems();
    SetProgramList(start, end);
}

void ProgramsPanel::OnProgramSelected(wxCommandEvent &evt)
{
    int sel = programList->GetSelectedRow();
    if (sel == wxNOT_FOUND) return;

    // Get the actual program index from the first column
    wxVariant variant;
    programList->GetValue(variant, sel, 0);
    int idx = std::stoi(variant.GetString().ToStdString());

    DisplayProgram(idx);
}

void ProgramsPanel::start(wxCommandEvent &event)
{
}

void ProgramsPanel::step(wxCommandEvent &event)
{
}

void ProgramsPanel::end(wxCommandEvent &event)
{
    SetProgramList(startProgramIdx, endProgramIdx);
}

void ProgramsPanel::reset(wxCommandEvent &event)
{
    // Reset program list
    SetProgramList(0, gp->getPopulationSize());
}

ProgramsPanel::ProgramsPanel(std::shared_ptr<GPSystem> gp,
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

    // Main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Left side: program list
    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);

    // Search bar
    searchBox = new wxTextCtrl(this, wxID_ANY);
    searchBox->SetHint("Enter index");
    searchBox->SetBackgroundColour(wxColour(40, 40, 40));
    searchBox->SetForegroundColour(wxColour(200, 200, 200));

    // Program list
    programList = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(300, 500));
    programList->SetBackgroundColour(wxColour(40, 40, 40));
    programList->SetForegroundColour(wxColour(200, 200, 200));
    
    // Create and associate custom data model for sorting
    programListStore = new CustomDataViewModel();
    programList->AssociateModel(programListStore);
    
    // Add data columns
    programList->AppendTextColumn("Index", wxDATAVIEW_CELL_INERT, 80, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
    programList->AppendTextColumn("Fitness", wxDATAVIEW_CELL_INERT, 120, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
    programList->AppendTextColumn("Size", wxDATAVIEW_CELL_INERT, 80, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
    
    // Finish left side setup
    leftSizer->Add(searchBox, 0, wxEXPAND | wxALL, 5);
    leftSizer->Add(programList, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(leftSizer, 1, wxEXPAND);

    // Right side: Program info and instructions
    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    // Program info
    programInfoIndex = new wxStaticText(this, wxID_ANY, "Select a program");
    programInfoFitness = new wxStaticText(this, wxID_ANY, "");
    programInfoSize = new wxStaticText(this, wxID_ANY, "");
    
    // Instructions
    instructionScroll = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    instructionScroll->SetScrollRate(0, 10);
    instructionSizer = new wxBoxSizer(wxVERTICAL);
    instructionScroll->SetSizer(instructionSizer);
    
    // Finish right side setup
    rightSizer->Add(programInfoIndex, 0, wxEXPAND | wxALL, 5);
    rightSizer->Add(programInfoFitness, 0, wxEXPAND | wxALL, 5);
    rightSizer->Add(programInfoSize, 0, wxEXPAND | wxALL, 5);
    rightSizer->Add(instructionScroll, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(rightSizer, 2, wxEXPAND);

    // Finish setting up sizer
    SetSizer(mainSizer);

    // Event bindings
    searchBox->Bind(wxEVT_TEXT, &ProgramsPanel::OnSearch, this);
    programList->Bind(wxEVT_DATAVIEW_SELECTION_CHANGED, &ProgramsPanel::OnProgramSelected, this);

    // Initial program list
    SetProgramList(0, gp->getPopulationSize());

    // Bind GPSystem events
    Bind(EVT_RUN_STARTED, &ProgramsPanel::start, this);
    Bind(EVT_RUN_STEP, &ProgramsPanel::step, this);
    Bind(EVT_RUN_ENDED, &ProgramsPanel::end, this);
    Bind(EVT_RUN_RESET, &ProgramsPanel::reset, this);
}

void ProgramsPanel::SetProgramList(const int startIdx, const int endIdx)
{
    // Clear out old programs
    programList->DeleteAllItems();

    startProgramIdx = startIdx;
    endProgramIdx = endIdx;

    // Create new program list, each row has program idx, fitness, and size
    for (int i = startIdx; i < endIdx; ++i)
    {
        wxVector<wxVariant> row;
        row.push_back(wxString::Format("%d", i));
        row.push_back(wxString::Format("%d", gp->getProgramFitness(i)));
        row.push_back(wxString::Format("%d", gp->getProgramSize(i)));
        programList->AppendItem(row);
    }
}

void ProgramsPanel::DisplayProgram(int index)
{
    programInfoIndex->SetLabel("Index: " + std::to_string(index));
    programInfoFitness->SetLabel("Fitness: " + std::to_string(gp->getProgramFitness(index)));
    programInfoSize->SetLabel("Size: " + std::to_string(gp->getProgramSize(index)));

    // Clear old instructions
    instructionSizer->Clear(true);

    // Add new instructions
    std::vector<std::string> instructions = gp->getProgramInststructions(index);
    for (const auto& line : instructions)
    {
        wxStaticText* label = new wxStaticText(instructionScroll, wxID_ANY, line);
        instructionSizer->Add(label, 0, wxTOP | wxLEFT, 2);
    }

    instructionScroll->Layout();
    instructionScroll->FitInside();
}
