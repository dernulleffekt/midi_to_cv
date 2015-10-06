/****************************************************
 * MIDI handler
 *****************************************************/

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if (Verbose == 1)
  {
    Serial.print("NoteOn::");
    Serial.print(channel);
    Serial.print("--");
    Serial.print(pitch);
    Serial.print("--");
    Serial.println(velocity);
  }
  int Ppitch = map(pitch, 0, 95, 0, 4000);
  int Vvelocity = map(velocity, 0, 127, 0, 255);
  if (channel == NoteChannel1)
  {
    digitalWrite(Gate1Pin, HIGH);
    setDac(Ppitch, 0);
    setPWM9(Vvelocity);
  }
  else if (channel == NoteChannel2)
  {
    digitalWrite(Gate2Pin, HIGH);
    setDac(Ppitch, 1);
    setPWM10(Vvelocity);
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  if (Verbose == 1)
  {
    Serial.print("NoteOff::");
    Serial.print(channel);
    Serial.print("--");
    Serial.print(pitch);
    Serial.print("--");
    Serial.println(velocity);
  }
  if (channel == NoteChannel1)
  {
    digitalWrite(Gate1Pin, LOW);
    setPWM9(0);
  }
  else if (channel == NoteChannel2)
  {
    digitalWrite(Gate2Pin, LOW);
    setPWM10(0);
  }
}

void handleControlChange(byte channel, byte number, byte value)
{
  if (Verbose == 1)
  {
    Serial.print("ControlCange::");
    Serial.print(channel);
    Serial.print("--");
    Serial.print(number);
    Serial.print("--");
    Serial.println(value);
  }
  int Vvalue = map(value, 0, 127, 0, 255);
  if (channel == CCChannel1)
  {
    if (number == CCNumber1)
    {
      setPWM6(Vvalue);
    }
  }
  if (channel == CCChannel2)
  {
    if (number == CCNumber2)
    {
      setPWM5(Vvalue);
    }
  }
}

void handleClock()
{
  ClockCounter += 1;
  if (ClockCounter > ClockDivider)
  {
    digitalWrite(MidiClockPin, HIGH);
    SwitchMillis = millis();
    ClockCounter = 0;
    ClockActiv = 1;
  }
}

