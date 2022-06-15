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

String shelter_name;
String signal_class;
// flag to mark when the dial has been moved
bool change_to_push = false;
bool encoder_button_pressed = false;
String support_message;

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
unsigned long button_clicked_time, millis_since_click;
// True when rotary encoder button is pushed
bool button_pushed;
// Current state of rotary encoder button. True when rotary encoder button is pressed.
bool button_state;
// the last state of the rotary encoder 
bool last_button_state;
bool countdown_start;
// flag to track if support message was just sent
// used to reset back to "START SEND FOR HELP SCREEN" incase 
// user holds down the button after countdown completes and
// support message is sent
bool telegram_message_sent = false;
// used to calculate how many seconds button has been held for
int button_clicked_time_seconds, last_button_clicked_time_seconds, button_clicked_time_countdown;


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