/* Grumpy Cat

  By applying pressure to the cat's back, the cat will react positively or negatively.

  Force Sensitive Resistor (Pressure Sensor) connected to A0
  Two RED LEDs connected to D13
  Servo/tail connected to D7
*/
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

//Servo counter variables
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;        // will store last time servo moved
const long interval = 15;
int tailState = LOW;

//Servo Positions Variables
int pos = 0;    // variable to store the servo position for tailSLOW
int pos1 = 45;  //variable to store servo position for tailMED
int pos2 = 75;  //variable to store servo position for tailFAST
float a = 7.5; //created so that pos2 could move by 7.5 degrees

//Variables
const int ledPin =  13;      // the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider

void setup() {
  // debugging information via the Serial monitor
  Serial.begin(9600);

  myservo.attach(7);  // attaches the servo on pin 7 to the servo object

  pinMode(ledPin, OUTPUT);
}

void loop() {
  fsrReading = analogRead(fsrPin);
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // the raw analog reading

  if (fsrReading < 100) {
    Serial.println(" - No pressure");
    ledOFF();
    tailSLOW(); //call upon slow tail movement
  }
  else if (fsrReading > 100 && fsrReading < 200) {
    Serial.println(" - Perfect Pressure");
    ledOFF(); //call upon ledOFF function
    tailMED();
  }
  else if (fsrReading >= 200) {
    Serial.println(" - TOO MUCH");
    ledON();
    tailFAST();
  }
}

void ledON() {
  digitalWrite(ledPin, HIGH);
}

void ledOFF() {
  digitalWrite(ledPin, LOW);
}

void tailSLOW() {       //full 180 degree movement indicating the cat is waiting
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  }
  if (tailState == LOW) {
    pos++; // go up in position
  } else {
    pos--; // go down
  }
  // if pos goes above 180 switch to low if lower than 0 switch to high
  if (pos > 180) {
    tailState = HIGH;
  } else if (pos < 1) {
    tailState = LOW;
  }
  myservo.write(pos);              // tell servo to go to position in variable 'pos=0'
}

void tailMED() {      //faster movement between 45 and 135 degrees indicating a happy cat
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  }
  if (tailState == LOW) {
    pos1 = pos1 + 5; // go up in position
  } else {
    pos1 = pos1 - 5; // go down
  }
  // if pos goes above 135 switch to low if lower than 45 switch to high
  if (pos1 > 135) {
    tailState = HIGH;
  } else if (pos1 < 45) {
    tailState = LOW;
  }
  myservo.write(pos1);              // tell servo to go to position in variable 'pos1=45'
}

void tailFAST() {           //fastest movement between 75 and 105 degrees indicating the cat is angry
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  }
  if (tailState == LOW) {
    pos2 = pos2 + a; // go up in position
  } else {
    pos2 = pos2 - a; // go down
  }
  // if pos goes above 105 switch to low if lower than 75 switch to high
  if (pos2 > 105) {
    tailState = HIGH;
  } else if (pos2 < 75) {
    tailState = LOW;
  }
  myservo.write(pos2);              // tell servo to go to position in variable 'pos2=75'
}
