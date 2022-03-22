#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include <external_library_includes.h>

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

void occupancy_request(String push_or_pull)
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

#endif