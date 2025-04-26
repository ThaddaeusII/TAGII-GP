#include "EnvironmentPanel.h"

#include "CustomEvents.h"

void EnvironmentPanel::start(wxCommandEvent &event)
{
}

void EnvironmentPanel::step(wxCommandEvent &event)
{
}

void EnvironmentPanel::end(wxCommandEvent &event)
{
}

void EnvironmentPanel::reset(wxCommandEvent &event)
{
}

EnvironmentPanel::EnvironmentPanel(std::shared_ptr<GPSystem> gp,
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

    // Bind GPSystem events
    Bind(EVT_RUN_STARTED, &EnvironmentPanel::start, this);
    Bind(EVT_RUN_STEP, &EnvironmentPanel::step, this);
    Bind(EVT_RUN_ENDED, &EnvironmentPanel::end, this);
    Bind(EVT_RUN_RESET, &EnvironmentPanel::reset, this);
}
