#define TFT_DC 9
#define TFT_CS 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
String hello_world = "Hello World!";
void tft_test()
{
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(0, 0);

  //text properties
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println(hello_world);
  tft.drawLine(3, tft.height() /2 + 3, tft.width() - 3, tft.height() /2 + 3, ILI9341_RED);
}
