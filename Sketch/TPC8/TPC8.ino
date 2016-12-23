/*
   TPC8.ino
   Francesco Pasino
   Settembre 2016
   v0.1
   Controller MIDI with 8 capacitive sensors
   and 3 pot for Teensy 3.2
*/

#include "Configuration.h"
int velocity = 127;

// Touch Button *************************************
#define N_TOUCH 8
const int touch_pin[] = {
  18, 19, 22, 23,
  17, 16, 15, 1
};

const int notes[] = {
  52, 50, 58, 56, // E3, D3, A#3, G#3,
  49, 48, 54, 66, // C#3, C3, F#3, F#4,
  61, 67, 63, 65, // C#4, G#4, D#4, F4,
  60, 59, 57, 55,  // C4, B3, A3, G3
  85, 86, 83, 39, // C#6, D6, B5, D#2,
  68, 74, 75, 76, // G#4, D5, D#5, E5,
  77, 78, 88, 89, // F5, F#5, E6, F6,
  90, 81, 93, 92  // F#6, A5, A6, G#6
}; // which midi notes to send from the digital pins selected above

boolean on[] = {
  false, false, false, false,
  false, false, false, false,
};
// Touch Button end *********************************

// Potentiometers ***********************************
#define N_POT 3
const int pot_pin[] = {
  14, 20, 21
};

int value[] = {
  0, 0, 0
};
// Potentiometers end *******************************

int bank = 0; // 0 - 3

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  // Analog read resolution at 7-bit (0-127) like MIDI
  analogReadResolution(ANALOG_RES);
}

void loop() {
  // Touch Button
  for (int i = 0; i < N_TOUCH; i++) {
    if (touchRead(touch_pin[i]) > THRESHOLD) {
      if (!on[i]) {
        on[i] = true;
        sendNoteON(notes[N_TOUCH + i], velocity);
      }
    }
    else {
      if (on[i]) {
        on[i] = false;
        sendNoteOFF(notes[N_TOUCH + i]);
      }
    }
  }
  // Potentiometers
  for (int i = 0; i < N_POT; i++) {
    int readed = analogRead(pot_pin[i]);
    if (value[i] != readed) {
      value[i] = readed;
      switch (i) {
        case 0: // Potentiometer 0
          velocity = readed;
          break;
        case 1:// Potentiometer 1
          if (readed < 32) bank = 0;
          else if (readed >= 32 && readed < 64) bank = 1;
          else if (readed >= 64 && readed < 96) bank = 2;
          else if (readed >= 96 && readed < 128) bank = 3;
          // Aggiungere tutte note off
          for (int i = 0; i < N_TOUCH * 4; i++) {
            if (on[i]) {
              on[i] = false;
              sendNoteOFF(notes[i]);
            }
          }
          break;
        case 2: // Potentiometer 2
          // code
          break;
      }
    }
  }
  delayMicroseconds(DELAY);
}

void sendNoteON(int note, int velocity) {
#ifdef SERIAL
  Serial.print("note on :\t");
  Serial.print(note);
  Serial.print("\t");
  Serial.println(velocity);
#endif
#ifdef MIDI
  usbMIDI.sendNoteOn(note, velocity, CHANNEL);
#endif
}
void sendNoteOFF(int note) {
#ifdef SERIAL
  Serial.print("note off :\t");
  Serial.println(note);
#endif
#ifdef MIDI
  usbMIDI.sendNoteOff(note, 0, CHANNEL);
#endif
}
