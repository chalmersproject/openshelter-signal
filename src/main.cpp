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
#include <globals/interrupts.h>
// API secret and shelter ID
#include <shelter_secrets.h>

// subroutines
#include "subroutines/connect_to_wifi.h"
#include "subroutines/sync_to_cloud.h"
#include "subroutines/update_guislice.h"
// #include "subroutines/support_button_clicked.h"

///////////////////////////////////////////////////////////////////////////////////////////
//                    Rotary Encoder Interrupt                                           //
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
//                    MAIN SCRIPT STARTS HERE                                            //
///////////////////////////////////////////////////////////////////////////////////////////

void update_LEDs()
{
  hue = map(occupancy, 0, capacity, 90, 0);
  CHSV color = CHSV(hue, 255, 255);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  change_to_push = true;
}

void setup()
{
  Serial.begin(115200);
  init_interrupts();

  // TODO
  // chalmers START screen
  //
  gslc_InitDebug(&DebugOut);
  InitGUIslice_gen();
  if (enable_internet == true)
  {
    connect_to_wifi();
  }
  else
  {
    gslc_SetPageCur(&m_gui, E_PG_MAIN);
    update_all_GSlice_UI();
  }

  //
  // start LED with color of occupancy / capacity
  //
  // FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  // FastLED.setBrightness(led_brightness);

  // hue = map(occupancy, 0, capacity, 90, 0);
  // CHSV color = CHSV(hue, 255, 255);
  // fill_solid(leds, NUM_LEDS, color);
  // FastLED.show();
  Serial.println("END OF SETUP");
}

void loop()
{

  // Serial.println("CHECKING POSITION OF DIAL");
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
    Serial.print("occupancy: ");
    Serial.print(occupancy);
    Serial.println();
    Serial.println("UPDATING GUISLICE UI");
    update_all_GSlice_UI();
    // update_LEDs();
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
