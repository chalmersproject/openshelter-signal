#ifndef SUPPORT_BUTTON_H
#define SUPPORT_BUTTON_H

#include <external_library_includes.h>
#include <globals/globals.h> //this contains timers used in this script
#include <globals/attributes.h>

bool countdown_start;

void support_button_clicked()
{
    last_button_state = button_state;
    button_state = digitalRead(button_pin);

    //
    // if button is pressed, and was previously released
    if ((button_state == LOW) && (last_button_state == HIGH))
    {
        // if button is getting clicked, start timing how long
        button_clicked_time = now;
        Serial.println("ENCODER BUTTON PRESSED!");
    }
    else if ((button_state == HIGH) && (last_button_state == LOW))
    {
        button_clicked_time = 0;
        Serial.println("ENCODER BUTTON RELEASED!");
    }
    else if (button_state == last_button_state)
    {
    }

    if ((now - button_clicked_time) >= button_clicked_wait)
    {
        Serial.println("button held for 5 seconds! SEND MESSAGE!");
        button_clicked_time = 0;
    }
    // if button has been held for button_clicked_wait milliseconds
    // send

    // encoder timer starts at zero, so the first time the button is
    // pressed (now - button_clicked_timer) will likely trigger all the
    // below if statements.
    // to combat that I've created this flag which becomes true at the
    // start of this method, and becomes false once it's completed its
    // full run
    // if (countdown_start == false)
    // {
    //     countdown_start = true;
    // }

    // // trigger support countdown screen after
    // // 200 millis of button being held down
    // if (now - button_clicked_time >= button_clicked_wait)
    // {
    //     Serial.println("Initiating call for support countdown!");
    //     gslc_SetPageCur(&m_gui, E_PG_MAIN);
    //     gslc_Update(&m_gui);
    // }

    // if button is pressed, but support message was sent <2000millis ago
    // return to main page
    // set 10 second wait before support can be called again
}
#endif