/*
   Configuration.h
   Francesco Pasino
   Settembre 2016
   v0.1
   Controller MIDI with 8 capacitive sensors
   and 3 pot for Teensy 3.2
*/

/******************
  Protocol
*******************/
//#define SERIAL
#define MIDI
//#define KEYBOARD // Not supported
//#define JOYSTICK // Not supported

/******************
   Touch sensibility
*******************/
#define THRESHOLD 2000

/******************
   Delay in microseconds
*******************/
#define DELAY 100


/******************
   MIDI PROTOCOL
*******************/
// Analog Resolution of pots
#define ANALOG_RES 7
// MIDI Channel
#define CHANNEL 1

/******************
   Other
*******************/
#ifndef ANALOG_RES
#define ANALOG_RES 7
#endif
