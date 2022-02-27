#include <Arduino.h>

// GuiSlice Libraries
// #include "GUIsliceProjects/GUIsliceProjects_GSLC.h"
// #include "guislice_init.h"
// #include "guislice_callbacks.h"

// Globals from main.cpp
// extern bool change_to_push;
// extern unsigned long now, last, encoder_button_timer;
// bool change_to_push;
// unsigned long now, last, encoder_button_timer;
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
// API secret and shelter ID
//
#include <shelter_secrets.h>

#define REQBUFF_SIZE 256
#define VARBUFF_SIZE 256
#define RESPBUFF_SIZE 2048

const char *_API_HOST = "https://api.cloud.chalmersproject.com/graphql";

// Attempting to do a multi-line variable declaration: HOWTO?
const char *PUSH = "               \
mutation CreateSignalMeasurement(  \
  $signalId: ID!                   \
  $signalSecret: String!           \
  $measurement: Int!               \
) {                                \
  createSignalMeasurement(         \
    input: {                       \
      signalId: $signalId          \
      signalSecret: $signalSecret  \
      measurement: $measurement    \
    }                              \
  ) {                              \
    measurement {                  \
      id                           \
    }                              \
  }                                \
}";

const char *PULL = "               \
query CheckSignalMeasurement(      \
  $signalId: ID!                   \
) {                                \
    signal(id: $signalId)  {       \
      measurements (limit:1){      \
        occupancy                  \
        {                          \
          spots                    \
          beds                     \
        }                          \
        capacity                   \
        {                          \
          spots                    \
          beds                     \
        }                          \
      }                            \
    }                              \
}";

// HTTP POST to chalmersproject API
void occupancy_request(WiFiClientSecure client, String push_or_pull, int occupancy, int capacity)
{
  HTTPClient http;
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
  reqJson["operationName"] = (push_or_pull == "push") ? "CreateSignalMeasurement" : "CheckSignalMeasurement";
  reqJson["variables"] = varJson;

  String request;
  serializeJson(reqJson, request);
  // Serial.print("REQUEST: ");
  // Serial.println(request);

  int responseStatus = http.POST(request);
  // Serial.print("RESPONSE STATUS: ");
  // Serial.println(responseStatus);
  // Serial.print("RESPONSE: ");
  // Serial.println(http.getString());

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