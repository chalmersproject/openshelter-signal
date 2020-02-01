const int dial_pin = A0;
int dial_value, current_value, last_value, mapped_value;
int val_1 = 0;
int val_2 = 500;

//records the time since last time dial status was printed to console
uint32_t last_dial_check = 0;

int check_dial_change()
{
  if (now - last_dial_check >= 300)
  {
    Serial.println("----------------------");
    Serial.println("----------------------");
    Serial.print("dial_value: ");
    Serial.println(dial_value);
    Serial.print("mapped_value: ");
    Serial.println(mapped_value);
    Serial.println("----------------------");
    Serial.println("----------------------");
    Serial.println("");
    Serial.println("");

    last_dial_check = now;
  }

  dial_value = analogRead(dial_pin);
  mapped_value = map(dial_value, val_1, val_2, 0, 5);
  // if mapped_value resolves to some value other than the known discrete dial values
  // then analogRead was probably run while the dial was between positions and pin A0's
  // PWM resolved something between the last dial position and the next dial position
  //
  // therefore set mapped_value to the last recoorded value
  if(mapped_value != 0 && mapped_value != 1 && mapped_value !=5)
  {
    Serial.println("mapped_value came out to something strange!");
    Serial.print("Mapped Value: ");
    Serial.println(mapped_value);
    mapped_value = current_value; //at this point current_value is actually the last recorded value, not last_value
  }

  last_value = current_value;
  current_value = mapped_value;

  if(last_value == current_value)
  {
    return 0;
  }
  else if (last_value == 0 && current_value == 1)
  {
    return 1;
  }
  else if (last_value == 1 && current_value == 5)
  {
    return 1;
  }
  else if (last_value == 5 && current_value == 0)
  {
    return 1;
  }
  else
  {
    return -1;
  }
}
