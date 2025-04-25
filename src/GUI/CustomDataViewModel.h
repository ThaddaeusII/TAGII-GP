#pragma once

#include <wx/dataview.h>

class CustomDataViewModel : public wxDataViewListStore
{
public:
    CustomDataViewModel() : wxDataViewListStore() {}
    
    int Compare(const wxDataViewItem& item1, const wxDataViewItem& item2,
                unsigned int column, bool ascending) const override;
};