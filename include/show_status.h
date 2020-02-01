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

void show_lights_status()
{

}

void update_tft_occupancy(int occupancy, int capacity)
{
  tft.fillScreen();
  tft.setCursor(50, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println(occupancy);
  tft.setCursor(30, 55);
  tft.println("----");
  tft.setCursor(40, 80);
  tft.println(capacity);
}

void update_led_occupancy(int occupancy)
{

}
