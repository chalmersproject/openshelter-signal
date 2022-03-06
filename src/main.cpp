//////////////////////////////////////////////////////////
//            CHALMERS SIGNAL OCCUPANCY                 //
//////////////////////////////////////////////////////////
/*
The Chalmers Signal Occuapncy Device is a client tally counter
for shelter reception staff.

Written and Maintained by the Chalmers project info@chalmersproject.com
F/OSS under M.I.T License
*/

#include <external_library_includes.h>
// globals and attributes
#include <globals/attributes.h>
#include <globals/globals.h>

// API secret and shelter ID
#include <shelter_secrets.h>

// subroutines
#include "subroutines/connect_to_wifi.h"
#include "subroutines/sync_to_cloud.h"
// #include "subroutines/support_button_clicked.h"

///////////////////////////////////////////////////////////////////////////////////////////
//                    Rotary Encoder Interrupt                                           //
///////////////////////////////////////////////////////////////////////////////////////////

void ICACHE_RAM_ATTR encoder_change_trigger()
{
  encoder.tick();
  Serial.println("interrupt triggered!");
}

void ICACHE_RAM_ATTR encoder_button_trigger()
{
  encoder_button_pressed = true;
  Serial.println("encoder button was pressed!");
}

///////////////////////////////////////////////////////////////////////////////////////////
//                    MAIN SCRIPT STARTS HERE                                            //
///////////////////////////////////////////////////////////////////////////////////////////

void update_all_GSlice_UI()
{
  char string_to_write[MAX_STR];
  snprintf(string_to_write, MAX_STR, "%u", occupancy);
  gslc_ElemSetTxtStr(&m_gui, m_pElemVal2, string_to_write);

  snprintf(string_to_write, MAX_STR, "%u", capacity);
  gslc_ElemSetTxtStr(&m_gui, m_pElemVal2_3, string_to_write);

  int gauge_pos = map(occupancy, 0, capacity, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGauge1, gauge_pos);
  gslc_Update(&m_gui);
}

void update_LEDs()
{
  hue = map(occupancy, 0, capacity, 90, 0);
  CHSV color = CHSV(hue, 255, 255);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  change_to_push = true;
}

#define encoder_button_pin 0

void setup()
{
  pinMode(encoder_button_pin, INPUT_PULLUP);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(4), encoder_change_trigger, CHANGE);
  attachInterrupt(digitalPinToInterrupt(5), encoder_change_trigger, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(encoder_button_pin), encoder_button_trigger, ONLOW);

  // TODO
  // chalmers START screen
  //
  gslc_InitDebug(&DebugOut);
  if (enable_internet == true)
  {

    // ------------------------------------------------
    // Create graphic elements
    // ------------------------------------------------
    InitGUIslice_gen();
    gslc_SetPageCur(&m_gui, E_PG_WIFICON);
    gslc_Update(&m_gui);
    initWifi();
    client.setInsecure();

    if (WiFi.status() == WL_CONNECTED)
    {
      delay(4000);

      // pull latest occupancy capacity numbers from remote and set them to the display
      // occupancy_request(client, "pull", occupancy, capacity); //
      // Update OCCUPANCY and CAPACITY GUI numbers
      Serial.println("SAYING WIFI CONNECTED");
      gslc_SetPageCur(&m_gui, E_PG_MAIN);
      Serial.println("UPDATING GUISLICE UI");
      update_all_GSlice_UI();
    }

    // TODO:
    // verify connection to api.chalmersproject.com
    //
  }

  //
  // start LED with color of occupancy / capacity
  //
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(led_brightness);

  hue = map(occupancy, 0, capacity, 90, 0);
  CHSV color = CHSV(hue, 255, 255);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  Serial.println("END OF SETUP");
}

void loop()
{
  static int pos = 0;
  Serial.println("CHECKING POSITION OF DIAL");
  int newPos = encoder.getPosition();
  if (pos != newPos)
  {
    Serial.print("Pos: ");
    Serial.print(newPos);
    Serial.println();
    if (pos > newPos)
    {
      occupancy--;
    }
    else if (newPos > pos)
    {
      occupancy++;
    }
    Serial.print("occupancy: ");
    Serial.print(occupancy);
    Serial.println();
    pos = newPos;

    // set barriers on occupancy
    if (0 >= occupancy)
    {
      occupancy = 0;
    }
    else if (occupancy >= capacity)
    {
      occupancy = capacity;
    }
    Serial.println("UPDATING GUISLICE UI");
    update_all_GSlice_UI();
    update_LEDs();
    Serial.println("UPDATING TIMERS last_change_time and last_occupancy");
    last_change_time = now;
    last_occupancy = occupancy;
  }

  //
  // wait at least 3 seconds since last change before pushing to api.chalmers.project
  //
  now = millis();
  // push_to_cloud(now, last, client, push_wait, enable_internet, occupancy, capacity);
  // push_to_cloud();
  // pull_from_cloud(now, last_change_time, client, pull_wait, enable_internet, occupancy, capacity);
  // support_button_clicked(encoder_button_pin, now, encoder_button_timer);
}
