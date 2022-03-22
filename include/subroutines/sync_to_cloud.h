#ifndef SYNC_TO_CLOUD_H
#define SYNC_TO_CLOUD_H

#include <external_library_includes.h>

//
// globals and attributes
//
#include <globals/globals.h> //this contains timers used in this script
#include <globals/attributes.h>
#include <globals/graphql_queries.h> // PUSH and PULL graphql queries that are sent to API
#include <shelter_secrets.h>         // API secret and shelter ID
#include <subroutines/connect_to_wifi.h>
#include <subroutines/http_request.h>

// push_to_cloud handles sending the signal's current
// state to the api.
// Because the ESP8266 is a single core device we need to
// be careful how often
// bool push_to_cloud(unsigned long now, unsigned long last, WiFiClientSecure client, int push_wait, bool enable_internet, int occupancy, int capacity)
// bool push_to_cloud()
// {
//   // if it's been longer than push_wait since last_change_time, push current dial state "occupancy"
//   // to the api
//   if (now - last_change_time >= push_wait && change_to_push)
//   {
//     gslc_SetPageCur(&m_gui, E_PG_CLOUDSYNC);
//     gslc_Update(&m_gui);
//     // doing the actual push to the database can be disabled in attributes by setting
//     // enable_internet to false
//     if (enable_internet == true)
//     {
//       // Serial.println("pushing to " + (String)_API_HOST + "!");
//       occupancy_request(client, "push", occupancy, capacity);
//     }
//     else
//     {
//       delay(1500); // use a delay to simulate the time spent waiting for HTTP request to resolve
//     }
//     change_to_push = false;
//     last_change_time = now; // reset last counter so that pull sync happens at a minimum 30 seconds from now.
//     gslc_SetPageCur(&m_gui, E_PG_MAIN);
//     gslc_Update(&m_gui);
//   }
// }

// void pull_from_cloud(unsigned long now, unsigned long last, WiFiClientSecure client, int pull_wait, bool enable_internet, int occupancy, int capacity)
// {
//   if (now - last >= 70000 && !(change_to_push))
//   {
//     if (enable_internet == true)
//     {
//       gslc_SetPageCur(&m_gui, E_PG_CLOUDSYNC);
//       gslc_Update(&m_gui);
//       Serial.println("pulling from " + (String)_API_HOST + "!");
//       occupancy_request(client, "pull", occupancy, capacity);
//       change_to_push = false;
//       last = now; // reset last counter so that pull sync happens at a minimum 30 seconds from now.
//       gslc_SetPageCur(&m_gui, E_PG_MAIN);
//       gslc_Update(&m_gui);
//     }
//   }
// }
/*
Periodically the signal will push it's latest data to the api, or it will pull down the
API's latest data (to ensure the data stored in the cloud is the source of truth)
When a signal pushes or pulls it calls an HTTP library that takes up the microcontroller's
single CPU thread. This means the signal will stop listening for changes on the dial. From the user's point of view the signal has "frozen".

To keep this "freezing" to a minumum, we run timers
Push and Pull have different "wait" lengths. Timers get reset any time the dial is moved
or a sync_to_cloud happens.
*/
void perform_sync(String sync_direction)
{
  gslc_SetPageCur(&m_gui, E_PG_CLOUDSYNC);
  gslc_Update(&m_gui);
  // doing the actual push to the database can be disabled in attributes by setting
  // enable_internet to false
  if (enable_internet == true)
  {
    // Serial.println("pushing to " + (String)_API_HOST + "!");
    occupancy_request(sync_direction);
  }
  else
  {
    delay(1500); // use a delay to simulate the time spent waiting for HTTP request to resolve
  }
  change_to_push = false;
  // reset last_change_time counter so the next cloud sync is at
  // least sync_wait seconds away
  last_change_time = now;

  // finally return to main guislice page
  gslc_SetPageCur(&m_gui, E_PG_MAIN);
  gslc_Update(&m_gui);
  // TODO: if cloud sync returns an error, throw an error message
  // onto the screen before returning to main page
  // maybe ask the user to send for support from chalmers project
}
void sync_to_cloud(String sync_direction)
{
  // depending on if pushing or pulling determine how long sync_wait should be
  // values of push_wait & pull_wait are set in include/globals/attributes.h
  int sync_wait = (sync_direction == "push") ? push_wait : pull_wait;
  // sync signal state to the API if it's been longer than sync_wait since last_change_time
  if (now - last_change_time >= sync_wait)
  {
    // if performing a push, make sure change_to_push is true;
    if ((sync_direction == "push") && (change_to_push == true))
    {
      perform_sync(sync_direction);
      update_all_GSlice_UI();
    } // if performing a pull, make sure change_to_push is false;
    else if ((sync_direction == "pull") && (change_to_push == false))
    {
      Serial.println("making a pull from api!");
      perform_sync(sync_direction);
      Serial.println("  OCCUPANCY: " + (String)occupancy);
      Serial.println("  CAPACITY : " + (String)capacity);
      update_all_GSlice_UI();
    }
  }
}

/*
      gslc_SetPageCur(&m_gui, E_PG_CLOUDSYNC);
      gslc_Update(&m_gui);
      Serial.println("pulling from " + (String)_API_HOST + "!");
      occupancy_request(client, "pull", occupancy, capacity);
      change_to_push = false;
      last = now; // reset last counter so that pull sync happens at a minimum 30 seconds from now.
      gslc_SetPageCur(&m_gui, E_PG_MAIN);
      gslc_Update(&m_gui);
*/
#endif