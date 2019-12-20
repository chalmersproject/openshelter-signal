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

  /*
  connect_TFT();

  //Internet stuff
  show_chalmers_start();

  connect_Wifi();
  show_wifi_connected();
  delay(500);
  */
  connect_Wifi();
  delay(500);

  set_local_json();
  json.parse().get("Service_Status").get("Firecode_Space").get("Firecode_Occupancy");
  firecode_occupancy = json.parseResult().intValue;

  Serial.println("===================");
  Serial.println("Initialized Json Value");
  Serial.println("===================");
  Serial.print("Firecode Occupancy: ");
  Serial.println(firecode_occupancy);

  Serial.println("===================");
  Serial.println("Connectecting to Firebase and pulling remote json");
  Serial.println("===================");
  connect_Firebase();
  pull_remote_json();
  write_remote_json_to_local();

  //write local json to local variable
  json.parse().get("Service_Status").get("Firecode_Space").get("Firecode_Occupancy");

  Serial.println("===================");
  Serial.println("Pulled JSON Value written to local variable");
  Serial.println("===================");
  Serial.print("Firecode Occupancy: ");
  Serial.println(firecode_occupancy);

  /*
  connect_Firebase();
  pull_remote_json();
  write_remote_json_to_local();
  show_chalmers_start();

  //instatiate the locally stored json object
  //with properties defined above
  //in firebase_json.h
  set_local_json();

  //if shelter info already exists in firebase, pull the data
  //and write it to local firebase json object
  if((Firebase.getJSON(firebaseData, path)))
  {
    // Firebase.setJSON(firebaseData, path, json);
    Serial.println("Writing remote json to local json");
    pull_remote_json();
    write_remote_json_to_local();
  }
  //else, if data isn't in firebase yet
  //instatiate the local json object and write it out
  //to firebase
  else{
    //
    set_local_json();
  }

  tft_test();
  write_remote_json_to_local();
  show_lights_status();
  */
}

void loop() {
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
