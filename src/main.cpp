//////////////////////////////////////////////////////////
//            CHALMERS SIGNAL OCCUPANCY                 //
//////////////////////////////////////////////////////////
/*
The Chalmers Signal Occuapncy Device is a client tally counter
for shelter reception staff.

Written and Maintained by the Chalmers project info@chalmersproject.com
F/OSS under M.I.T License
*/

///////////////////////////////////////////////////////////////////////////////////////////
//                     Includes                                                          //
///////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>

// display
#include <SPI.h>
#include <RotaryEncoder.h>

// WiFi and HTTPS requests
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> // create TLS connection
#include <WiFiManager.h>
// LED
#include <FastLED.h>

//
// JSON Support
//
#include <ArduinoJson.h>

//
// API secret and shelter ID
//
#include <shelter_secrets.h>

// GUISlice

#include "GUIsliceProjects/GUIsliceProjects_GSLC.h"
#include "guislice_init.h"
#include "guislice_callbacks.h"

// subroutines
#include "subroutines/support_button_clicked.h"
#include "subroutines/sync_with_cloud.h"

///////////////////////////////////////////////////////////////////////////////////////////
//                    Toggles                                                            //
///////////////////////////////////////////////////////////////////////////////////////////

// some chalmers signals have red-pcb 1.44" displays from creatron
// others use the cheaper blue-pcb 1.44" displays from aliexpress
static int display_color = 1; //(blue_pcb = 1; red_pcb = 2)

// for debugging it's useful to turn off the chalmers signal's internet-y abilities. That way we can do things like make changes with it's interface without waiting for it to connect to the internet
static bool enable_internet = true;

// earlier versions of chalmers signals don't have their button attached to the ESP. It's useful to be able to quickly turn off all features of the chalmers signal that use this button.
static bool has_button = true;

///////////////////////////////////////////////////////////////////////////////////////////
//                    Globals                                                            //
///////////////////////////////////////////////////////////////////////////////////////////

//
// Sync timer delays. These are the number of seconds the signal will wait
// (since the dial was last changed) before pushing/pulling to/from
// chalmers api
#define pull_wait 70000 // 70 seconds

//
// Measured occupancy value from the chalmers signal
//
int occupancy = 15;
int capacity = 90;
int last_occupancy;
//
// Rotary Encoder Global Variables
//
#define inputCLK 4 // pin
#define inputDT 5
RotaryEncoder encoder(5, 4);

//
// LED Globals
//
int hue = 0;
uint32 led_last;
#define NUM_LEDS 8
#define DATA_PIN 15
CRGB leds[NUM_LEDS];
int led_brightness = 32;

///////////////////////////////////////////////////////////////////////////////////////////
//                    FUNCTIONS                                                          //
///////////////////////////////////////////////////////////////////////////////////////////

WiFiClientSecure client;
void initWifi()
{
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  // WiFi.begin(_WIFI_SSID, _WIFI_PWD);

  // https://github.com/tzapu/WiFiManager/blob/master/examples/Basic/Basic.ino
  // WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  bool res;
  res = wm.autoConnect("Chalmers-Signal");
  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }
  // Serial.println("Connecting..");
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   Serial.println(".");
  // }
  // Serial.printf("SSID: %s\nIP: %s\n", _WIFI_SSID, WiFi.localIP().toString().c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////
//                    QUERY                                                              //
///////////////////////////////////////////////////////////////////////////////////////////

//
// REQUEST FORMAT:
//

/*
{
  query: "...the raw query text...",
  variables: {
    signalId: "...",
    signalSecret: "...",
    _MEASUREMENT: 10
  }
}

reqJson = {
  query: "...",
  variables: varJson
}
*/

// typedef struct graphqlQuery
// {
//   char req[REQBUFF_SIZE];
//   char var[VARBUFF_SIZE];
//   int status;
//   String resp;
// } GraphqlQuery;

///////////////////////////////////////////////////////////////////////////////////////////
//                    Rotary Encoder Interrupt                                           //
///////////////////////////////////////////////////////////////////////////////////////////
// flag to mark when the dial has been moved. Calls the LEDs, LCD, and push_to_firebase functions
bool change_to_push = false;
bool encoder_button_pressed = false;

void ICACHE_RAM_ATTR encoder_change_trigger()
{
  encoder.tick();
  Serial.println("interrupt triggered!");
}

void ICACHE_RAM_ATTR encoder_button_trigger()
{
  encoder_button_pressed = true;
  Serial.println("encoder button was pressed!");
}

///////////////////////////////////////////////////////////////////////////////////////////
//                    MAIN SCRIPT STARTS HERE                                            //
///////////////////////////////////////////////////////////////////////////////////////////

void update_all_GSlice_UI()
{
  char string_to_write[MAX_STR];
  snprintf(string_to_write, MAX_STR, "%u", occupancy);
  gslc_ElemSetTxtStr(&m_gui, m_pElemVal2, string_to_write);

  snprintf(string_to_write, MAX_STR, "%u", capacity);
  gslc_ElemSetTxtStr(&m_gui, m_pElemVal2_3, string_to_write);

  int gauge_pos = map(occupancy, 0, capacity, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, m_pElemXRingGauge1, gauge_pos);
  gslc_Update(&m_gui);
}

void update_LEDs()
{
  hue = map(occupancy, 0, capacity, 90, 0);
  CHSV color = CHSV(hue, 255, 255);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  change_to_push = true;
}

#define encoder_button_pin 0

void setup()
{
  pinMode(encoder_button_pin, INPUT_PULLUP);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(4), encoder_change_trigger, CHANGE);
  attachInterrupt(digitalPinToInterrupt(5), encoder_change_trigger, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(encoder_button_pin), encoder_button_trigger, ONLOW);

  // TODO
  // chalmers START screen
  //
  gslc_InitDebug(&DebugOut);
  if (enable_internet == true)
  {

    // ------------------------------------------------
    // Create graphic elements
    // ------------------------------------------------
    InitGUIslice_gen();
    gslc_SetPageCur(&m_gui, E_PG_WIFICON);
    gslc_Update(&m_gui);
    initWifi();
    client.setInsecure();

    if (WiFi.status() == WL_CONNECTED)
    {
      delay(4000);

      // pull latest occupancy capacity numbers from remote and set them to the display
      occupancy_request(client, "pull", occupancy, capacity); //
      // Update OCCUPANCY and CAPACITY GUI numbers
      gslc_SetPageCur(&m_gui, E_PG_MAIN);

      update_all_GSlice_UI();
    }

    // TODO:
    // verify connection to api.chalmersproject.com
    //
  }

  //
  // start LED with color of occupancy / capacity
  //
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(led_brightness);

  hue = map(occupancy, 0, capacity, 90, 0);
  CHSV color = CHSV(hue, 255, 255);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
}

unsigned long now, last, encoder_button_timer;

void loop()
{
  static int pos = 0;
  int newPos = encoder.getPosition();
  if (pos != newPos)
  {
    Serial.print("Pos: ");
    Serial.print(newPos);
    Serial.println();
    if (pos > newPos)
    {
      occupancy--;
    }
    else if (newPos > pos)
    {
      occupancy++;
    }
    Serial.print("occupancy: ");
    Serial.print(occupancy);
    Serial.println();
    pos = newPos;

    // set barriers on occupancy
    if (0 >= occupancy)
    {
      occupancy = 0;
    }
    else if (occupancy >= capacity)
    {
      occupancy = capacity;
    }
    update_all_GSlice_UI();

    // update LEDs
    update_LEDs();
    last = now;
    last_occupancy = occupancy;
  }

  //
  // wait at least 3 seconds since last change before pushing to api.chalmers.project
  //
  now = millis();
  if (now - last >= 3000 && change_to_push)
  {
    if (enable_internet == true)
    {
      gslc_SetPageCur(&m_gui, E_PG_CLOUDSYNC);
      gslc_Update(&m_gui);
      Serial.println("pushing to " + (String)_API_HOST + "!");
      occupancy_request(client, "push", occupancy, capacity);
      change_to_push = false;
      last = now; // reset last counter so that pull sync happens at a minimum 30 seconds from now.
      gslc_SetPageCur(&m_gui, E_PG_MAIN);
      gslc_Update(&m_gui);
    }
  }
  //
  // wait at least 70 seconds since last change before pushing to cloud.chalmersproject.com
  //

  pull_from_cloud(now, last, client, pull_wait, enable_internet, change_to_push, occupancy, capacity);
  now = millis();

  now = millis();
  support_button_clicked(encoder_button_pin, now, encoder_button_timer);
}
