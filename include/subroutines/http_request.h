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
#define REQBUFF_SIZE 1024
#define VARBUFF_SIZE 1024
#define RESPBUFF_SIZE 2048

const char *_API_HOST = "https://openshelter.fly.dev/graphql";

void occupancy_request(String push_or_pull)
{
    // ESP8266 HTTP library object instatiation.
    // this object handles all http requests
    HTTPClient http;
    //
    // memory allocation for storing json objects
    // to be sent to the chalmers signal api
    DynamicJsonDocument reqJson(REQBUFF_SIZE);
    DynamicJsonDocument varJson(RESPBUFF_SIZE);
    DynamicJsonDocument resJson(RESPBUFF_SIZE);

    varJson["signalId"] = SIGNAL_ID;
    varJson["secretKey"] = SIGNAL_SECRET;
    varJson["measurement"] = occupancy;

    Serial.println("Sending HTTP POST");
    http.begin(client, _API_HOST);
    http.addHeader("Content-Type", "application/json");

    varJson["signalId"] = SIGNAL_ID;

    if (push_or_pull == "update_params")
    {
        reqJson["query"] = UPDATE_PARAMETERS;
    }
    else
    {
        reqJson["query"] = (push_or_pull == "push") ? PUSH : PULL;
        //
        // this is where the graphql query gets set
        // to one of the string literals defined above
        // named *PUSH and *PULL
        //
        reqJson["operationName"] = (push_or_pull == "push") ? "CreateSignalMeasurement" : "CheckSignalMeasurement";
    }

    Serial.println("reqJson: " + (String)reqJson["query"]);

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
    Serial.print("RESPONSE STATUS: ");
    Serial.println(responseStatus);
    Serial.print("RESPONSE: ");
    Serial.println(http.getString());

    //
    // if we're *pulling data from* chalmers signal api
    // we need this next block of code
    // it handles recieving the json message from the api
    // and pulling the occupancy and capacity values out of it
    if (push_or_pull == "pull")
    {
        Serial.println(http.getString());
        DeserializationError error = deserializeJson(resJson, http.getString());
        // Test if parsing succeeds.
        if (error)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
        }
        occupancy = resJson["data"]["shelterSignalMeasurementLast"]["value"].as<int>();

        signal_type = resJson["data"]["shelterSignalMeasurementLast"]["type"].as<String>();

        signal_class = (signal_type == "headcount") ? "HEADS" : "BEDS";
        Serial.println(" Response occupancy: " + (String)occupancy);
        Serial.println(" Response capacity: " + (String)capacity);
    }
    if (push_or_pull == "update_params")
    {
        Serial.println(http.getString());
        DeserializationError error = deserializeJson(resJson, http.getString());
        // shelter_name = resJson["data"]["shelterFromSignalId"]["name"].as<String>();
        capacity_headcount = resJson["data"]["shelterFromSignalId"]["maxHeadcount"].as<int>();
        capacity_bedcount = resJson["data"]["shelterFromSignalId"]["maxBedcount"].as<int>();

        if (signal_class == "HEADS")
        {
            capacity = capacity_headcount;
        }
        else if (signal_class == "BEDS")
        {
            capacity = capacity_bedcount;
        }

        //
        // print all signal properties we're going to update guislice with
        //
        Serial.println("Signal Type: " + signal_class);
        Serial.println("Occupancy: " + (String)occupancy);
        Serial.println("Capacity: " + (String)capacity);
        Serial.println("Capacity Headcount: " + (String)capacity_headcount);
        Serial.println("Capacity Bedcount: " + (String)capacity_bedcount);
        Serial.println("Capacity Bedcount: " + (String)resJson["data"]["shelterFromSignalId"]["maxBedcount"]);
        update_all_GSlice_UI();
    }

    // Memory leaks begone :)
    http.end();
}

#endif