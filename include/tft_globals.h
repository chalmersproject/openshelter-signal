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