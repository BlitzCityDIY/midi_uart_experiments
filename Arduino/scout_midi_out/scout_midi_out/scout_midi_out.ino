#include "Frequency.h"
#include "KeyBuffer.h"
#include "Notes.h"
#include <MIDI.h> 


MIDI_CREATE_DEFAULT_INSTANCE();
// SETTINGS
int octave = 3;
int the_note;
bool empty = true;
int lastBuffer;
int newBuffer;
float glide = .25;
bool glideOnFreshKeyPresses = true;
bool printToSerial = false;

int midi_notes[] = {
  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
  0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40
};

const int CYCLES_PER_GLIDE_MAX = printToSerial ? 25 : 250;
const int STARTING_NOTE_DISTANCE_FROM_MIDDLE_A = -9;

const int SPEAKER_PIN = A0;

Notes notes(STARTING_NOTE_DISTANCE_FROM_MIDDLE_A);
KeyBuffer buffer;
Frequency frequency(glide, CYCLES_PER_GLIDE_MAX);

void blink(int count = 2, int wait = 200) {
  while (count >= 0) {
    digitalWrite(13, HIGH);
    delay(wait);
    digitalWrite(13, LOW);
    delay(wait);
    count = count - 1;
  }
}

void setup() {
  //Serial.begin(31250);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
//  MIDI.setHandleNoteOn(noteOn); 
  //MIDI.setHandleNoteOff(noteOff); 
  
  pinMode(13, OUTPUT);

  blink();
}

void loop() {
  
  //original scout program
  buffer.populate();

  if (printToSerial) {
    frequency.print();
  }

   if (buffer.isEmpty()){
      if (empty == true){
      MIDI.sendNoteOff(midi_notes[the_note], 0, 1);
      empty = false;
      lastBuffer = buffer.isEmpty();
      }
      digitalWrite(LED_BUILTIN, LOW);
      
  } else {

    the_note = buffer.getFirst();
    //newBuffer = the_note
    if (the_note != lastBuffer) {
    
      MIDI.sendNoteOn(midi_notes[the_note], 127, 1);
    }
    digitalWrite(LED_BUILTIN, HIGH);
    lastBuffer = the_note;
    empty = true;  
  }
   
} 
  
/*void noteOn(byte channel, byte pitch, byte velocity) { 
  digitalWrite(13,HIGH);
  for (int x = 0; x < NOTES_COUNT; x++)
  {
    if (midi_notes[x] == pitch)
    {
      frequency.update(notes.get(x) / 4 * pow(2, octave));
      tone(SPEAKER_PIN, frequency.get());
    }
  }
}

void noteOff(byte channel, byte pitch, byte velocity) { 
  frequency.reset();
  noTone(SPEAKER_PIN);
  digitalWrite(13,LOW);
}*/
