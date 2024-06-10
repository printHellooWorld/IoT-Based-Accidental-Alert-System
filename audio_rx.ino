#include <TMRpcm.h>
#include <SPI.h>

TMRpcm audio;  // Create an audio object

const int rfReceiverPin = 2; // Pin connected to the RF receiver
const int audioTriggerPin = 3; // Pin to trigger the audio module
const int ledPin = 4; // Optional: LED pin to indicate signal reception

void setup() {
  pinMode(rfReceiverPin, INPUT); // RF receiver input
  pinMode(audioTriggerPin, OUTPUT); // Audio module trigger output
  pinMode(ledPin, OUTPUT); // LED output
  
  audio.speakerPin = 9; // Set the speaker pin for the audio module
  
  Serial.begin(9600); // Initialize Serial for debugging
  
  if (!SD.begin(SD_ChipSelectPin)) { // Initialize SD card
    Serial.println("SD fail");
    return;
  }
  audio.setVolume(6); // Set volume level (0 to 7)
}

void loop() {
  int rfSignal = digitalRead(rfReceiverPin); // Read the RF receiver signal
  
  if (rfSignal == HIGH) { // If signal received
    digitalWrite(ledPin, HIGH); // Turn on LED
    Serial.println("Signal received!");
    
    // Trigger audio playback
    audio.play("alert.wav"); // Replace with the name of your audio file on SD card
    delay(1000); // Wait for 1 second to avoid repeated triggering
    
    digitalWrite(ledPin, LOW); // Turn off LED
  } else {
    digitalWrite(ledPin, LOW); // Ensure LED is off if no signal
  }
  
  delay(100); // Short delay for stability
}