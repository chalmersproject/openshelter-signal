#ifndef GLOBALS_H
#define GLOBALS_H

// flag to mark when the dial has been moved
bool change_to_push = false;
bool encoder_button_pressed = false;
unsigned long now, last, encoder_button_timer;

#endif