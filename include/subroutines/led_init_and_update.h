#include <external_library_includes.h>
#ifndef LED_INIT_AND_UPDATE_H
#define LED_INIT_AND_UPDATE_H

int map_color(int * rgb_array, int occupancy, int capacity)
{
    // LED ring takes argument Color which is tuple ( (r,g,b), a) values

    // This function takes occupancy, capacity as input
    // As output it fills an array of occupancy/capacity 
    // mapped green -> red as an rgb value
    
    // map occupancy value to 0-255 such that
    // as occupancy moves further from capacity and closer to 0
    // green moves closer from 0 to 255
    int green = map(occupancy, capacity, 0,  0, 255);

    // do the same operation, but in reverse, for red value
    int red = map(occupancy, 0, capacity, 0, 255);

    rgb_array[0] = red;
    rgb_array[1] = green;
    rgb_array[2] = 0;
}

void init_LEDs()
{
    // UNUSED FastLED library bindings
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(led_brightness);
    
    //
    // Instatiate Adafruit Neopixel Class
    // Adafruit_NeoPixel led_ring(NUM_LEDS,LED_DATA_PIN,NEO_GRBW + NEO_KHZ800);
    // led_ring.begin();

    // int rgb_array[3];
    // map_color(rgb_array, occupancy, capacity);
    // Serial.print("RGBA Array of mapped occupancy/capacity values: ");

    // Serial.println((String)rgb_array[0] + (String)rgb_array[1] + (String)rgb_array[2]);

    // hue = map(occupancy, 0, capacity, 90, 0);
    // CHSV color = CHSV(hue, 255, 255);
    // fill_solid(leds, NUM_LEDS, color);
    // FastLED.show();
}

void update_LEDs()
{
    hue = map(occupancy, 0, capacity, 90, 0);
    CHSV color = CHSV(hue, 255, 255);
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    change_to_push = true;
}

#endif