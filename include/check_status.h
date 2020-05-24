const int dial_pin = A0;
int dial_value, current_value, last_value, mapped_value;
int val_1 = 0;
int val_2 = 500;


int counter = 0;
int currentStateCLK;
int previousStateCLK;

//records the time since last time dial status was printed to console
uint32_t last_dial_check = 0;

int check_dial_change()
{
  // Read the current state of inputCLK
    currentStateCLK = digitalRead(inputCLK);

    // If the previous and the current state of the inputCLK are different then a pulse has occured
    if (currentStateCLK != previousStateCLK){

      // If the inputDT state is different than the inputCLK state then
      // the encoder is rotating counterclockwise
      if (digitalRead(inputDT) != currentStateCLK) {
        counter --;
        encdir ="CCW";
      } else {
        // Encoder is rotating clockwise
        counter ++;
        encdir ="CW";
      }
      Serial.print("Direction: ");
      Serial.print(encdir);
      Serial.print(" -- Value: ");
      Serial.println(counter);
    }
    // Update previousStateCLK with the current state
    previousStateCLK = currentStateCLK;
}
