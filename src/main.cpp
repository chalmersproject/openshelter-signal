#define _GLIBCXX_USE_C99 1
#include <Arduino.h>
// #include <iostream>
// #include <string>

//display
#include <SPI.h>
// #include <Adafruit_ILI9341.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>

//internet
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

// !!!!!!!!!!! THIS FILE IS .gitignore'd !!!!!!!!!!!
// it includes API keys SSIDs, and passwords
// You need to fill it in with your own credentials
// before this program will work.
#include "credentials.h"

//////////////////////////////////////////////////////////
//                Shelter Properties                    //
//////////////////////////////////////////////////////////

//json objects
FirebaseData firebaseData;
FirebaseJson json;
FirebaseJsonObject jsonParseResult;

String jsonData = "";
FirebaseJson testJson;

String path = "/Shelters/st_felix_augusta";
//available space
int firecode_capacity = 100;
int bed_capacity      = 43;
//------------------------//
int firecode_occupancy = 42;
int bed_occupancy = 42;

//meal_status (meal, no_meal, snacks)
String meal_status = "meal";

//Client Properties
bool adult_only = false;
bool youth_only = false;
bool family_only = false;
bool male_only = false;
bool female_only = false;
bool lgbtq_only = false;
bool all_allowed = true;

//Utilities
#include "connect.h"
#include "firebase_json.h"
#include "tft_test.h"
#include "check_status.h"
#include "show_status.h"

void setup() {
  connect_Serial();
  Serial.println("Start Chalmers Signal!");
  pinMode(dial_pin, INPUT);

  connect_Wifi();
  delay(500);

  connect_Firebase();

  //if shelter info does not already exist in firebase
  //create a json object at shelter path and push to firebase
  if( !Firebase.getJSON(firebaseData, path) )
  {
    Serial.println("Shelter data does not exist in firebase!");
    Serial.println("Creating Shelter data and pushing to firebase!");
    set_local_json();
    write_local_to_remote();
  }
  //else if shelter data is already in firebase
  //pull the last shelter occupancy pushed to firebase
  else
  {
    Serial.print("Pulling last known occupancy for " + path + " : ");
    Firebase.getInt(firebaseData, path + "/Service_Status/Firecode_Space/Firecode_Occupancy", firecode_occupancy);
    Serial.println(firecode_occupancy);
  }
}

int dial_pin_value;
void loop() {
  dial_pin_value = analogRead(dial_pin);
  delay(300);
  Serial.println("Dial pin analog read : " + dial_pin_value);
  /*
  // put your main code here, to run repeatedly:
  if(check_dial_change() == 1)
  {
    firecode_occupancy++;
    update_tft_occupancy(firecode_occupancy);
  }
  else if(check_dial_change() == -1)
  {
    firecode_occupancy--;
    update_tft_occupancy(firecode_occupancy);
  }
  */
}
