// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef *m_pELEM_TEXT1 = NULL;
gslc_tsElemRef *m_pElemVal2 = NULL;
gslc_tsElemRef *m_pElemVal2_3 = NULL;
gslc_tsElemRef *m_pElemVal2_5 = NULL;
gslc_tsElemRef *m_pElemXRingGauge1 = NULL;
gslc_tsElemRef *m_pElemKeyPadNum = NULL;

// Define debug message function
static int16_t DebugOut(char ch)
{
    if (ch == (char)'\n')
        Serial.println("");
    else
        Serial.write(ch);
    return 0;
}