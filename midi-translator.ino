/**
  MIDI Translator
  Name: midi-translator.ino
  Purpose: This is an Arduino based project for communication manipulation for MIDI messages..

  @author Bastian Bührig
  @version 0.1 02/14/18

  This proect uses this Arduino MIDILibrary: https://github.com/FortySevenEffects/arduino_midi_library
*/

#include <MIDI.h>

// This is the MIDI channel number for the listening MIDI-device.
static const int CHANNEL_MIDI_DEVICE = 1;

// Create a 'MIDI' object using MySettings bound to Serial1. On different Arduino-models you have
// to change the Serial
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial1, MIDI, midi::DefaultSettings);


/**
 * Setup your Arduino!
 */
void setup() {
  // MIDI listening to device channel
  MIDI.begin(CHANNEL_MIDI_DEVICE);
  // we don't won't to echo all incoming data without filtering or translating!
  MIDI.setThruFilterMode(midi::Thru::Off);
  // declare our MIDI-handlers.
  MIDI.setHandleControlChange(handlerControlChange);
  MIDI.setHandleProgramChange(handlerProgramChange);

  // Monitoring activities on standard Serial Monitor
  Serial.begin(9600);
  Serial.println("MIDI Translator v0.1");
  Serial.println("----------------------");
}


/**
 * Start reading MIDI-Inputs...
 */
void loop() {
  MIDI.read();
}


/**
 * Handle all incoming ControlChange messages. We want to echo all incoming
 * ControlChange message only. This is for expression pedals! 
 * 
 * @param channel MIDI channel for incoming MIDI ControlChange message
 * @param number  number of controller that was received
 * @param value   value of invcoming ControlChange message. Possible values: 0-127
 */
void handlerControlChange(byte channel, byte number, byte value) {
  // Log all incoming ControlChange messages...
  char logstring[70];
  sprintf (logstring, "ControlChange received! CH #%02u  CC #%03u  VAL #%03u", channel, number, value);
  Serial.println(logstring);
  // ...and send them back to MIDI-Out without translating or filtering!
  MIDI.sendControlChange(number, value, channel);
}


/**
 * Handle all incoming ProgramChange messages. There is a translation implemented. For
 * all different ProgramChange numbers it is possibility to send any MIDI-message out
 * to your MIDI-device. Here we react to ProgramChange 0 - 4. It will be translated to
 * ControlChange-message on controler number 34. It sends value 0 - 4. ControlChange 34
 * is the default ControlChange number for scene-switching in Fractal Audio Axe-FX II.
 * 
 * @param channel MIDI channel for incoming MIDI ProgramChange message. 
 * @param number  Incoming program-number.
 */
void handlerProgramChange(byte channel, byte number) {
  // Log all incoming ProgramChange messages...
  char logstring[70];
  sprintf (logstring, "ProgramChange received! CH #%02u  PC #%03u received!", channel, number);
  Serial.println(logstring);

  // Do the translation-stuff...
  if (number == 0) {
    // Switch to scene 1
    Serial.println("Switch to Axe-FX Scene 1");
    MIDI.sendControlChange(34, 0, CHANNEL_MIDI_DEVICE);
    
  } else if (number == 1) {
    // Switch to scene 2
    Serial.println("Switch to Axe-FX Scene 2");
    MIDI.sendControlChange(34, 1, CHANNEL_MIDI_DEVICE);
    
  }  else if (number == 2) {
    // Switch to scene 3
    Serial.println("Switch to Axe-FX Scene 3");
    MIDI.sendControlChange(34, 2, CHANNEL_MIDI_DEVICE);
    
  }  else if (number == 3) {
    // Switch to scene 4
    Serial.println("Switch to Axe-FX Scene 4");
    MIDI.sendControlChange(34, 3, CHANNEL_MIDI_DEVICE);
    
  }  else if (number == 4) {
    // Switch to scene 5
    Serial.println("Switch to Axe-FX Scene 5");
    MIDI.sendControlChange(34, 4, CHANNEL_MIDI_DEVICE);
    
  } else {
    // All other ProgramChange messages will be echoed to MIDI-Out. 
    MIDI.sendProgramChange(number, CHANNEL_MIDI_DEVICE);
  }
}

