#include <external_library_includes.h>
#ifndef LED_INIT_AND_UPDATE_H
#define LED_INIT_AND_UPDATE_H

void init_LEDs()
{
    //
    // start LED with color of occupancy / capacity

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(led_brightness);

    hue = map(occupancy, 0, capacity, 90, 0);
    CHSV color = CHSV(hue, 255, 255);
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
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