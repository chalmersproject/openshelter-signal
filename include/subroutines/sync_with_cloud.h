#ifndef SYNC_WITH_CLOUD_H
#define SYNC_WITH_CLOUD_H
#include <Arduino.h>

//
// JSON Support
//
#include <ArduinoJson.h>

// WiFi and HTTPS requests
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> // create TLS connection
#include <WiFiManager.h>

//
// globals and attributes
//
#include <globals/globals.h> //this contains timers used in this script
#include <globals/attributes.h>
#include <globals/graphql_queries.h> // PUSH and PULL graphql queries that are sent to API
#include <shelter_secrets.h>         // API secret and shelter ID

//
// memory allocation for json objects to store graphql api queries
//
#define REQBUFF_SIZE 256
#define VARBUFF_SIZE 256
#define RESPBUFF_SIZE 2048

const char *_API_HOST = "https://api.cloud.chalmersproject.com/graphql";

void occupancy_request(WiFiClientSecure client, String push_or_pull, int occupancy, int capacity)
{
  // ESP8266 HTTP library object instatiation.
  // this object handles all http requests
  HTTPClient http;
  //
  // memory allocation for storing json objects
  // to be sent to the chalmers signal api
  DynamicJsonDocument reqJson(1024);
  DynamicJsonDocument varJson(1024);
  DynamicJsonDocument resJson(1024);

  varJson["signalId"] = SIGNAL_ID;
  varJson["signalSecret"] = SIGNAL_SECRET;
  varJson["measurement"] = occupancy;

  Serial.println("Sending HTTP POST");
  http.begin(client, _API_HOST);
  http.addHeader("Content-Type", "application/json");

  varJson["signalId"] = SIGNAL_ID;
  reqJson["query"] = (push_or_pull == "push") ? PUSH : PULL;
  Serial.println("reqJson: " + (String)reqJson["query"]);

  //
  // this is where the graphql query gets set
  // to one of the string literals defined above
  // named *PUSH and *PULL
  //
  reqJson["operationName"] = (push_or_pull == "push") ? "CreateSignalMeasurement" : "CheckSignalMeasurement";
  //
  // varJson["variables"] contains:
  // shelter id, shelter secret, occupancy, capacity
  //
  reqJson["variables"] = varJson;

  String request;
  serializeJson(reqJson, request);

  // Serial.print("REQUEST: ");
  // Serial.println(request);

  int responseStatus = http.POST(request);

  // TODO: scope these to debug output
  // Serial.print("RESPONSE STATUS: ");
  // Serial.println(responseStatus);
  // Serial.print("RESPONSE: ");
  // Serial.println(http.getString());

  //
  // if we're *pulling data from* chalmers signal api
  // we need this next block of code
  // it handles recieving the json message from the api
  // and pulling the occupancy and capacity values out of it
  if (push_or_pull == "pull")
  {
    DeserializationError error = deserializeJson(resJson, http.getString());
    // Test if parsing succeeds.
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    }
    occupancy = resJson["data"]["signal"]["measurements"][0]["occupancy"]["spots"].as<int>();
    capacity = resJson["data"]["signal"]["measurements"][0]["capacity"]["spots"].as<int>();
    Serial.println(" Response occupancy: " + (String)occupancy);
    Serial.println(" Response capacity: " + (String)capacity);
  }

  // Memory leaks begone :)
  http.end();
}

// push_to_cloud handles sending the signal's current
// state to the api.
// Because the ESP8266 is a single core device we need to
// be careful how often
bool push_to_cloud(unsigned long now, unsigned long last, WiFiClientSecure client, int push_wait, bool enable_internet, int occupancy, int capacity)
{
  if (now - last >= push_wait && change_to_push)
  {
    if (enable_internet == true)
    {
      gslc_SetPageCur(&m_gui, E_PG_CLOUDSYNC);
      gslc_Update(&m_gui);
      // Serial.println("pushing to " + (String)_API_HOST + "!");
      occupancy_request(client, "push", occupancy, capacity);
      change_to_push = false;
      last = now; // reset last counter so that pull sync happens at a minimum 30 seconds from now.
      gslc_SetPageCur(&m_gui, E_PG_MAIN);
      gslc_Update(&m_gui);
    }
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
#endif