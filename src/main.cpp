#include <Arduino.h>

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
  
  connect_TFT();
  show_chalmers_start();
  
  connect_Wifi();
  show_wifi_connected();
  delay(500);

  connect_Firebase();
  show_chalmers_start();

  //instatiate the locally stored json object
  //with properties defined above
  //in firebase_json.h
  // set_local_json();

  //if shelter doesn't exist in online database yet,
  //push shelter info to database
  // if(!(Firebase.getJSON(firebaseData, path)))
  // {
    // Firebase.setJSON(firebaseData, path, json);
  // }
  //else, if it does exist get the last shelter
  //data pushed to the online database and write
  //it to the locally stored json
  // else{
    // write_remote_json_to_local();
  // }
  // tft_test();
  // write_remote_json_to_local();
  
  // show_lights_status();
}

void loop() {
  // put your main code here, to run repeatedly:

}
