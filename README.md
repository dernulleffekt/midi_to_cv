# midi_to_cv
An Arduino Leonardo program for a MIDI to Control Voltage (CV) interface

It support 4 fast PWM, 2 ADC outputs and 3 Outputs and has MIDI and MIDI-USB support:
- 2x Note  1V/Okt
- 2x Velocity  0 -> 5V
- 2x Gate On/Off
- 1x Clock
- 2x Control Change 0 -> 5V

The hardware for the project is on:
http://paperpcb.dernulleffekt.de/doku.php?id=paper_synth:midi_to_cv

One needs to install the MIDI-USB support for Arduino at:
https://github.com/rkistner/arcore.git
