void show_wifi_connected()
{
  //show connected on display!
  tft.fillScreen();
  tft.setCursor(10, 50);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Connected to Internet!");
  tft.println("  to");
  tft.println("  Internet!");
}
void show_chalmers_start()
{
  tft.fillScreen();
  tft.setCursor(16, 50);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Chalmers ");
  tft.println("  Signal!");
}


void update_tft_occupancy(int occupancy, int capacity)
{
  tft.fillScreen();
  tft.setCursor(35, 10);
  tft.setTextColor(WHITE);
  tft.setTextSize(5);
  tft.println(occupancy);
  tft.setCursor(8, 42);
  tft.println("----");
  tft.setCursor(20, 75);
  tft.println(capacity);
}


int hue = 0;
uint32 led_last;
void update_led_occupancy(int occupancy, int capacity)
{ 
  //empty occupancy = blue / 171
  //full occupancy  = red / 0
  hue = map(occupancy, 0, capacity, 171, 0);
  CHSV color = CHSV(hue, 255, 255);
  fill_solid(leds,NUM_LEDS, color);
  FastLED.show();
}
