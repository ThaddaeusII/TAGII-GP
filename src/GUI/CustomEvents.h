#pragma once

#include <wx/wx.h>

// Define new event types
wxDECLARE_EVENT(EVT_RUN_STARTED, wxCommandEvent);
wxDECLARE_EVENT(EVT_RUN_STEP, wxCommandEvent);
wxDECLARE_EVENT(EVT_RUN_ENDED, wxCommandEvent);
wxDECLARE_EVENT(EVT_RUN_RESET, wxCommandEvent);
wxDECLARE_EVENT(EVT_RUN_SAVE, wxCommandEvent);