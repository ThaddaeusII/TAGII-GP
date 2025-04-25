#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>

#include "ControlPanel.h"
#include "MainPanel.h"

#include <memory>

#include "GPSystem.h"

class Mainframe : public wxFrame
{
private:
    std::shared_ptr<GPSystem> gp;

    wxSplitterWindow* mainSplitter;
    ControlPanel* controlPanel;
    MainPanel* mainPanel;

public:
    Mainframe(wxWindow* parent,
        wxWindowID id = wxID_ANY,
        const wxString& title = "TAGII-GP",
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxSize(1200,800),
        long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
	~Mainframe();

    void mainSplitterOnIdle(wxIdleEvent&);
    void SetTheme();
};