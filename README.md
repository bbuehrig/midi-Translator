# MIDI-Translator
This is an Arduino based project for communication manipulation for MIDI messages. The idea was born as a simple translator for MIDI messages sent by a simple MIDI foot-controller to a MIDI device like an FX-processor. I need it for translating ProgramChange messages to ControlChange messages sent by a Boss FC50 MIDI foot-controller. The ControlChange messages were sent towards an Fractal Audio Axe-FX II for controlling the scene switching.

Fell free to improve and adapt it for your own MIDI tool!


## Requirements
This tool was tested in live band situations on an Arduino UNO. It will ne working on all other Arduinos too.

For the MIDI-Communication you need two MIDI-Ports: MIDI-In and MIDI-Out. I tested it with Sparkfun MIDI-Shield that is stacked on top of the Arduino.

You have to install the Arduino MIDI-Library by FourtySevenEffects . You will find it on GitHub here: https://github.com/FortySevenEffects/arduino_midi_library!

That's all! :)


