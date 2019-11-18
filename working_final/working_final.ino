#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/*---------------Global Scope--------------------------*/

Servo servo1;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
long distance;
int temp1;
int margin1 = 10; // Sensor 1 - Margin
int dbtwsens = 5 ;
int state;
int s2i,s2f;


/*--------------------------Pin Connections-----------*/
#define TEMP_PIN 2 // Temp Sensor Pin
#define TRIG_PIN_1 4 // Trigger Pin of Ultrasonic Sensor 1
#define ECHO_PIN_1 3 // Echo Pin of Ultrasonic Sensor 1
#define TRIG_PIN_2 4 // Trigger Pin of Ultrasonic Sensor 1
#define ECHO_PIN_2 3 // Echo Pin of Ultrasonic Sensor 1
#define SERVOMD_PIN_SIG 13 //Servo Pin

/*--------LCD PINS---*/
#define LCD_PIN_RS  12
#define LCD_PIN_E 11
#define LCD_PIN_DB4 7
#define LCD_PIN_DB5 8
#define LCD_PIN_DB6 9
#define LCD_PIN_DB7 10

OneWire oneWire(TEMP_PIN); // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature.

/*---------------------------Functions--------------------------*/
long microsecondsToCentimeters(long microseconds) //for Distance sensor
{
   return microseconds / 29 / 2;
}

Servo tapOpen(Servo servo)
{
  pos = 90;
  servo.write(90);      // tell servo to go to position in variable 'pos'

}
Servo tapClose(Servo servo)
{
  pos = 0;
  servo.write(pos);     // tell servo to go to position in variable 'pos'
}
/*-------------Intial Setup-------------------------*/
void setup()
{
// Starting Serial Terminal Giving a Baudrate of 9600
   Serial.begin(9600);
//Servo Motor Beginning
   servo1.attach(SERVOMD_PIN_SIG);

/* -----------Temp Sensor Beginning --------------------*/
   // Serial.println("Dallas Temperature IC Control Library Demo");
   sensors.begin();   // Start up the library
/*LCD beginning */

}

/*----------------------LOOP----------------------------*/
void loop() {

//
   long duration1,duration2, inches, cm1,cm2;
   pinMode(TRIG_PIN, OUTPUT);
   digitalWrite(TRIG_PIN, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);
   pinMode(ECHO_PIN, INPUT);

   duration1 = pulseIn(ECHO_PIN, HIGH);
   cm1 = microsecondsToCentimeters(duration1);

    pinMode(TRIG_PIN, OUTPUT);
   digitalWrite(TRIG_PIN, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);
   pinMode(ECHO_PIN, INPUT);

   Serial.print(cm1);
   Serial.print("cm");
   Serial.println();
   delay(100);

  switch state
    {
    case 1:
          if(cm1<margin1) //An object is present
          {
          delay(1000);
            if(cm1 <margin1)
            {
              delay(1000);
              if(cm1 < margin1)
              {
                state = 2;
              }
            }
          }

          break;
    case 2:
          tapOpen(servo1);
          state = 3;
          s2i = cm2;
          break;
    case 3:

          if(cm1>margin1)  // No bject is Placed at the Station
          {
            state = 4;
          }
          if(cm2 <  dbtwsens) // Extra 5 is for lag
          {
            state = 4;
          }
          if(time > long_time)
          {
            state =4;
          }
          break;
    case 4:
          tapClose(servo1);
          state =1;
          break;
    }






// delay(1000);
// Automatic Closing

else if(cm2 > margin2 )
{

}


  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Temperature is: ");
  temp1 = sensors.getTempCByIndex(0); // You can have more than one IC on the same bus.
  // 0 refers to the first IC on the wire
  Serial.println();
  Serial.print(temp1); // Why "byIndex"?

    delay(1000);
}
