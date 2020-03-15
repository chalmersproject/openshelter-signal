#include <Arduino.h>

//display
#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>

//internet
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

//LED
#include <FastLED.h>

// !!!!!!!!!!! THIS FILE IS .gitignore'd !!!!!!!!!!!
// it includes API keys SSIDs, and passwords
// You need to fill it in with your own credentials
// before this program will work.
#include "credentials.h"
#include "Shelters/st_felix.h"


//////////////////////////////////////////////////////////
//             Globals and Utilities                    //
//////////////////////////////////////////////////////////

//Global Variables
int dial_pin_value;
int dial_return_value;
int last_firecode_occupancy = firecode_occupancy;
int last_last_firecode_occupancy = firecode_occupancy;
bool there_is_a_change_to_push = false;
bool there_is_tft_a_change_to_push = false;
uint32_t now;
uint32_t last;
uint32_t last_pull;
uint32_t last_dial_change;

//LED Global Variables
#define NUM_LEDS 8
#define DATA_PIN 5
CRGB leds[NUM_LEDS];
int led_brightness = 64;

//Utilities
#include "connect.h"
#include "firebase_json.h"
#include "tft_test.h"
#include "check_status.h"
#include "show_status.h"

//////////////////////////////////////////////////////////
//                       Setup                          //
//////////////////////////////////////////////////////////

void setup() {
  connect_Serial();
  Serial.println("Start Chalmers Signal!");
  pinMode(dial_pin, INPUT);

  connect_Wifi();
  delay(1000);

  connect_TFT();
  Serial.println("conencted TFT");
  delay(1000);


  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.println("connected LEDs");
  delay(1000);

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

  update_tft_occupancy(firecode_occupancy, firecode_capacity);
}

//////////////////////////////////////////////////////////
//                       Loop                           //
//////////////////////////////////////////////////////////

void loop() {
  now = millis();
  last_firecode_occupancy = firecode_occupancy;
  dial_return_value = check_dial_change();
  firecode_occupancy += dial_return_value;

  //if firecode occupancy has changed
  if (firecode_occupancy != last_firecode_occupancy)
  {
    // if occupancy has just become larger than capacity or less than zero
    // then hold it at it's current value instead of increasing it.
    if (firecode_occupancy > firecode_capacity || 0 > firecode_occupancy)
    {
      firecode_occupancy = last_firecode_occupancy;
    }
    else
    {
      // update display, then delay pushing to firebase by 600 milliseconds
      // by resetting last to now
      // set the "change to push" boolean to true
      Serial.print("Firecode_Occupancy: ");
      Serial.println(firecode_occupancy);
      last = now;
      last_firecode_occupancy = firecode_occupancy;
      last_last_firecode_occupancy = last_firecode_occupancy;
      there_is_a_change_to_push = true;
      there_is_tft_a_change_to_push = true;
      last_dial_change = now;
    }
  }
  update_led_occupancy(firecode_occupancy, firecode_capacity);
  // because updating the display introduces a delay that can be longer than the
  // amount of time between dial position changes during a quick turning of the dial
  // the tft display will only be updated if it's been 240 milliseconds since the last
  // time the dial has been moved
  if(now - last_dial_change >= 240 && there_is_tft_a_change_to_push == true)
  {
    update_tft_occupancy(firecode_occupancy, firecode_capacity);
    last_dial_change = now;
    there_is_tft_a_change_to_push = false;
  }

  //only push to firebase if there is a change to push and it has been
  //at least 600 milliseconds since the last change
  //so to avoid pushing a million times when the dial is turned
  //a whole bunch of times during an update by the user
  if ( (now - last >= 1000) && there_is_a_change_to_push ){

    if(Firebase.setInt(firebaseData, path_firecode_occupancy, firecode_occupancy))
    {
      Serial.println("Updating Firebase!!");
      Serial.println("Updating Firebase!!");
      Serial.println("Updating Firebase!!");
    }
    else
    {
      Serial.println("REASON: " + firebaseData.errorReason());
      delay(1000);
    }
    there_is_a_change_to_push = false;
    last = now;
    last_pull = now;
  }

  // if there hasn't been a change pushed in the last 2 seconds
  // pull the latest from firebase
  /*
  if ( now - last_pull >= 2000 )
  {
    Serial.println("Pulling from Firebase!!");
    Serial.println("Pulling from Firebase!!");
    Serial.println("Pulling from Firebase!!");
    Firebase.getInt(firebaseData, path + "/Service_Status/Firecode_Space/Firecode_Occupancy", firecode_occupancy);
  }
  */
}
