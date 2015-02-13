/*
 * Simple_Arduino_Instrument_No_Breath_3_Key_Whistle.ino
 *
 * Author: Kevin Dela Rosa
 * 2015-02-12
 *
 * Simple Arduino Instruments
 * 
 * No Breath 3 Key Whistle
 */
 
#define SPEAKER_PIN 8
#define KEY1_PIN 2 // Top Key
#define KEY2_PIN 3 // Middle Key
#define KEY3_PIN 4 // Bottom Key

const int numTones = 7;
const char note[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};
const float baseFrequency[] = {523.25, 587.33, 659.25, 698.46, 783.99, 880.00, 987.77};

// Note:      C5 D5 E5 F5 G5 A5 B5      
// Note #:    0  1  2  3  4  5  6 
// Fingering: 0  4  6  2  3  1  5
const int fingerToNote[] = {0, 5, 3, 4, 1, 6, 2};

// Play sample tones and setup keys
void setup()
{
  // Play notes on load
  for (int i = 0; i < numTones; i++)
  {
    tone(SPEAKER_PIN, baseFrequency[i]);
    delay(200);
  }
  for (int i = numTones-1; i >= 0; i--)
  {
    tone(SPEAKER_PIN, baseFrequency[i]);
      delay(150);
  }  
  noTone(SPEAKER_PIN);
  
  // Setup keys and 'mouthpiece'
  pinMode(KEY1_PIN, INPUT);
  pinMode(KEY2_PIN, INPUT);
  pinMode(KEY3_PIN, INPUT);  
}

// Translates the fingering configuration to a note number
int readNoteNumber(){
   int fingering = !digitalRead(KEY1_PIN) + !digitalRead(KEY2_PIN)*2 + !digitalRead(KEY3_PIN)*2*2;
   return fingerToNote[fingering];
}

// Main loop
void loop()
{
  int noteNumber = readNoteNumber();
  
  if(noteNumber >=0 && noteNumber < numTones) {
      tone(SPEAKER_PIN, baseFrequency[noteNumber]); 
  } else {
      noTone(SPEAKER_PIN);
  }
  
  delay(5); // For stability
}
