#include "CustomEvents.h"

// Implement the events
wxDEFINE_EVENT(EVT_RUN_STARTED, wxCommandEvent);
wxDEFINE_EVENT(EVT_RUN_STEP, wxCommandEvent);
wxDEFINE_EVENT(EVT_RUN_ENDED, wxCommandEvent);
wxDEFINE_EVENT(EVT_RUN_RESET, wxCommandEvent);