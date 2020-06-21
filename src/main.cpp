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

//////////////////////////////////////////////////////////
//             Globals and Utilities                    //
//////////////////////////////////////////////////////////

// Which shelter this chalmers signal is for. Defines occupancy, capacity, etc.
#include "Shelters/housing_first_strachan_house.h"

//Rotary Encoder Global Variables
#define inputCLK 4
#define inputDT 5
RotaryEncoder encoder(5, 4);

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
int last_occupancy; //used to detect when occupancy has grown by one digit ( e.g. 9 -> 10 ) and occupancy has to be wiped from the LCD

// LED Globals
int hue = 0;
uint32 led_last;
#define NUM_LEDS 8
#define DATA_PIN 15
CRGB leds[NUM_LEDS];
int led_brightness = 64;

//Wifi Globals
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!! THIS FILE IS .gitignore'd !!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// it includes API keys SSIDs, and passwords
// You need to fill it in with your own credentials
// before this program will work.
#include "credentials.h"

//Firebase Globals
FirebaseData firebaseData;
FirebaseJson json;
FirebaseJsonObject jsonParseResult;
#include "firebase_json.h" // for pushing new shelter entry if firebase doesn't have this shelter in it already

//////////////////////////////////////////////////////////
//             Script Starts Here                       //
//////////////////////////////////////////////////////////

// flag to mark when the dial has been moved. Calls the LEDs, LCD, and push_to_firebase functions
bool change_to_push = false;

void ICACHE_RAM_ATTR encoder_change_trigger() {
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

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(led_brightness);

  tft.begin();
  tft.setCursor(35, 10);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(5);
  tft.println(occupancy);
  tft.setCursor(8, 42);
  tft.println("----");
  tft.setCursor(20, 75);
  tft.println(capacity);

  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Serial.print("Connecting to Wi-Fi");
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //     Serial.print(".");
  //     delay(300);
  // }
  // Serial.println(); Serial.print("Connected with IP: ");
  // Serial.println(WiFi.localIP()); Serial.println();
  //
  // Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // Firebase.reconnectWiFi(true);
  // Serial.println("Firebase Connnected");
}

unsigned long now,last;
void loop(){
  static int pos = 0;

  int newPos = encoder.getPosition();
  if (pos != newPos)
  {
    Serial.print("Pos: "); Serial.print(newPos);
    Serial.println();
    if (pos > newPos)
    {
      occupancy--;
    } else if ( newPos > pos)
    {
      occupancy++;
    }
    Serial.print("Occupancy: "); Serial.print(occupancy);
    Serial.println();
    pos = newPos;

    //set barriers on occupancy
    if ( 0 >= occupancy )
    {
      occupancy = 0;
    } else if ( occupancy >= capacity )
    {
      occupancy = capacity;
    }
    tft.setCursor(35, 10);
    // used to detect when occupancy has grown by one digit ( e.g. 10 -> 9 ) and occupancy has to be wiped from the LCD
    if ( occupancy == 9 && last_occupancy == 10 || occupancy == 99 && last_occupancy == 100 )
    {
      tft.fillRect( 0, 10 , tft.width() , 40 , BLACK );
      last_occupancy = occupancy;
    }
    tft.println(occupancy);
    // update LEDs
    hue = map(occupancy, 0, capacity, 171, 0);
    CHSV color = CHSV(hue, 255, 255);
    fill_solid(leds,NUM_LEDS, color);
    FastLED.show();

    change_to_push=true;
    last = now;
    last_occupancy = occupancy;
  }

  // wait at least 3 seconds since last change before pushing to firebase
  // if firebase gets updated too often it will cost a lot of money
  now=millis();
  if (now - last >= 3000 && change_to_push)
  {
    // if(Firebase.setInt(firebaseData, path_firecode_occupancy, occupancy))
    // {
    //   Serial.println("Updating Firebase!!");
    // }
    // else
    // {
    //   Serial.println("REASON: " + firebaseData.errorReason());
    //   delay(1000);
    // }
    change_to_push=false;
  }
}
