#pragma once

#include <wx/wx.h>
#include <wx/panel.h>

class CustomStaticLine : public wxPanel
{
public:
    CustomStaticLine(wxWindow* parent, wxColour color = *wxBLACK, int thickness = 1)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE),
          m_color(color), m_thickness(thickness)
    {
        SetMinSize(wxSize(-1, thickness)); // Default horizontal
        Bind(wxEVT_PAINT, &CustomStaticLine::OnPaint, this);
    }

private:
    void OnPaint(wxPaintEvent&)
    {
        wxPaintDC dc(this);
        dc.SetPen(wxPen(m_color, m_thickness));
        dc.DrawLine(0, 0, GetSize().x, 0); // Horizontal line
    }

    wxColour m_color;
    int m_thickness;
};