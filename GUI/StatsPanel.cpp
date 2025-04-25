#include "StatsPanel.h"

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
}