#include "ControlPanel.h"

ControlPanel::ControlPanel(std::shared_ptr<GPSystem> gp,
    wxWindow *parent,
    wxWindowID id,
    const wxPoint &pos,
    const wxSize &size,
    long style,
    const wxString &name)
    : wxPanel(parent, id, pos, size, style, name)
{
}
