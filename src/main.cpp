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
#include "subroutines/led_init_and_update.h"
#include "subroutines/telegram_init_and_send.h"
#include "subroutines/support_button.h"

///////////////////////////////////////////////////////////////////////////////////////////
//                    Rotary Encoder Interrupt                                           //
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
//                    MAIN SCRIPT STARTS HERE                                            //
///////////////////////////////////////////////////////////////////////////////////////////

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
    perform_sync("pull");
    sync_to_cloud("update_params");
  }
  init_LEDs();
  gslc_SetPageCur(&m_gui, E_PG_MAIN);
  update_all_GSlice_UI();

  Serial.println("END OF SETUP");
}

void loop()
{
  now = millis();
  // Serial.println("CHECKING POSITION OF DIAL");
  int newPos = encoder.getPosition();
  if (pos != newPos)
  {
    // Serial.print("Pos: ");
    // Serial.print(newPos);
    // Serial.println();
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
    update_LEDs();

    Serial.println("UPDATING TIMERS last_change_time and last_occupancy");
    last_change_time = now;
    last_occupancy = occupancy;
    change_to_push = true;
  }
  //
  // wait at least 3 seconds since last change before pushing to api.chalmers.project
  //
  sync_to_cloud("push");
  sync_to_cloud("pull");

  //
  // these timers are causing the chalmers signal to crash
  // when the dial gets turned sometimes
  // I think there's some conflict in interrupts between
  // the rotary encoder interrupts and the
  // timer library interrupts

  // handle_support_button_timer();

  // yield();
}
