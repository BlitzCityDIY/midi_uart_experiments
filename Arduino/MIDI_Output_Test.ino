#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  pinMode(13, OUTPUT);
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
  digitalWrite(13, HIGH);
  MIDI.sendNoteOn(60, 127, 1);
  delay(1000);		       
  MIDI.sendNoteOff(60, 0, 1);
  digitalWrite(13, LOW);
  delay(1000);

  digitalWrite(13, HIGH);
  MIDI.sendNoteOn(55, 127, 1);
  delay(1000);           
  MIDI.sendNoteOff(55, 0, 1);
  digitalWrite(13, LOW);
  delay(1000);
}
