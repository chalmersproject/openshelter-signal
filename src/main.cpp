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
#include <RotaryEncoder.h>

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


//Rotary Encoder Global Variables
#define inputCLK 4
#define inputDT 5

//TFT Globals
#define __DC 0
#define __CS 2
// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
//instatiate TFT!
TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);

RotaryEncoder encoder(5, 4);

// volatile int stateCLK;
// volatile int encoder_rotation_counter = 0; //the rotary encoder counts two rotations per "bump" so I just count 2 rotations as 1. This variable tracks the individual rotations so a full bump-to-bump event only counts as 1 when added to firecode_occupancy
// #define inputCLK  4
// #define inputDT 5
// //Encoder Global
// RotaryEncoder encoder(4, 5);

//Utilities
// #include "connect.h"
// #include "firebase_json.h"
// #include "tft_test.h"
// #include "check_status.h"
// #include "show_status.h"

//////////////////////////////////////////////////////////
//             Script Starts Here                       //
//////////////////////////////////////////////////////////
// flag to mark when the dial has been moved. Calls the LEDs, LCD, and push_to_firebase functions
bool change_to_push = false;

void ICACHE_RAM_ATTR encoder_change_trigger() {
  Serial.println("interrupt triggered!");
  encoder.tick();
}
void setup()
{
  Serial.begin(115200);
  Serial.println("======================");
  Serial.println("======================");
  Serial.println("Start Chalmers Signal!");
  Serial.println("======================");
  Serial.println("======================");

  attachInterrupt(digitalPinToInterrupt(4), encoder_change_trigger, CHANGE);
  attachInterrupt(digitalPinToInterrupt(5), encoder_change_trigger, CHANGE);

  tft.begin();
  tft.setCursor(35, 10);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(occupancy);
  tft.setCursor(8, 42);
  tft.println("----");
  tft.setCursor(20, 75);
  tft.println(capacity);
  // connect_Wifi();
  // delay(1000);
  //
  // connect_TFT();
  // Serial.println("conencted TFT");
  // delay(1000);
  //
  // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // Serial.println("connected LEDs");
  // delay(1000);

  // connect_Firebase();
}

void loop(){
  static int pos = 0;

  int newPos = encoder.getPosition();
  if (pos != newPos)
  {
    Serial.print(newPos);
    Serial.println();
    pos = newPos;
    occupancy = newPos;
    tft.setCursor(35, 10);
    tft.println(occupancy);
  }
}
