#ifndef GLOBALS_H
#define GLOBALS_H

// occupancy global. keeps track of what the signal is reporting as
// the shelter's current occupancy status
int occupancy = 0;
// used to keep track of whatever the last occupancy value was.
// useful for determining when a occupancy change has occured.
int last_occupancy = 0;
// capacity global. keeps track of what the signal is reporting as
// the shelter's total amount of space for clients, either
// sitting space or bed space.
int capacity = 100;

// flag to mark when the dial has been moved
bool change_to_push = false;
bool encoder_button_pressed = false;
//
// records the state of millis() once per cycle
// millis() == how many milliseconds since micocomputer started up
unsigned long now;
//
// timer that records how long since last time dial was changed
// last_change_time is reset to value of now/millis() whenever:
// - the dial gets moved
// - a push to the API is made
// - a pull from the API is made
// gets initialized at the value of pull_wait attribute. That's so when sync_to_cloud("pull") gets called in setup the last change timer will have a high enough time that the pull happens.
unsigned long last_change_time = pull_wait;
//
// timer that records how long since the encoder's click-y button was pressed
unsigned long button_clicked_time;

//
// Rotary Encoder Global Variables
//

// rotary encoder clicky button
#define button_pin 0

// pin 1 on rotary encoder
#define inputCLK 4

// pin 2 on rotary encoder
#define inputDT 5

// the RotaryEncoder Library object
RotaryEncoder encoder(5, 4);

// tracks absolute position of dial.
// i.e. (all it's clockwise turns) - (all it's couterclockwise turns)
// since the signal started up
int pos = 0;

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