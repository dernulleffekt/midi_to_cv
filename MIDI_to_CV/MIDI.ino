/****************************************************
 * Setup for the Midi library
 *
 * https://github.com/FortySevenEffects/arduino_midi_library/releases/tag/4.2
 *****************************************************/

void MIDIsetup()
{
  // Connect the handler functions to the library,
  // so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandleClock(handleClock);
  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI);
}
