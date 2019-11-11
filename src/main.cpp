#include <Arduino.h>

//display
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>

//internet
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>


//
// !!!!!!!!!!! THIS FILE IS .gitignore'd !!!!!!!!!!!
// it includes API keys SSIDs, and passwords
#include "credentials.h"

//Define Firebase Data object
FirebaseData firebaseData;

//functions
#include "connect.h"


//available space
int firecode_capacity = 100;
int bed_capacity      = 43;
//------------------------//
int firecode_occupancy = 42;
int bed_occupancy = 42;

//meal_status (meal, no_meal, snacks)
String meal_status = "meal";

//Shelter Properties
bool adult_only = false;
bool youth_only = false;
bool family_only = false;
bool male_only = false;
bool female_only = false;
bool lgbtq_only = false;
bool all_allowed = true;

#include "json_test.h"
#include "tft_test.h"


void setup() {
  connect_Serial();
  connect_Wifi();
  connect_Firebase();

  json_test();
  tft_test();
}

void loop() {
  // put your main code here, to run repeatedly:
}
