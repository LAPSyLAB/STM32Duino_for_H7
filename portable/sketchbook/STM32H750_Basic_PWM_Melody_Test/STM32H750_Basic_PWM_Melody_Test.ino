/*
  Melody

  Plays a melody

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
*/

#include "pitches.h"
 int duty = 128;
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 0, 4, 4
};

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
        for (int thisNote = 0; thisNote < 8; thisNote++) {
      
          // to calculate the note duration, take one second divided by the note type.
          //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
          int noteDuration = 1000 / noteDurations[thisNote];
           
          analogWriteFrequency(melody[thisNote]); // Set PMW period to Note Hz
 
          if (noteDurations[thisNote] == 0 ) {
               duty = 0;
          } else {
               duty=128;
          }
          
          analogWrite(PA_3, duty); // Start PWM on PA3, at melody[thisNote] Hz with 50% duty cycle
          
          analogWrite(PD_12, duty); // Start PWM on PA3, at melody[thisNote] Hz with 50% duty cycle
          analogWrite(PD_13, duty); // Start PWM on PA3, at melody[thisNote] Hz with 50% duty cycle

          
          // tone(8, melody[thisNote], noteDuration);
          Serial3.print("   Note [Hz]:");
          Serial3.println(melody[thisNote]);
          
          delay(1000);
          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          //delay(500);

        }


        Serial3.print("End of Melody - ");
        Serial3.println(i++);
        delay(500);

        
}
