/****************************************************
 * Switch the pin for the Midi Clock
 *****************************************************/

// checks the actual time, turns off the clock pin if the interval is reached
void CheckClock()
{
  if (ClockActiv == 1)
  {
    CurrentMillis = millis();
    if (CurrentMillis - SwitchMillis >= ClockInterval)
    {
      digitalWrite(MidiClockPin, LOW);
      ClockActiv = 0;
    }
  }
}
