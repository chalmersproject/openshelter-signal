//when encoder clk triggers
  // counter + or -
  // if counter % 2 == 0          //the rotary encoder counts twice per "bump"
    //update occupancy(counter/2) //so I just count 2 jumps as 1
    //update tft(occupancy)
    //update led(occupancy)

//in main loop
  //if occupancy is different from last_occupancy
    // change_to_push=true
    // firebase_upload_countdown_start=now
    // if (now - firebase_upload_countdown_start > 4000 && change_to_push == true)
        // upload to firebase
        // firebase_upload_countdown_start=now
        // change_to_push = false

//////////////////////////////////////////////////////////
//                     Includes                         //
//////////////////////////////////////////////////////////
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
#include "Shelters/housing_first_strachan_house.h"
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

//Rotary Encoder Global Variables
volatile int stateCLK;
volatile int encoder_rotation_counter = 0; //the rotary encoder counts two rotations per "bump" so I just count 2 rotations as 1. This variable tracks the individual rotations so a full bump-to-bump event only counts as 1 when added to firecode_occupancy
#define inputCLK  4
#define inputDT 5

//Utilities
#include "connect.h"
#include "firebase_json.h"
#include "tft_test.h"
#include "check_status.h"
#include "show_status.h"

//////////////////////////////////////////////////////////
//             Script Starts Here                       //
//////////////////////////////////////////////////////////
bool change_to_push = false;
void ICACHE_RAM_ATTR encoder_change_trigger()
{
  change_to_push = true;
  firecode_occupancy+=read_dial_change();
  // update_tft_occupancy(firecode_occupancy, firecode_capacity);
  // update_led_occupancy(firecode_occupancy, firecode_capacity);
  Serial.println("=========================================");
  Serial.print("shelter occupancy:"); Serial.println(firecode_occupancy);
}

void setup()
{
  connect_Serial();
  Serial.println("======================");
  Serial.println("======================");
  Serial.println("Start Chalmers Signal!");
  Serial.println("======================");
  Serial.println("======================");

  pinMode(inputCLK, INPUT);
  pinMode (inputDT,INPUT);
  Serial.println("attaching interrupt!");
  attachInterrupt(digitalPinToInterrupt(inputCLK), encoder_change_trigger, CHANGE);

  connect_Wifi();
  delay(1000);

  connect_TFT();
  Serial.println("conencted TFT");
  delay(1000);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.println("connected LEDs");
  delay(1000);

  connect_Firebase();
}
void loop(){}
