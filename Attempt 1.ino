/* Grumpy Cat

By applying pressure to the cat's back, the cat will react positively or negatively.

Force Sensitive Resistor (Pressure Sensor) connected to A0
Two RED LEDs connected to D13
Servo connected to D7
Speaker connected to D9
*/
#include <Servo.h> //Include Servo Library
#include <TMRpcm.h> //Include Sound Library
#include <SD.h> //Include SD Card
#include <SPI.h>
#define SD_ChipSelectPin 4 //Using Digital Pin 4 - SD Card Shield

Servo myservo; // create servo object to control a servo
TMRpcm tmrpcm;

int pos = 30; // variable to store the servo position
const int ledPin = 13; // the number of the LED pin
int ledState = LOW; // ledState used to set the LED
int fsrPin = 0; // the FSR and 10K pulldown are connected to a0
int fsrReading; // the analog reading from the FSR resistor divider

void setup(void) {
// We'll send debugging information via the Serial monitor
Serial.begin(9600);

myservo.attach(7); // attaches the servo on pin 7 to the servo object

pinMode(ledPin, OUTPUT);

//SD Card + Speaker Setup
tmrpcm.speakerPin = 9; //Pin 9 on Uno
SD.begin(SD_ChipSelectPin);
}

void loop(void) {
fsrReading = analogRead(fsrPin);

Serial.print("Analog reading = ");
Serial.print(fsrReading); // the raw analog reading

if (fsrReading < 50) {
Serial.println(" - No pressure");
digitalWrite(ledPin, HIGH);

for (pos = 0; pos <= 180; pos += 1) // goes from 30 degrees to 150 degrees
{ // in steps of 1 degree
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position
}
for (pos = 180; pos >= 0; pos -= 1) // goes from 150 degrees to 30 degrees
{
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits for the servo to reach the position
}
}

else if (fsrReading < 100) {
Serial.println(" - Perfect Pressure");
tmrpcm.play("m.wav"); //this sound file tone will play each time the arduino powers up, or is reset to check function

for (pos = 30; pos <= 150; pos += 3) // goes from 30 degrees to 150 degrees
{ // in steps of 1 degree
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position
}
for (pos = 150; pos >= 30; pos -= 3) // goes from 150 degrees to 30 degrees
{
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits for the servo to reach the position
}
}

else if (fsrReading > 100) {
Serial.println(" TOO MUCH");
digitalWrite(ledPin, HIGH);
tmrpcm.play("gn.wav"); //this sound file tone will play each time the arduino powers up, or is reset to check function
for (pos = 75 ; pos <= 105; pos += 5) // goes from 75 degrees to 105 degrees
{ // in steps of 1 degree
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits 15ms for the servo to reach the position
}
for (pos = 105; pos >= 75; pos -= 5) // goes from 150 degrees to 30 degrees
{
myservo.write(pos); // tell servo to go to position in variable 'pos'
delay(15); // waits for the servo to reach the position
}
}
delay(500);
}
