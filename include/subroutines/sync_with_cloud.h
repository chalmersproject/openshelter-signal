#include <Arduino.h>

// GuiSlice Libraries
#include "GUIsliceProjects/GUIsliceProjects_GSLC.h"
#include "guislice_init.h"
#include "guislice_callbacks.h"

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

// #define SYNCPRINT_SIZE 256
#define REQBUFF_SIZE 256
#define VARBUFF_SIZE 256
#define RESPBUFF_SIZE 2048

// const char *_API_HOST = "http://192.168.133.61:8080/graphql";
const char *_API_HOST = "https://api.cloud.chalmersproject.com/graphql";
// const char *_API_HOST = "https://1d2b-2607-f2c0-928a-b500-64cc-e3d2-f2ad-16c7.ngrok.io/graphql";
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
    // GraphqlQuery *graphql = (GraphqlQuery *)malloc(sizeof(GraphqlQuery));
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
    Serial.print("REQUEST: ");
    Serial.println(request);

    int responseStatus = http.POST(request);
    Serial.print("RESPONSE STATUS: ");
    Serial.println(responseStatus);
    Serial.print("RESPONSE: ");
    Serial.println(http.getString());

    if (push_or_pull == "pull")
    {
        // TODO: change http.getString to http.getStream --  https://arduinojson.org/v6/how-to/use-arduinojson-with-httpclient/
        // according to arduino json docs using getString is inefficient as it copies the entire response into memory before copying it to the json variable
        // but I can't get getStream() to work. DeserializeJson complains getStream() returns empty.
        DeserializationError error = deserializeJson(resJson, http.getString());
        // Test if parsing succeeds.
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            // return;
        }
        occupancy = resJson["data"]["signal"]["measurements"][0]["occupancy"]["spots"].as<int>();
        capacity = resJson["data"]["signal"]["measurements"][0]["capacity"]["spots"].as<int>();
        // deserializeJson(resJson, http.getStream());
        // Serial.println(" Response resJson: " + (String)resJson);
        Serial.println(" Response occupancy: " + (String)occupancy);
        Serial.println(" Response capacity: " + (String)capacity);
    }

    // Memory leaks begone :)
    http.end();
    // Serial.print("Response: ");
    // Serial.println( resJson.getElement );
}
void pull_from_cloud(unsigned long now, unsigned long last, WiFiClientSecure client, int pull_wait, bool enable_internet, bool change_to_push, int occupancy, int capacity)
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