#pragma once

#include <wx/panel.h>
#include <wx/dataview.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/scrolwin.h>

#include <memory>

#include "CustomDataViewModel.h"
#include "GPSystem.h"

class ProgramsPanel : public wxPanel
{
private:
    std::shared_ptr<GPSystem> gp;

    wxTextCtrl* searchBox;
    wxDataViewListCtrl* programList;
    CustomDataViewModel* programListStore;
    wxStaticText* programInfoIndex;
    wxStaticText* programInfoFitness;
    wxStaticText* programInfoSize;
    wxScrolledWindow* instructionScroll;
    wxBoxSizer* instructionSizer;

    void OnSearch(wxCommandEvent& evt);
    void OnProgramSelected(wxCommandEvent& evt);

    int startProgramIdx = 0;
    int endProgramIdx = 0;

    const int MAX_PROGRAMS_LISTED = 200;
    
    void start(wxCommandEvent& event);
    void step(wxCommandEvent& event);
    void end(wxCommandEvent& event);
    void reset(wxCommandEvent& event);

public:
    ProgramsPanel(std::shared_ptr<GPSystem> gp,
        wxWindow *parent, 
        wxWindowID id=wxID_ANY, 
        const wxPoint &pos=wxDefaultPosition, 
        const wxSize &size=wxDefaultSize, 
        long style=wxTAB_TRAVERSAL, 
        const wxString &name=wxPanelNameStr);

    void SetProgramList(const int startIdx, const int endIdx);
    void DisplayProgram(int index);
};