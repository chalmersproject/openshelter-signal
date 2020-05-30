int counter = 0;
int read_dial_change()
{
  // Read the current state of inputCLK
    stateCLK = digitalRead(inputCLK);
    // If the inputDT state is different than the inputCLK state then
    // the encoder is rotating counterclockwise
    if (digitalRead(inputDT) != stateCLK) {
      counter--;
    } else {
      // Encoder is rotating clockwise
      counter++;
    }
    if (counter % 2 == 0)
    {
      return counter/2;
      counter = 0;
    } else
    {
      return 0;
    }
}
