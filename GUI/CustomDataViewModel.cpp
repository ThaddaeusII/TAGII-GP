#include "CustomDataViewModel.h"

int CustomDataViewModel::Compare(const wxDataViewItem &item1, const wxDataViewItem &item2, unsigned int column, bool ascending) const
{
    wxVariant value1, value2;
    GetValue(value1, item1, column);
    GetValue(value2, item2, column);
    int val1 = value1.GetInteger();
    int val2 = value2.GetInteger();

    if (ascending)
        return (val1 < val2) ? -1 : (val1 > val2) ? 1 : 0;
    else
        return (val1 > val2) ? -1 : (val1 < val2) ? 1 : 0;
}