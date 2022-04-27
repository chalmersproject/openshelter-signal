#include <external_library_includes.h>
#ifndef UPDATE_GUISLICE_H
#define UPDATE_GUISLICE_H
void update_all_GSlice_UI()
{   
    // update signal measurement type E_ELEM_TEXT1
    char string_to_write[MAX_STR];
    snprintf(string_to_write, MAX_STR, "%u", signal_class);
    gslc_ElemSetTxtStr(&m_gui, m_pELEM_TEXT1, string_to_write);
    
    // update occupancy number
    snprintf(string_to_write, MAX_STR, "%u", occupancy);
    gslc_ElemSetTxtStr(&m_gui, m_pElemVal2, string_to_write);
    
    // update capacity number
    snprintf(string_to_write, MAX_STR, "%u", capacity);
    gslc_ElemSetTxtStr(&m_gui, m_pElemVal2_3, string_to_write);

    // update ring gauge
    int gauge_pos = map(occupancy, 0, capacity, 0, 100);
    gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGauge1, gauge_pos);
    gslc_Update(&m_gui);
}
#endif