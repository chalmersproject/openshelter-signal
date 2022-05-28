#ifndef SUPPORT_BUTTON_H
#define SUPPORT_BUTTON_H

#include <external_library_includes.h>
#include <globals/globals.h> //this contains timers used in this script
#include <globals/attributes.h>
#include <subroutines/telegram_init_and_send.h>


/*
## What this is
Function to handle when the rotary encoder's button gets clicked. When it gets clicked and held for button_clicked_wait milliseconds the chalmers signal will send out a "Need Help from this Shelter!" message to a telegram group of Chalmers Project members. A member will then need to visit the shelter the support message came from and find out what they needed help with!

## How this works. 

Is the button clicked?
    If no, 
        # we keep resetting telegram_message_sent to false while button 
        # is released so that a second telegram message can't be sent  
        # without first releasing the button
        set telegram_message_sent to false (resetting it)
        exit and continue in main loop
    If yes, continue.

#
# we only want one telegram message sent per "button 
# clicking event". We don't want the user to be able to 
# continue senting telegram messages by holding the button
# down. So we have this check to ensure we aren't sending a telegram
# message again until it's been reset by releasing the button
#
Was the telegram message sent already (telegram_message_sent flag)?
    If yes, exit and continue in main loop
    If no, continue

If the button was clicked, was the last state we saw it in "unclicked"?
    # As long as the button is held down we will not update button_held_for , allowing it's value to drift from now
    If yes, set button_held_for timer to "now" (resetting it)
    If no, continue. (check that button_held_for =/= "now". if false, exit with error)

If the button is clicked, and it's last state was also clicked, how long has it been clicked?
    If the button is clicked, has the button been held down for longer than...
        50 milliseconds?
            Change screen to "Support Call"
        button_clicked_wait milliseconds?
            Change screen to "Sending Support Call"
            if (send telegram message)
            {
                Change screen to "MESSAGE SENT!"
            } else 
            {
                Change screen to "MESSAGE SEND ERROR!"
            }
            # to make sure another telegram message isn't set
            # we record that we've successfully sent a telegram message
            # (or at least tried to; Maybe the operation failed)
            set telegram_message_sent to True
*/
int handle_support_button()
{
    // record the last state of rotary encoder button before
    // overwriting it with it's current state
    last_button_state = button_state;
    button_state = digitalRead(button_pin);

    // is the button pressed?
    if ( button_state == false)
    {
        // if button is not pressed, exit to main loop without error
        telegram_message_sent = false; // but first make sure telegram_message_sent is reset
        return 0;
    }

    // if the button is pressed, was the telegram message sent already?
    if ( button_state && telegram_message_sent )
    {   
        // if telegram message was sent already exit to main loop 
            // we only want to send one telegram message per "button pressed event"
            // since we're seeing that telegram message was already sent 
            // and telegram_message_sent hasn't been reset yet by releasing the button
            // we know the button is being held down even after message was sent.
            // we can safely exit to main loop
        return 0;
    }

    // if the button is pressed, was the last state of the button unpressed?
    if ( button_state && last_button_state == false )
    {
        // if the button was *just* pressed then as long as the button is held down
        // we will not update button_held_for, allowing it's value to drift from now
        button_clicked_time = now;
        Serial.println("Button was *just* pressed. Starting countdown to send message");
    }

    // If the button is clicked, and it's last state was also clicked, how long has it been clicked?
    if ( button_state && last_button_state )
    {
        // record seconds since button clicked before overwriting it
        last_button_clicked_time_seconds = button_clicked_time_seconds;
        Serial.println("CALACULATING HOW LONG BUTTON HAS BEEN HELD FOR");
        // first lets calculate how long the button has been held
        millis_since_click = now - button_clicked_time;
        // then we'll convert that number from millis to seconds
        button_clicked_time_seconds = (int)( millis_since_click / 1000 );
        
        // within the first 200 millis of holding the button down
        // set the screen to the "sending support message" screen
        // this is limited to the first 200 millis to avoid to many
        // gslc_SetPageCur calls
        if ( 200 >= millis_since_click >= 50)
        {
            Serial.println("Button held 200millis. Starting SUPPORT CALL SCREEN");
            gslc_SetPageCur(&m_gui, E_PG_SUPPORTCALL);
            gslc_Update(&m_gui);
        }

        // if button_clicked_time_seconds has changed, update 
        if (last_button_clicked_time_seconds != button_clicked_time_seconds)
        {
            Serial.println("button_clicked_time_seconds HAS CHANGED");
            // here we convert button_clicked_time_seconds to button_clicked_time_countdown
            // so button_clicked_time_countdown can be printed to the display
            Serial.println("CALCULATING COUNTDOWN NUMBER TO PRINT");
            button_clicked_time_countdown = button_clicked_wait_seconds - button_clicked_time_seconds; 
            Serial.println("COUNTDOWN TIMER =  " + (String)button_clicked_time_countdown);
            // if countdown is greater than zero, print countdown value to display
            if ( button_clicked_time_countdown > 0)
            {
                Serial.println("PRINTING COUNTDOWN TO DISPLAY");
                char string_to_write[MAX_STR];
                snprintf(string_to_write, MAX_STR, "%u", button_clicked_time_countdown);
                gslc_ElemSetTxtStr(&m_gui, m_pElemVal2_5, string_to_write);
                gslc_Update(&m_gui);
            }
            // if countdown is at zero:
                // set screen to "sending help message!" 
                // send telegram message; 
                // set screen to "help message sent!"
            if ( 0 >= button_clicked_time_countdown )
            {
                Serial.println("COUNTDOWN HIT 0, SHOWING SUPPORT MESSAGE");
                // switch screen to SENDING_FOR_SUPPORT screen
                gslc_SetPageCur(&m_gui, E_PG_SUPPORTSENT);
                
                // set screen to SENDING NEED HELP MESSAGE!
                char string_to_write[MAX_STR];
                // snprintf(string_to_write, MAX_STR, "%u", "SENDING NEED HELP");
                // gslc_ElemSetTxtStr(&m_gui, m_pELEM_TEXT18, string_to_write);
                // snprintf(string_to_write, MAX_STR, "%u", "MESSAGE!");
                // gslc_ElemSetTxtStr(&m_gui, m_pELEM_TEXT19, string_to_write);
                // gslc_Update(&m_gui);
                
                Serial.println("SENDING TELEGRAM MESSAGE");
                // send help message to telegram support group
                support_message = (String)shelter_name + ": NEED HELP!";
                bot.sendMessage(CHAT_ID, support_message, "");
                
                // set screen to HELP MESSAGE SENT!
                // snprintf(string_to_write, MAX_STR, "%u", "HELP MESSAGE");
                // gslc_ElemSetTxtStr(&m_gui, m_pELEM_TEXT18, string_to_write);
                // snprintf(string_to_write, MAX_STR, "%u", "SENT!");
                // gslc_ElemSetTxtStr(&m_gui, m_pELEM_TEXT19, string_to_write);
                // gslc_Update(&m_gui);
                delay(1500);

                // record that a telegram message has been sent
                // so that another one won't be if the button is held down
                telegram_message_sent = true;
            }
            // TODO:if countdown is less than zero, throw error
        }
    }
}

// void support_button_clicked()
// {
//     last_button_state = button_state;
//     button_state = digitalRead(button_pin);

//     // button is HIGH when released
//     if (button_state == HIGH)
//     {
//         //while button released, keep button_clicked_time in sync with now
//         button_clicked_time = now;
//         telegram_message_sent = false;
//     }
//     //if button is pressed, allow button_clicked_time to start to drift from now
//     if ((button_state == LOW) && (last_button_state == HIGH))
//     { 
//         Serial.println("begin drifting button_clicked_time and now");
//     }
//     // while button is held down, calculate how many seconds it has been held for
//     if (button_state == LOW)
//     {
//         // so long as button is pushed, keep last_change_time synced with now
//         // to prevent push or pull to cloud happening while support button is pushed
//         last_change_time = now;
//         // record the number of seconds since button was pressed
//         // num of seconds button has been clicked is equal to the difference in time
//         // between now and button_clicked_time
//         // then we convert button_clicked_time_seconds from millis to seconds, rounding up
//         // button_clicked_time_seconds = (int)round((now - button_clicked_time/1000));
//         button_clicked_time_seconds = (int)( (now - button_clicked_time) / 1000 );

//         // Serial.println("Button Clicked Seconds CURRENT: " + (String)button_clicked_time_seconds);
//         // Serial.println("last_button_seconds:          " + (String)last_button_clicked_time_seconds);
//         // Serial.println("button_clicked_time_seconds: " + (String)button_clicked_time_seconds);
//         // if num of seconds has changed since the last time we checked, 
//         // update guiSlice countdown button
//         if (button_clicked_time_seconds != last_button_clicked_time_seconds)
//         {
            
//             Serial.println("Button Clicked Seconds: " + (String)button_clicked_time_seconds);
//             button_clicked_time_countdown = (int)(button_clicked_wait/1000) - button_clicked_time_seconds;
//             char string_to_write[MAX_STR];
//             snprintf(string_to_write, MAX_STR, "%u", button_clicked_time_countdown);
//             gslc_ElemSetTxtStr(&m_gui, m_pElemVal2_5, string_to_write);
//             gslc_Update(&m_gui);
//             // last_button_clicked_time_seconds = button_clicked_time_seconds;
//         }
//         // reset last_button_clicked_time_seconds to current button_clicked_time_seconds
//         // to prepare for the next time we check
//         last_button_clicked_time_seconds = button_clicked_time_seconds;
//     }
//     // if button has been held down length button_clicked_debounce
//     // or if button is being held down and telegram message was *just sent*
//     // set screen to "CALLING FOR HELP COUNTDOWN" screen
//     if (
//         // TODO: these debounces & flags are getting unruly
//         // For now I'll just rely on that the guislice calls will naturally introduce a debounce
//         // but eventually I should move to some kind of scheduler/timer library.
//         // (button_state == LOW) && (( now - button_clicked_time ) >= button_clicked_debounce ) || 
//         (button_state == LOW) && (last_button_state == HIGH) || 
//         (button_state == LOW) && (last_button_state == LOW) && ( telegram_message_sent )
//         )
//     {
//         Serial.println("ENCODER BUTTON PRESSED");
//         Serial.println("START SEND FOR HELP SCREEN");
//         gslc_SetPageCur(&m_gui, E_PG_SUPPORTCALL);
//         gslc_Update(&m_gui);
//         telegram_message_sent = false;
//     } //when button is released, return screen to standard display
//     else if ((button_state == HIGH) && (last_button_state == LOW))
//     {
//         Serial.println("ENCODER BUTTON RELEASED!");
//         gslc_SetPageCur(&m_gui, E_PG_MAIN);
//         gslc_Update(&m_gui);
//         button_clicked_time = now;
//     }

//     if ((now - button_clicked_time) >= button_clicked_wait)
//     {
//         Serial.println("button held for 5 seconds! SEND MESSAGE!");
//         //TODO: switch screen to SENDING_FOR_SUPPORT screen
//         //TODO: send telegram message to support group.
//         support_message = (String)shelter_name + ": NEED SUPPORT!";
//         bot.sendMessage(CHAT_ID, support_message, "");
        
//         gslc_SetPageCur(&m_gui, E_PG_SUPPORTSENT);
//         gslc_Update(&m_gui);
//         delay(1500);
//         telegram_message_sent = true;
//         //reset time to now, so if button is still held
//         button_clicked_time = now;
//     }
//     // if button has been held for button_clicked_wait milliseconds
//     // send

//     // encoder timer starts at zero, so the first time the button is
//     // pressed (now - button_clicked_timer) will likely trigger all the
//     // below if statements.
//     // to combat that I've created this flag which becomes true at the
//     // start of this method, and becomes false once it's completed its
//     // full run
//     // if (countdown_start == false)
//     // {
//     //     countdown_start = true;
//     // }

//     // // trigger support countdown screen after
//     // // 200 millis of button being held down
//     // if (now - button_clicked_time >= button_clicked_wait)
//     // {
//     //     Serial.println("Initiating call for support countdown!");
//     //     gslc_SetPageCur(&m_gui, E_PG_MAIN);
//     //     gslc_Update(&m_gui);
//     // }

//     // if button is pressed, but support message was sent <2000millis ago
//     // return to main page
//     // set 10 second wait before support can be called again
// }
#endif