#include <MIDI.h> 

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(31250);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(noteOn); 
  MIDI.setHandleNoteOff(noteOff); 
  
  pinMode(13, OUTPUT);

}

void loop() {
  MIDI.read();
} 
  
void noteOn(byte channel, byte pitch, byte velocity) { 
  digitalWrite(13,HIGH);
}

void noteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(13,LOW);
}
