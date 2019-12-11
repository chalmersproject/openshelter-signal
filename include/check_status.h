#define dial_pin 16
int dial_value, current_value, last_value;
int val_1 = 300;
int val_2 = 600;
int val_3 = 900;
int find_dial_values()
{
  dial_value = analogRead(dial_pin);

  if(dial_value >= val_3)
  {
    return 1;
    // break;
  }
  else if(dial_value >= val_2)
  {
    return 0;
    // break;
  }
  else if(dial_value >= val_1)
  {
    return -1;
    // break;
  }
  else
  {
    Serial.println("ERROR: adjust dial_values");
    return -2;
  }
}

int check_dial_change()
{
  last_value = current_value;
  current_value = find_dial_values();
  if(last_value == current_value)
  {
    return 0;
  }
  else if (last_value == 0 && current_value == 1){
    return 1;
  }
  else if (last_value == 1 && current_value == 2){
    return 1;
  }
  else if (last_value == 2 && current_value == 0)
  {
    return 1;
  }
  else{
    return -1;
  }
}
