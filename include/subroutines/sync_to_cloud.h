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
bool push_to_cloud()
{
  // if it's been longer than push_wait since last_change_time, push current dial state "occupancy"
  // to the api
  if (now - last_change_time >= push_wait && change_to_push)
  {
    gslc_SetPageCur(&m_gui, E_PG_CLOUDSYNC);
    gslc_Update(&m_gui);
    // doing the actual push to the database can be disabled in attributes by setting
    // enable_internet to false
    if (enable_internet == true)
    {
      // Serial.println("pushing to " + (String)_API_HOST + "!");
      occupancy_request(client, "push", occupancy, capacity);
    }
    else
    {
      delay(1500); // use a delay to simulate the time spent waiting for HTTP request to resolve
    }
    change_to_push = false;
    last_change_time = now; // reset last counter so that pull sync happens at a minimum 30 seconds from now.
    gslc_SetPageCur(&m_gui, E_PG_MAIN);
    gslc_Update(&m_gui);
  }
}

void pull_from_cloud(unsigned long now, unsigned long last, WiFiClientSecure client, int pull_wait, bool enable_internet, int occupancy, int capacity)
{
  if (now - last >= 70000 && !(change_to_push))
  {
    if (enable_internet == true)
    {
      gslc_SetPageCur(&m_gui, E_PG_CLOUDSYNC);
      gslc_Update(&m_gui);
      Serial.println("pulling from " + (String)_API_HOST + "!");
      occupancy_request(client, "pull", occupancy, capacity);
      change_to_push = false;
      last = now; // reset last counter so that pull sync happens at a minimum 30 seconds from now.
      gslc_SetPageCur(&m_gui, E_PG_MAIN);
      gslc_Update(&m_gui);
    }
  }
}

bool sync_to_cloud(String push_or_pull)
{
  // if it's been longer than push_wait since last_change_time, push current dial state "occupancy"
  // to the api
  if (now - last_change_time >= push_wait && change_to_push)
  {
    gslc_SetPageCur(&m_gui, E_PG_CLOUDSYNC);
    gslc_Update(&m_gui);
    // doing the actual push to the database can be disabled in attributes by setting
    // enable_internet to false
    if (enable_internet == true)
    {
      // Serial.println("pushing to " + (String)_API_HOST + "!");
      occupancy_request(client, "push", occupancy, capacity);
    }
    else
    {
      delay(1500); // use a delay to simulate the time spent waiting for HTTP request to resolve
    }
    change_to_push = false;
    last_change_time = now; // reset last counter so that pull sync happens at a minimum 30 seconds from now.
    gslc_SetPageCur(&m_gui, E_PG_MAIN);
    gslc_Update(&m_gui);
  }
}
#endif