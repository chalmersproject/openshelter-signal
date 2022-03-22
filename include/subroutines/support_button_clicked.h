bool countdown_start;

void support_button_clicked(int button_pin, unsigned long now, unsigned long button_clicked_timer)
{
    //
    // encoder button getting pressed
    //
    if (digitalRead(button_pin) == LOW)
    {
        // encoder timer starts at zero, so the first time the button is
        // pressed (now - button_clicked_timer) will likely trigger all the
        // below if statements.
        // to combat that I've created this flag which becomes true at the
        // start of this method, and becomes false once it's completed its
        // full run
        if (countdown_start == false)
        {
            countdown_start = true;
        }

        // trigger support countdown screen after
        // 200 millis of button being held down
        if (now - button_clicked_timer >= 200)
        {
            Serial.println("Initiating call for support countdown!");
            gslc_SetPageCur(&m_gui, E_PG_MAIN);
            gslc_Update(&m_gui);
        }

        // if button is pressed, but support message was sent <2000millis ago
        // return to main page
        // set 10 second wait before support can be called again
    }
}