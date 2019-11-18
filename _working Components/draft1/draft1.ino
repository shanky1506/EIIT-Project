#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
long distance;

const int pingPin = 6; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 7; // Echo Pin of Ultrasonic Sensor

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   myservo.attach(9);
}
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void loop() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);


   
   duration = pulseIn(echoPin, HIGH);
   // inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
  // Serial.print(inches);
  // Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(100);   


if(cm<15){
    // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(90);              // tell servo to go to position in variable 'pos'
    //delay(100);
    // waits 15ms for the servo to reach the position
  
}
if(cm>15){
    // goes from 180 degrees to 0 degrees
    myservo.write(0);              // tell servo to go to position in variable 'pos'
    //delay(100);                       // waits 15ms for the servo to reach the position
  
}
delay(1000);

}
