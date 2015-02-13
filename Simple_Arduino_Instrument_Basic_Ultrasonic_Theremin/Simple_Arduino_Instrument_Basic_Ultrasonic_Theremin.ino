/*
 * Simple_Arduino_Instrument_Basic_Ultrasonic_Theremin.ino
 * 
 * Author: Kevin Dela Rosa
 * 2015-02-12
 *
 * Simple Arduino Instruments
 * 
 * Basic Ultrasonic Theremin
 */

#include "Ultrasonic.h"

#define SPEAKER_PIN 8
#define ULTRASONIC_PIN 4

Ultrasonic ultrasonic(ULTRASONIC_PIN);

const int maximumRange = 60; // in centimeters

const float baseFrequency = 220;    // A3  
const float maxFrequency = 2093.00; // C7

float readingAdjustmentFactor;

// Make calculations used in determinig pitch and play some sample notes
void setup()
{
  readingAdjustmentFactor = (maxFrequency-baseFrequency)/maximumRange;
  
  // Play notes in range on load
  for(int i = 0; i <= maximumRange; i++){
    int pitch = baseFrequency + i*readingAdjustmentFactor;
    tone(SPEAKER_PIN, pitch);
    delay(20);
  }
  for(int i = maximumRange; i >= 0; i--){
    int pitch = baseFrequency + i*readingAdjustmentFactor;
    tone(SPEAKER_PIN, pitch);
    delay(15);
  }  
  noTone(SPEAKER_PIN);
}

// Main loop
void loop()
{
  long reading = ultrasonic.MeasureInCentimeters();

  if(reading <= maximumRange){
    int pitch = baseFrequency + reading*readingAdjustmentFactor;
    tone(SPEAKER_PIN, pitch);
  } else {
    noTone(SPEAKER_PIN);
  }

  delay(5); // For stability
}
