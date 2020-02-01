const int dial_pin = A0;
int dial_value, current_value, last_value, mapped_value;
int val_1 = 0;
int val_2 = 500;

//records the time since last time dial status was printed to console
uint32_t last_dial_check = 0;

int check_dial_change()
{
  dial_value = analogRead(dial_pin);
  mapped_value = map(dial_value, val_1, val_2, 0, 10);

  if (now - last_dial_check >= 1000)
  {
    Serial.println("----------------------");
    Serial.println("----------------------");
    Serial.print("dial_value: ");
    Serial.println(dial_value);
    Serial.print("mapped_value: ");
    Serial.println(mapped_value);
    Serial.println("----------------------");
    Serial.println("----------------------");

    last_dial_check = now;
  }

  last_value = current_value;
  current_value = mapped_value;

  if(last_value == current_value)
  {
    return 0;
  }
  else if (last_value == 0 && current_value == 2)
  {
    return 1;
  }
  else if (last_value == 2 && current_value == 10)
  {
    return 1;
  }
  else if (last_value == 10 && current_value == 0)
  {
    return 1;
  }
  else
  {
    return -1;
  }
}
