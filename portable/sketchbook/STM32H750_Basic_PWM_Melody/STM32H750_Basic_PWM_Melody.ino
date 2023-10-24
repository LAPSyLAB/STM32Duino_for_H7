/*
  Melody

  Plays a melody

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
*/

#include "pitches.h"

#define REST 1
// notes in the melody Lion sleeps tonight
int melody[] = {
  NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_A4,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_A4,
  NOTE_G4,
  NOTE_C5, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_C5,
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_A4,
  NOTE_G4,
  
  NOTE_C5,
  NOTE_C5, NOTE_AS4, NOTE_C5, NOTE_AS4,
  NOTE_A4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_C4,
  

};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 4, 4, 4,
  1,
  4, 4, 8, 4, 8,
  4, 4, 8, 4, 8,
  4, 4, 4, 4,
  1,
  
  1,
  4, 8, 8, 2,
  4, 8, 4, 8, 4,
  1,
  
};

const int num_elements_in_arr = sizeof(melody)/sizeof(melody[0]);

int i;
HardwareSerial Serial3(PB_11, PB_10);


      
void setup() {
        // put your setup code here, to run once:
        // initialize digital pins PI13,PJ2 as outputs.
        pinMode(PA_3, OUTPUT);

        pinMode(PD_12, OUTPUT);
        pinMode(PD_13, OUTPUT);

        Serial3.begin(115200); 

     
}

void loop() {
        // iterate over the notes of the melody:
        for (int thisNote = 0; thisNote < num_elements_in_arr; thisNote++) {
      
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / noteDurations[thisNote];
           
          analogWriteFrequency(melody[thisNote]); // Set PMW period to Note Hz
          
          analogWrite(PA_3, 128); // Start PWM on Pin, at melody[thisNote] Hz with 50% duty cycle
          analogWrite(PD_12, 128); // Start PWM on Pin, at melody[thisNote] Hz with 50% duty cycle
          analogWrite(PD_13, 128); // Start PWM on Pin, at melody[thisNote] Hz with 50% duty cycle
          // tone(8, melody[thisNote], noteDuration);

          
          Serial3.print("   Note (#");
          Serial3.print(thisNote);
          Serial3.print(") [Hz]:");
          Serial3.print(melody[thisNote]);
          Serial3.print("   Duration:");
          Serial3.println(noteDuration);
          
          delay(noteDuration);
      
          // stop the tone playing:
          analogWrite(PA_3, 0); // Start PWM on Pin, at melody[thisNote] Hz with 50% duty cycle
          analogWrite(PD_12, 0); // Start PWM on Pin, at melody[thisNote] Hz with 50% duty cycle
          analogWrite(PD_13, 0); // Start PWM on Pin, at melody[thisNote] Hz with 50% duty cycle

          // to distinguish the notes, set a minimum time between them.
          // the note's duration 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 0.3;
          delay(pauseBetweenNotes);
        }

    
        delay(1000);              // wait for a second
        
        i++;
         
        Serial3.print("End of Melody - ");
        Serial3.println(i);
        
      }


      
