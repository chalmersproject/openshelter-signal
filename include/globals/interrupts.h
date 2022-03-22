#ifndef INTERRUPTS_H
#define INTERRUPTS_H

void ICACHE_RAM_ATTR encoder_change_trigger()
{
    encoder.tick();
    // Serial.println("interrupt triggered!");
}

void ICACHE_RAM_ATTR encoder_button_trigger()
{
    encoder_button_pressed = true;
    // Serial.println("encoder button was pressed!");
}

void init_interrupts()
{
    attachInterrupt(digitalPinToInterrupt(4), encoder_change_trigger, CHANGE);
    attachInterrupt(digitalPinToInterrupt(5), encoder_change_trigger, CHANGE);
    pinMode(button_pin, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(encoder_button_pin), encoder_button_trigger, ONLOW);
}
#endif
