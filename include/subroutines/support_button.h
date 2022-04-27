#ifndef SUPPORT_BUTTON_H
#define SUPPORT_BUTTON_H

#include <external_library_includes.h>
#include <globals/globals.h> //this contains timers used in this script
#include <globals/attributes.h>
#include <subroutines/telegram_init_and_send.h>

bool countdown_start;
// flag to track if support message was just sent
// used to reset back to "START SEND FOR HELP SCREEN" incase 
// user holds down the button after countdown completes and
// support message is sent
bool telegram_message_sent = false;

// used to calculate how many seconds button has been held for
int button_clicked_time_seconds, last_button_clicked_time_seconds, button_clicked_time_countdown;
void support_button_clicked()
{
    last_button_state = button_state;
    button_state = digitalRead(button_pin);

    // button is HIGH when released
    if (button_state == HIGH)
    {
        //while button released, keep button_clicked_time in sync with now
        button_clicked_time = now;
        telegram_message_sent = false;
    }
    //if button is pressed, allow button_clicked_time to start to drift from now
    if ((button_state == LOW) && (last_button_state == HIGH))
    { 
        Serial.println("begin drifting button_clicked_time and now");
    }
    // while button is held down, calculate how many seconds it has been held for
    if (button_state == LOW)
    {
        // so long as button is pushed, keep last_change_time synced with now
        // to prevent push or pull to cloud happening while support button is pushed
        last_change_time = now;
        // record the number of seconds since button was pressed
        // num of seconds button has been clicked is equal to the difference in time
        // between now and button_clicked_time
        // then we convert button_clicked_time_seconds from millis to seconds, rounding up
        // button_clicked_time_seconds = (int)round((now - button_clicked_time/1000));
        button_clicked_time_seconds = (int)( (now - button_clicked_time) / 1000 );

        // Serial.println("Button Clicked Seconds CURRENT: " + (String)button_clicked_time_seconds);
        // Serial.println("last_button_seconds:          " + (String)last_button_clicked_time_seconds);
        // Serial.println("button_clicked_time_seconds: " + (String)button_clicked_time_seconds);
        // if num of seconds has changed since the last time we checked, 
        // update guiSlice countdown button
        if (button_clicked_time_seconds != last_button_clicked_time_seconds)
        {
            
            Serial.println("Button Clicked Seconds: " + (String)button_clicked_time_seconds);
            button_clicked_time_countdown = (int)(button_clicked_wait/1000) - button_clicked_time_seconds;
            char string_to_write[MAX_STR];
            snprintf(string_to_write, MAX_STR, "%u", button_clicked_time_countdown);
            gslc_ElemSetTxtStr(&m_gui, m_pElemVal2_5, string_to_write);
            gslc_Update(&m_gui);
            // last_button_clicked_time_seconds = button_clicked_time_seconds;
        }
        // reset last_button_clicked_time_seconds to current button_clicked_time_seconds
        // to prepare for the next time we check
        last_button_clicked_time_seconds = button_clicked_time_seconds;
    }
    // if button has been held down length button_clicked_debounce
    // or if button is being held down and telegram message was *just sent*
    // set screen to "CALLING FOR HELP COUNTDOWN" screen
    if (
        // TODO: these debounces & flags are getting unruly
        // For now I'll just rely on that the guislice calls will naturally introduce a debounce
        // but eventually I should move to some kind of scheduler/timer library.
        // (button_state == LOW) && (( now - button_clicked_time ) >= button_clicked_debounce ) || 
        (button_state == LOW) && (last_button_state == HIGH) || 
        (button_state == LOW) && (last_button_state == LOW) && ( telegram_message_sent )
        )
    {
        Serial.println("ENCODER BUTTON PRESSED");
        Serial.println("START SEND FOR HELP SCREEN");
        gslc_SetPageCur(&m_gui, E_PG_SUPPORTCALL);
        gslc_Update(&m_gui);
        telegram_message_sent = false;
    } //when button is released, return screen to standard display
    else if ((button_state == HIGH) && (last_button_state == LOW))
    {
        Serial.println("ENCODER BUTTON RELEASED!");
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        gslc_Update(&m_gui);
        button_clicked_time = now;
    }

    if ((now - button_clicked_time) >= button_clicked_wait)
    {
        Serial.println("button held for 5 seconds! SEND MESSAGE!");
        //TODO: switch screen to SENDING_FOR_SUPPORT screen
        //TODO: send telegram message to support group.
        support_message = (String)shelter_name + ": NEED SUPPORT!";
        bot.sendMessage(CHAT_ID, support_message, "");
        telegram_message_sent = true;
        //reset time to now, so if button is still held
        button_clicked_time = now;
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