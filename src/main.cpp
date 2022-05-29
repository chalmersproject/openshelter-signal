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
    sync_to_cloud("pull");
  }
  init_LEDs();
  gslc_SetPageCur(&m_gui, E_PG_MAIN);
  update_all_GSlice_UI();

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
    update_LEDs();

    Serial.println("UPDATING TIMERS last_change_time and last_occupancy");
    last_change_time = now;
    last_occupancy = occupancy;
    change_to_push = true;
  }

  //
  // wait at least 3 seconds since last change before pushing to api.chalmers.project
  //
  now = millis();
  sync_to_cloud("push");
  sync_to_cloud("pull");
  // support_button_clicked();

  // call handle support button and handle return code.
  // used to send a "need help!" message to telegram support chat
  // 0 == function ran correctly
  // 1 == unable to send telegram support message
  // 2 == rotary encoder is misbehaving
  // if ( handle_support_button() == 1)
  // {
  //   Serial.println("Something went wrong in handle_support_button()");
  // }
  // Serial.println("Function handle support button has exited");

  handle_support_button_timer();
}
