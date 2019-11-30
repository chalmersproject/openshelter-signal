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
