void connect_Serial(){
    Serial.begin(115200);
    Serial.println();
    Serial.println();
}

// Rotary Encoder Inputs
#define inputCLK 5
#define inputDT 4
void connect_Rotary_Encoder(){
  // Set encoder pins as inputs
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);

  // Read the initial state of inputCLK
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(inputCLK);
}

void connect_Wifi(){
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

void connect_Firebase(){
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
}

void connect_TFT()
{
  // All wiring required, only 3 defines for hardware SPI on 328P
  #define __DC 0
  #define __CS 2

  // Color definitions
  #define	BLACK   0x0000
  #define	BLUE    0x001F
  #define	RED     0xF800
  #define	GREEN   0x07E0
  #define CYAN    0x07FF
  #define MAGENTA 0xF81F
  #define YELLOW  0xFFE0
  #define WHITE   0xFFFF

  TFT_ILI9163C tft = TFT_ILI9163C(__CS, __DC);
  tft.begin();
}

void connect_LED()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(led_brightness);
}
