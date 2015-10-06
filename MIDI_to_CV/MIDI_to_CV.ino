/****************************************************
 * Midi to CV
 *
 * dernulleffekt.de
 * Wolfgang Spahn
 *
 * An arduino leonardo program for a MIDI to CV interface with 4 fast PWM and 2 ADC outputs
 *
 * To change the Midi Channels for the Notes change NoteChannel1 and 2
 * and to change the Control Change Channel and Number change CCChannel and CCNumber
 * To change the Midi Clock divider change ClockDivider
 * and to change the length of the interval for the Clock Pin change ClockInterval
 *
 *****************************************************/

// include the libraries:
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
#include <SPI.h>

byte NoteChannel1 = 1;     // Cannel Number (1-16) of Note & Velocity Nr 1
byte NoteChannel2 = 2;     // Cannel Number (1-16) of Note & Velocity Nr 2
byte CCChannel1 = 1;        // Control Cannel (1-16)
byte CCNumber1 = 1;         // Control Number (1-127)
byte CCChannel2 = 2;        // Control Cannel (1-16)
byte CCNumber2 = 1;         // Control Number (1-127)

int ClockInterval = 20;          // length of the pulse at the clock pin in milliseconds
int ClockDivider = 24;           // Midi Clock sends 24 times per quarter note 
int ClockCounter = 0;            // counter for the Midi Clock
int ClockActiv = 0;             

int Gate1Pin = 7;                // Pin of the Gate Nr 1
int Gate2Pin = 8;                // Pin of the Gate Nr 2
int MidiClockPin = 4;

unsigned long SwitchMillis = 0;  // the time when the clock pin is set high   
unsigned long CurrentMillis = 0; // the actual time
int Verbose = 0;


void setup()
{
  for (int i = 4; i < 11; i++)
  {
    pinMode(i, OUTPUT);
  }
  MIDIsetup();
  DACsetup();
  PWMsetup();
  Serial.begin(9600);
}


void loop() {
  CheckClock();
  MIDI.read();
  while (MIDIUSB.available() > 0) // Repeat while notes are available to read.
  {
    MIDIEvent e;
    e = MIDIUSB.read();
    // Parse MIDI:
    // m1 = type = Status Byte
    // m2 = Data Byte 1
    // m3 = Data Byte 2
    if (e.m1 >= 144 && e.m1 <= 159)         // Note ON (144 -159)
    {
      e.m1 = e.m1 - 143;                    // Channel 1 - 16 instead of 144 - 159
      if (e.m3 > 0)                         // vilocity 0 = Note OFF
      {
        handleNoteOn (e.m1, e.m2, e.m3);
      }
      else handleNoteOff (e.m1, e.m2, e.m3);
    }
    else if (e.m1 >= 128 && e.m1 <= 143)    // Note OFF (128 - 143)
    {
      e.m1 = e.m1 - 127;                    // Channel 1 - 16 instead of 128 - 143
      handleNoteOff (e.m1, e.m2, e.m3);
    }
    else if (e.m1 >= 176 && e.m1 <= 191)    // Control (176 - 191)
    {
      e.m1 = e.m1 - 175;                    // Channel 1 - 16 instead of 176 - 191
      handleControlChange (e.m1, e.m2, e.m3);
    }
     else if (e.m1 == 248)                  // MIDI Clock (248)
    {
      handleClock();
    }
    MIDIUSB.flush();
  }
}

