//<File !Start!>
// FILE: [GUIsliceProjects_GSLC.h]
// Created by GUIslice Builder version: [0.16.b009]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XKeyPad_Num.h"
#include "elem/XRingGauge.h"

// Ensure optional features are enabled in the configuration
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
#error Project tab->Target Platform should be arduino
#endif
#include <TFT_eSPI.h>
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum
{
  E_PG_MAIN,
  E_PG_WIFICON,
  E_PG_CLOUDSYNC,
  E_PG_SUPPORTCALL,
  E_PG_SUPPORTSENT,
  E_POP_KEYPAD_NUM
};
enum
{
  CAPACITY_NUM_MONITOR,
  E_DRAW_LINE1,
  E_DRAW_LINE2,
  E_ELEM_BOX1,
  E_ELEM_BOX2,
  E_ELEM_BOX4,
  E_ELEM_NUMINPUT3,
  E_ELEM_NUMINPUT5,
  E_ELEM_TEXT1,
  E_ELEM_TEXT10,
  E_ELEM_TEXT11,
  E_ELEM_TEXT12,
  E_ELEM_TEXT13,
  E_ELEM_TEXT14,
  E_ELEM_TEXT18,
  E_ELEM_TEXT19,
  E_ELEM_TEXT4,
  E_ELEM_TEXT5,
  E_ELEM_TEXT6,
  E_ELEM_TEXT7,
  E_ELEM_TEXT8,
  E_ELEM_TEXT9,
  OCCUPANCY_GAGE,
  E_ELEM_KEYPAD_NUM
};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum
{
  E_BUILTIN5X8,
  E_FREESANS18,
  E_FREESANS9,
  E_FREESANSBOLD9,
  MAX_FONT
};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE 6

#define MAX_ELEM_PG_MAIN 5                    // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_WIFICON 7                       // # Elems total on page
#define MAX_ELEM_PG_WIFICON_RAM MAX_ELEM_PG_WIFICON // # Elems in RAM

#define MAX_ELEM_PG_CLOUDSYNC 4                         // # Elems total on page
#define MAX_ELEM_PG_CLOUDSYNC_RAM MAX_ELEM_PG_CLOUDSYNC // # Elems in RAM

#define MAX_ELEM_PG_SUPPORTCALL 4                           // # Elems total on page
#define MAX_ELEM_PG_SUPPORTCALL_RAM MAX_ELEM_PG_SUPPORTCALL // # Elems in RAM

#define MAX_ELEM_PG_SUPPORTSENT 3                           // # Elems total on page
#define MAX_ELEM_PG_SUPPORTSENT_RAM MAX_ELEM_PG_SUPPORTSENT // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui m_gui;
gslc_tsDriver m_drv;
gslc_tsFont m_asFont[MAX_FONT];
gslc_tsPage m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem m_asPopup1Elem[MAX_ELEM_PG_WIFICON_RAM];
gslc_tsElemRef m_asPopup1ElemRef[MAX_ELEM_PG_WIFICON];
gslc_tsElem m_asPopup2Elem[MAX_ELEM_PG_CLOUDSYNC_RAM];
gslc_tsElemRef m_asPopup2ElemRef[MAX_ELEM_PG_CLOUDSYNC];
gslc_tsElem m_asPopup3Elem[MAX_ELEM_PG_SUPPORTCALL_RAM];
gslc_tsElemRef m_asPopup3ElemRef[MAX_ELEM_PG_SUPPORTCALL];
gslc_tsElem m_asPopup4Elem[MAX_ELEM_PG_SUPPORTSENT_RAM];
gslc_tsElemRef m_asPopup4ElemRef[MAX_ELEM_PG_SUPPORTSENT];
gslc_tsElem m_asKeypadNumElem[1];
gslc_tsElemRef m_asKeypadNumElemRef[1];
gslc_tsXKeyPad m_sKeyPadNum;
gslc_tsXRingGauge m_sXRingGauge1;

#define MAX_STR 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef *m_pElemText1;
extern gslc_tsElemRef *m_pElemVal2;
extern gslc_tsElemRef *m_pElemVal2_3;
extern gslc_tsElemRef *m_pElemVal2_5;
extern gslc_tsElemRef *m_pElemXRingGauge1;
extern gslc_tsElemRef *m_pElemKeyPadNum;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void *pvGui, void *pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY);
// #ifndef CbBtnCommon
// #error CbBtnCommon is not defined
// #endif
bool CbCheckbox(void *pvGui, void *pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void *pvGui, void *pvElemRef, gslc_teRedrawType eRedraw);
bool CbKeypad(void *pvGui, void *pvElemRef, int16_t nState, void *pvData);
bool CbListbox(void *pvGui, void *pvElemRef, int16_t nSelId);
bool CbSlidePos(void *pvGui, void *pvElemRef, int16_t nPos);
bool CbSpinner(void *pvGui, void *pvElemRef, int16_t nState, void *pvData);
bool CbTickScanner(void *pvGui, void *pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen()
{
  gslc_tsElemRef *pElemRef = NULL;

  if (!gslc_Init(&m_gui, &m_drv, m_asPage, MAX_PAGE, m_asFont, MAX_FONT))
  {
    return;
  }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
  //<Load_Fonts !Start!>
  if (!gslc_FontSet(&m_gui, E_BUILTIN5X8, GSLC_FONTREF_PTR, NULL, 1))
  {
    return;
  }
  if (!gslc_FontSet(&m_gui, E_FREESANS18, GSLC_FONTREF_PTR, &FreeSans18pt7b, 1))
  {
    return;
  }
  if (!gslc_FontSet(&m_gui, E_FREESANS9, GSLC_FONTREF_PTR, &FreeSans9pt7b, 1))
  {
    return;
  }
  if (!gslc_FontSet(&m_gui, E_FREESANSBOLD9, GSLC_FONTREF_PTR, &FreeSansBold9pt7b, 1))
  {
    return;
  }
  //<Load_Fonts !End!>

  //<InitGUI !Start!>
  gslc_PageAdd(&m_gui, E_PG_MAIN, m_asPage1Elem, MAX_ELEM_PG_MAIN_RAM, m_asPage1ElemRef, MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui, E_PG_WIFICON, m_asPopup1Elem, MAX_ELEM_PG_WIFICON_RAM, m_asPopup1ElemRef, MAX_ELEM_PG_WIFICON);
  gslc_PageAdd(&m_gui, E_PG_CLOUDSYNC, m_asPopup2Elem, MAX_ELEM_PG_CLOUDSYNC_RAM, m_asPopup2ElemRef, MAX_ELEM_PG_CLOUDSYNC);
  gslc_PageAdd(&m_gui, E_PG_SUPPORTCALL, m_asPopup3Elem, MAX_ELEM_PG_SUPPORTCALL_RAM, m_asPopup3ElemRef, MAX_ELEM_PG_SUPPORTCALL);
  gslc_PageAdd(&m_gui, E_PG_SUPPORTSENT, m_asPopup4Elem, MAX_ELEM_PG_SUPPORTSENT_RAM, m_asPopup4ElemRef, MAX_ELEM_PG_SUPPORTSENT);
  gslc_PageAdd(&m_gui, E_POP_KEYPAD_NUM, m_asKeypadNumElem, 1, m_asKeypadNumElemRef, 1); // KeyPad

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui, E_PG_MAIN);

  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui, GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN

  // Create ring gauge OCCUPANCY_GAGE
  static char m_sRingText1[11] = "";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui, OCCUPANCY_GAGE, E_PG_MAIN, &m_sXRingGauge1,
                                       (gslc_tsRect){9, 26, 105, 105},
                                       (char *)m_sRingText1, 11, E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 20); // Set initial value
  gslc_ElemXRingGaugeSetAngleRange(&m_gui, pElemRef, 250, 220, true);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_CYAN, GSLC_COL_GREEN_DK4);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui, pElemRef, GSLC_COL_GRAY);
  m_pElemXRingGauge1 = pElemRef;

  // Create CAPACITY_NUM_MONITOR numeric input field
  static char m_sInputNumber2[5] = "123";
  pElemRef = gslc_ElemCreateTxt(&m_gui, CAPACITY_NUM_MONITOR, E_PG_MAIN, (gslc_tsRect){34, 50, 55, 27},
                                (char *)m_sInputNumber2, 5, E_FREESANS18);
  gslc_ElemSetTxtAlign(&m_gui, pElemRef, GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui, pElemRef, 5);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_GREEN);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui, pElemRef, true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal2 = pElemRef;

  // Create E_DRAW_LINE1 line
  pElemRef = gslc_ElemCreateLine(&m_gui, E_DRAW_LINE1, E_PG_MAIN, 37, 85, 87, 85);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_BLACK, GSLC_COL_GRAY_LT2, GSLC_COL_GRAY_LT2);

  // Create E_ELEM_TEXT1 text label
  static char m_sInpuSignalClass[15] = "SPOTS";
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT1, E_PG_MAIN, (gslc_tsRect){37, 5, 50, 15}, (char *)m_sInpuSignalClass, 15, E_FREESANSBOLD9);
  gslc_ElemSetTxtAlign(&m_gui, pElemRef, GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  m_pElemText1 = pElemRef;

  // Create E_ELEM_NUMINPUT3 numeric input field
  static char m_sInputNumber3[5] = "123";
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_NUMINPUT3, E_PG_MAIN, (gslc_tsRect){47, 90, 30, 15},
                                (char *)m_sInputNumber3, 5, E_FREESANS9);
  gslc_ElemSetTxtAlign(&m_gui, pElemRef, GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui, pElemRef, 5);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_CYAN);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui, pElemRef, true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal2_3 = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_WIFICON

  // Create E_ELEM_TEXT4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT4, E_PG_WIFICON, (gslc_tsRect){10, 10, 109, 10},
                                (char *)"Connecting to WiFi", 0, E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT9, E_PG_WIFICON, (gslc_tsRect){10, 25, 103, 10},
                                (char *)"Please Wait 60sec", 0, E_BUILTIN5X8);

  // Create E_DRAW_LINE2 line
  pElemRef = gslc_ElemCreateLine(&m_gui, E_DRAW_LINE2, E_PG_WIFICON, 10, 40, 110, 40);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_BLACK, GSLC_COL_GRAY_LT2, GSLC_COL_GRAY_LT2);

  // Create E_ELEM_TEXT5 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT5, E_PG_WIFICON, (gslc_tsRect){14, 60, 91, 10},
                                (char *)"else connect to", 0, E_BUILTIN5X8);

  // Create E_ELEM_TEXT8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT8, E_PG_WIFICON, (gslc_tsRect){22, 75, 73, 10},
                                (char *)"WiFi network", 0, E_BUILTIN5X8);

  // Create E_ELEM_TEXT6 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT6, E_PG_WIFICON, (gslc_tsRect){15, 93, 91, 10},
                                (char *)"Chalmers-Signal", 0, E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_GREEN);

  // Create E_ELEM_TEXT7 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT7, E_PG_WIFICON, (gslc_tsRect){20, 110, 79, 10},
                                (char *)"on your phone", 0, E_BUILTIN5X8);

  // -----------------------------------
  // PAGE: E_PG_CLOUDSYNC

  // Create E_ELEM_BOX1 box
  pElemRef = gslc_ElemCreateBox(&m_gui, E_ELEM_BOX1, E_PG_CLOUDSYNC, (gslc_tsRect){5, 40, 115, 48});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3);

  // Create E_ELEM_TEXT10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT10, E_PG_CLOUDSYNC, (gslc_tsRect){26, 50, 73, 10},
                                (char *)"SYNCING WITH", 0, E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3);

  // Create E_ELEM_TEXT11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT11, E_PG_CLOUDSYNC, (gslc_tsRect){5, 60, 115, 10},
                                (char *)"CHALMERSPROJECT.COM", 0, E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3);

  // Create E_ELEM_TEXT12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT12, E_PG_CLOUDSYNC, (gslc_tsRect){17, 72, 91, 10},
                                (char *)"**PLEASE WAIT**", 0, E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3);

  // -----------------------------------
  // PAGE: E_PG_SUPPORTCALL

  // Create E_ELEM_BOX2 box
  pElemRef = gslc_ElemCreateBox(&m_gui, E_ELEM_BOX2, E_PG_SUPPORTCALL, (gslc_tsRect){5, 30, 115, 60});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3);

  // Create E_ELEM_TEXT13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT13, E_PG_SUPPORTCALL, (gslc_tsRect){6, 40, 115, 10},
                                (char *)"calling for support", 0, E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3);
  gslc_ElemSetTxtEnc(&m_gui, pElemRef, GSLC_TXT_ENC_UTF8);

  // Create E_ELEM_TEXT14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT14, E_PG_SUPPORTCALL, (gslc_tsRect){10, 50, 31, 10},
                                (char *)"in...", 0, E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3);
  gslc_ElemSetTxtEnc(&m_gui, pElemRef, GSLC_TXT_ENC_UTF8);

  // Create E_ELEM_NUMINPUT5 numeric input field
  static char m_sInputNumber5[5] = "5";
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_NUMINPUT5, E_PG_SUPPORTCALL, (gslc_tsRect){60, 55, 30, 27},
                                (char *)m_sInputNumber5, 5, E_FREESANS18);
  gslc_ElemSetTxtAlign(&m_gui, pElemRef, GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui, pElemRef, 1);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_GREEN);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui, pElemRef, true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pElemVal2_5 = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_SUPPORTSENT

  // Create E_ELEM_BOX4 box
  pElemRef = gslc_ElemCreateBox(&m_gui, E_ELEM_BOX4, E_PG_SUPPORTSENT, (gslc_tsRect){4, 30, 115, 60});
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3);

  // Create E_ELEM_TEXT18 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT18, E_PG_SUPPORTSENT, (gslc_tsRect){16, 50, 91, 10},
                                (char *)"SUPPORT MESSAGE", 0, E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY);
  gslc_ElemSetTxtEnc(&m_gui, pElemRef, GSLC_TXT_ENC_UTF8);

  // Create E_ELEM_TEXT19 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT19, E_PG_SUPPORTSENT, (gslc_tsRect){46, 60, 31, 10},
                                (char *)"SENT!", 0, E_BUILTIN5X8);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui, pElemRef, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY_LT3, GSLC_COL_GRAY);
  gslc_ElemSetTxtEnc(&m_gui, pElemRef, GSLC_TXT_ENC_UTF8);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM

  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, true);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, true);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
                                                &m_sKeyPadNum, 65, 80, E_BUILTIN5X8, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);
  //<InitGUI !End!>

  //<Startup !Start!>
  gslc_GuiRotate(&m_gui, 0);
  //<Startup !End!>
}

#endif // end _GUISLICE_GEN_H
