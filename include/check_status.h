volatile int counter = 0;
volatile int currentStateCLK;
volatile int previousStateCLK;

int read_dial_change()
{
  // Serial.print("Dial Counter [1]: "); Serial.println(counter);
  // // Read the current state of inputCLK
  //   stateCLK = digitalRead(inputCLK);
  //   // If the inputDT state is different than the inputCLK state then
  //   // the encoder is rotating counterclockwise
  //   if (digitalRead(inputDT) != stateCLK) {
  //     Serial.print("Dial Counter [2]: "); Serial.println(counter);
  //     counter--;
  //   } else {
  //     // Encoder is rotating clockwise
  //     Serial.print("Dial Counter [2]: "); Serial.println(counter);
  //     counter++;
  //   }
  //   if (counter % 2 == 0)
  //   {
  //     Serial.print("Dial Counter [3]: "); Serial.println(counter);
  //     return counter/2;
  //     counter = 0;
  //   } else
  //   {
  //     Serial.print("Dial Counter [3]: "); Serial.println(counter);
  //     return 0;
  //   }
    // Read the current state of inputCLK
     currentStateCLK = digitalRead(inputCLK);

     // If the previous and the current state of the inputCLK are different then a pulse has occured
     if (currentStateCLK != previousStateCLK){

       // If the inputDT state is different than the inputCLK state then
       // the encoder is rotating counterclockwise
       if (digitalRead(inputDT) != currentStateCLK) {
         counter --;
         // encdir ="CCW";
       } else {
         // Encoder is rotating clockwise
         counter ++;
         // encdir ="CW";
       }
       // Serial.print("Direction: ");
       // Serial.print(encdir);
       Serial.print(" -- Value: ");
       Serial.println(counter);
     }
     // Update previousStateCLK with the current state
     previousStateCLK = currentStateCLK;
}
