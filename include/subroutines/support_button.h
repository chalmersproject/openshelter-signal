#ifndef SUPPORT_BUTTON_H
#define SUPPORT_BUTTON_H

#include <external_library_includes.h>
#include <globals/globals.h> //this contains timers used in this script
#include <globals/attributes.h>
#include <subroutines/telegram_init_and_send.h>


/*
## What this is
Function to handle when the rotary encoder's button gets clicked. When it gets clicked and held for button_clicked_wait milliseconds the chalmers signal will send out a "Need Help from this Shelter!" message to a telegram group of Chalmers Project members. A member will then need to visit the shelter the support message came from and find out what they needed help with!
*/
int countdown = support_call_wait_seconds;

void call_for_support()
{
    Serial.println("SENDING TELEGRAM MESSAGE");
    // send help message to telegram support group
    support_message = (String)shelter_name + ": NEED HELP!";
    bot.sendMessage(CHAT_ID, support_message, "");
}

void update_guislice_countdown()
{
    gslc_SetPageCur(&m_gui, E_PG_SUPPORTCALL);
    // update number on guislice countdown screen
    char string_to_write[MAX_STR];
    snprintf(string_to_write, MAX_STR, "%u", countdown);
    gslc_ElemSetTxtStr(&m_gui, m_pElemVal2_5, string_to_write);
    gslc_Update(&m_gui);
    countdown--;
}
void handle_support_button_timer(){
    // if button is clicked start timer
    // check if telegram_message_sent has been reset by releasing button
    SetTimer( countdown_timer,  1000 , update_guislice_countdown);
    SetTimer( support_timer,  support_call_wait, call_for_support);

    button_state = digitalRead(button_pin);
    // LOW means pressed; HIGH means released
    if ( (button_state == LOW) && (telegram_message_sent == false) ) 
    {   
        // every one second button is held down, update the countdown on GuiSlice
        countdown_timer.check();
        support_timer.check();
        // reset global push timer
        last_change_time = now;
    } else if (telegram_message_sent == true || button_state == HIGH)
    {   
        // once telegram message is sent or button is released
        // countdown_timer, support_timer is reset
        // countdown is reset
        // guislice is reset back to main screen
        countdown_timer.reset();
        support_timer.reset();
        countdown = support_call_wait_seconds;
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        gslc_Update(&m_gui);
        // telegram_message_sent is reset once button is released 
        if (button_state == HIGH)
        {
            telegram_message_sent == false;
        }

        if (telegram_message_sent)
        {
            // reset global push timer
            last_change_time = now;
        }
    } 
}

#endif