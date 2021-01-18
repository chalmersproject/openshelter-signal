//////////////////////////////////////////////////////////
//            CHALMERS SIGNAL OCCUPANCY                 //
//////////////////////////////////////////////////////////
/*
The Chalmers Signal Occuapncy Device is a client tally counter
for shelter reception staff. 

Written an Maintained by the Chalmers project info@chalmersproject.com
F/OSS under M.I.T License
*/

///////////////////////////////////////////////////////////////////////////////////////////
//                     Includes                                                          //
///////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>

//display
#include <SPI.h>
#include <TFT_ILI9163C.h>
#include <Adafruit_GFX.h>
#include <RotaryEncoder.h>

//WiFi and HTTPS requests
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> // create TLS connection

//LED
#include <FastLED.h>

//
// JSON Support
//
#include <ArduinoJson.h>

//
// API secret and shelter ID
//
#include <shelter_secrets.h>

///////////////////////////////////////////////////////////////////////////////////////////
//                    Toggles                                                            //
///////////////////////////////////////////////////////////////////////////////////////////

// some chalmers signals have red-pcb 1.44" displays from creatron
// others use the cheaper blue-pcb 1.44" displays from aliexpress
static int display_color = 2; //(blue_pcb = 1; red_pcb = 2)

// for debugging it's useful to turn off the chalmer signal's internet-y abilities. That way we can do things like make changes with it's interface without waiting for it to connect to the internet
static bool enable_internet = true;

// earlier versions of chalmers signals don't have their button attached to the ESP. It's useful to be able to quickly turn off all features of the chalmers signal that use this button.
static bool has_button = false;

///////////////////////////////////////////////////////////////////////////////////////////
//                    Globals                                                            //
///////////////////////////////////////////////////////////////////////////////////////////

//
// Measured occupancy value from the chalmers signal
//
int _MEASUREMENT = 15;
int capacity = 90;

//
// Rotary Encoder Global Variables
//
#define inputCLK 4 // pin
#define inputDT 5
RotaryEncoder encoder(5, 4);

//
// TFT Globals
//
// displays from creatron and aliexpress require different coordinates
#define y1 ((display_color == 1) ? 18 : 42) //top left of top digit
#define y2 ((display_color == 1) ? 48 : 67) //top left of divider line
#define y3 ((display_color == 1) ? 78 : 95) //top left of bottom digit
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
int last_MEASUREMENT; //used to detect when occupancy has grown by one digit ( e.g. 9 -> 10 ) and occupancy has to be wiped from the LCD

//
// LED Globals
//
int hue = 0;
uint32 led_last;
#define NUM_LEDS 8
#define DATA_PIN 15
CRGB leds[NUM_LEDS];
int led_brightness = 64;

///////////////////////////////////////////////////////////////////////////////////////////
//                    FUNCTIONS                                                          //
///////////////////////////////////////////////////////////////////////////////////////////

WiFiClientSecure client;
void initWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(_WIFI_SSID, _WIFI_PWD);

  Serial.println("Connecting..");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.printf("SSID: %s\nIP: %s\n", _WIFI_SSID, WiFi.localIP().toString().c_str());
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

// #define SYNCPRINT_SIZE 256
#define REQBUFF_SIZE 256
#define VARBUFF_SIZE 256
#define RESPBUFF_SIZE 2048

const char *_API_HOST = "https://api.chalmersproject.com/graphql";
// Attempting to do a multi-line variable declaration: HOWTO?
const char *MUTATION = "           \
mutation MeasureShelterOccupancy(  \
  $signalId: ID!                   \
  $signalSecret: String!           \
  $measurement: Int!               \
) {                                \
  measureShelterOccupancy(         \
    input: {                       \
      signalId: $signalId          \
      signalSecret: $signalSecret  \
      measurement: $measurement    \
    }                              \
  ) {                              \
    measurement {                  \
      id                           \
    }                              \
  }                                \
}";

typedef struct graphqlQuery
{
  char req[REQBUFF_SIZE];
  char var[VARBUFF_SIZE];
  int status;
  String resp;
} GraphqlQuery;

// HTTP POST to chalmersproject API
void occupancy_request(WiFiClientSecure client, int _MEASUREMENT)
{
  // GraphqlQuery *graphql = (GraphqlQuery *)malloc(sizeof(GraphqlQuery));
  HTTPClient http;
  DynamicJsonDocument reqJson(1024);
  DynamicJsonDocument varJson(1024);
  varJson["signalId"] = SIGNAL_ID;
  varJson["signalSecret"] = SIGNAL_SECRET;
  varJson["measurement"] = _MEASUREMENT;

  Serial.println("Sending HTTP POST");
  http.begin(client, _API_HOST);
  http.addHeader("Content-Type", "application/json");
  reqJson["query"] = MUTATION;
  reqJson["variables"] = varJson;

  String request;
  serializeJson(reqJson, request);
  Serial.print("Request: ");
  Serial.println(request);

  http.POST(request);

  Serial.print("Response: ");
  Serial.println(http.getString());
}
///////////////////////////////////////////////////////////////////////////////////////////
//                    Rotary Encoder Interrupt                                           //
///////////////////////////////////////////////////////////////////////////////////////////
// flag to mark when the dial has been moved. Calls the LEDs, LCD, and push_to_firebase functions
bool change_to_push = false;

void ICACHE_RAM_ATTR encoder_change_trigger()
{
  encoder.tick();
  Serial.println("interrupt triggered!");
}

///////////////////////////////////////////////////////////////////////////////////////////
//                    MAIN SCRIPT STARTS HERE                                            //
///////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(4), encoder_change_trigger, CHANGE);
  attachInterrupt(digitalPinToInterrupt(5), encoder_change_trigger, CHANGE);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(led_brightness);

  hue = map(_MEASUREMENT, 0, capacity, 171, 0);
  CHSV color = CHSV(hue, 255, 255);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();

  tft.begin();
  tft.setRotation(2);
  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(3);
  tft.println("CHALMERS");
  tft.println("SIGNAL");

  initWifi();
  // HTTPClient http;
  client.setInsecure();
  if (WiFi.status() == WL_CONNECTED)
  {
    tft.clearScreen(BLACK);
    tft.println("CONNECTED!");
    delay(4000);
    tft.clearScreen(BLACK);
  }
}

unsigned long now, last;

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
      _MEASUREMENT--;
    }
    else if (newPos > pos)
    {
      _MEASUREMENT++;
    }
    Serial.print("_MEASUREMENT: ");
    Serial.print(_MEASUREMENT);
    Serial.println();
    pos = newPos;

    //set barriers on _MEASUREMENT
    if (0 >= _MEASUREMENT)
    {
      _MEASUREMENT = 0;
    }
    else if (_MEASUREMENT >= capacity)
    {
      _MEASUREMENT = capacity;
    }
    tft.setCursor(35, y1);
    // used to detect when _MEASUREMENT has grown by one digit ( e.g. 10 -> 9 ) and _MEASUREMENT has to be wiped from the LCD
    if (_MEASUREMENT == 9 && last_MEASUREMENT == 10 || _MEASUREMENT == 99 && last_MEASUREMENT == 100)
    {
      tft.fillRect(35, y1, tft.width(), (y2 - 25), BLACK);
      last_MEASUREMENT = _MEASUREMENT;
    }
    tft.println(_MEASUREMENT);
    // update LEDs
    hue = map(_MEASUREMENT, 0, capacity, 171, 0);
    CHSV color = CHSV(hue, 255, 255);
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    change_to_push = true;
    last = now;
    last_MEASUREMENT = _MEASUREMENT;
  }

  //
  // wait at least 3 seconds since last change before pushing to api.chalmers.project
  //
  now = millis();
  if (now - last >= 3000 && change_to_push)
  {
    if (enable_internet == true)
    {
      occupancy_request(client, _MEASUREMENT);
      change_to_push = false;
    }
  }
}
