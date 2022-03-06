#ifndef GLOBALS_H
#define GLOBALS_H

// flag to mark when the dial has been moved
bool change_to_push = false;
bool encoder_button_pressed = false;
//
// records the state of millis() once per cycle
// millis() == how many milliseconds since micocomputer started up
unsigned long now;
//
// timer that records how long since last time dial was changed
unsigned long last_change_time;
//
// timer that records how long since the encoder's click-y button was pressed
unsigned long encoder_button_time;
int occupancy, capacity, last_occupancy;

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

#endif