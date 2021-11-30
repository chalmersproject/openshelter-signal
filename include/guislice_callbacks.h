// Common Button callback
bool CbBtnCommon(void *pvGui, void *pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY)
{
    // Typecast the parameters to match the GUI and element types
    gslc_tsGui *pGui = (gslc_tsGui *)(pvGui);
    gslc_tsElemRef *pElemRef = (gslc_tsElemRef *)(pvElemRef);
    gslc_tsElem *pElem = gslc_GetElemFromRef(pGui, pElemRef);

    if (eTouch == GSLC_TOUCH_UP_IN)
    {
        // From the element's ID we can determine which button was pressed.
        switch (pElem->nId)
        {
            //<Button Enums !Start!>
        case CAPACITY_NUM_MONITOR:
            // Clicked on edit field, so show popup box and associate with this text field
            gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadNum, E_POP_KEYPAD_NUM, m_pElemVal2);
            break;
            //<Button Enums !End!>
        default:
            break;
        }
    }
    return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
// KeyPad Input Ready callback
bool CbKeypad(void *pvGui, void *pvElemRef, int16_t nState, void *pvData)
{
    gslc_tsGui *pGui = (gslc_tsGui *)pvGui;
    gslc_tsElemRef *pElemRef = (gslc_tsElemRef *)(pvElemRef);
    gslc_tsElem *pElem = gslc_GetElemFromRef(pGui, pElemRef);

    // From the pvData we can get the ID element that is ready.
    int16_t nTargetElemId = gslc_ElemXKeyPadDataTargetIdGet(pGui, pvData);
    if (nState == XKEYPAD_CB_STATE_DONE)
    {
        // User clicked on Enter to leave popup
        // - If we have a popup active, pass the return value directly to
        //   the corresponding value field
        switch (nTargetElemId)
        {
            //<Keypad Enums !Start!>
        case CAPACITY_NUM_MONITOR:
            gslc_ElemXKeyPadInputGet(pGui, m_pElemVal2, pvData);
            gslc_PopupHide(&m_gui);
            break;

            //<Keypad Enums !End!>
        default:
            break;
        }
    }
    else if (nState == XKEYPAD_CB_STATE_CANCEL)
    {
        // User escaped from popup, so don't update values
        gslc_PopupHide(&m_gui);
    }
    return true;
}