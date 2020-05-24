const int dial_pin = A0;
int dial_value, current_value, last_value, mapped_value;
int val_1 = 0;
int val_2 = 500;


float counter = 0;


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
        counter = counter - 0.5;
      } else {
        // Encoder is rotating clockwise
        counter = counter + 0.5;
      }
      // each "bump" on the rotary encoder counts for 2 "steps"
      // there's a step in between each bump/resting point of the dial
      // so I added this if statement that only returns +1 or -1 after doing a whole bump/two steps
      if (counter == 1)
      {
        counter = 0;
        firecode_occupancy++;
      } else if (counter == -1)
      {
        counter = 0;
        firecode_occupancy--;
      }
    }
    // Update previousStateCLK with the current state
    previousStateCLK = currentStateCLK;
    last_dial_check = now;
}
