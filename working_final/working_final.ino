#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>


/*---------------Global Scope--------------------------*/

Servo servo1;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
long distance;
int temp1;
int margin1 = 10; // Sensor 1 - Margin
int dbtwsens = 5 ;
int margin2 = 15;
int state;
int s2i,s2f;
long duration1,duration2, inches, cm1,cm2;


/*--------------------------Pin Connections-----------*/
#define TEMP_PIN 2 // Temp Sensor Pin
#define TRIG_PIN_1 4 // Trigger Pin of Ultrasonic Sensor 1
#define ECHO_PIN_1 3 // Echo Pin of Ultrasonic Sensor 1
#define TRIG_PIN_2 4 // Trigger Pin of Ultrasonic Sensor 1
#define ECHO_PIN_2 3 // Echo Pin of Ultrasonic Sensor 1
#define SERVOMD_PIN 13 //Servo Pin

/*--------LCD PINS---*/
#define LCD_PIN_RS  12
#define LCD_PIN_E 11
#define LCD_PIN_DB4 7
#define LCD_PIN_DB5 8
#define LCD_PIN_DB6 9
#define LCD_PIN_DB7 10
/* LCD */
LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_E, LCD_PIN_DB4, LCD_PIN_DB5, LCD_PIN_DB6, LCD_PIN_DB7);
/* Temp Sensor Fixing */
OneWire oneWire1(TEMP_PIN); // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire1); // Pass our oneWire reference to Dallas Temperature.

/*---------------------------Functions--------------------------*/
long microsecondsToCentimeters(long microseconds) //for Distance sensor
{
   return microseconds / 29 / 2;
}

Servo tapOpen(Servo servo)
{
  pos = 90;
  servo.write(pos);      // tell servo to go to position in variable 'pos'

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
   servo1.attach(SERVOMD_PIN);

/* -----------Temp Sensor Beginning --------------------*/
   // Serial.println("Dallas Temperature IC Control Library Demo");
   sensors.begin();   // Start up the library
/*----------------------LCD beginning------------------------------------- */
    lcd.begin(16, 2); // set up the LCD's number of columns and rows:
    lcd.print("Arduino Tutorial"); //// Print a message to the LCD.
}

/*----------------------LOOP----------------------------*/
void loop() {

/*------------------------- Distance Sensor 1 --------------------------*/
   pinMode(TRIG_PIN, OUTPUT);
   digitalWrite(TRIG_PIN, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);
   pinMode(ECHO_PIN, INPUT);

   duration1 = pulseIn(ECHO_PIN, HIGH);
   cm1 = microsecondsToCentimeters(duration1);
   // Serial.print(cm1);
   // Serial.print("cm");
   // Serial.println();

/*------------------------- Distance Sensor 2 --------------------------*/
  pinMode(TRIG_PIN_2, OUTPUT);
   digitalWrite(TRIG_PIN_2, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN_2, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN_2, LOW);
   pinMode(ECHO_PIN_2, INPUT);
   duration2 = pulseIn(ECHO_PIN, HIGH);
   cm2 = microsecondsToCentimeters(duration2);
   // Serial.print(cm2);
   // Serial.print("cm");
   // Serial.println();
   delay(100);

/*-------------------------Temperature sensor-----------------------------------*/
   //Serial.print(" Requesting temperatures...");
   sensors.requestTemperatures(); // Send the command to get temperatures
   //Serial.println("DONE");

   //Serial.print("Temperature is: ");
   temp1 = sensors.getTempCByIndex(0); // You can have more than one IC on the same bus.
   // 0 refers to the first IC on the wire
   //Serial.println();
   //Serial.print(temp1); // Why "byIndex"?

  switch (state)
    {
    case 1: /* IDLE State with tap Closed */
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
    case 2: /* Tap opening */
          tapOpen(servo1);
          state = 3;
          s2i = cm2; // Taking the initial reading
          break;
    case 3: /* IDLE Tap open  */

          if(cm1 > margin1)  // No Object is Placed at the Station
          {
            state = 4;
          }
          if(cm2 < dbtwsens) // Extra 5 is for lag
          {
            state = 4;
          }
          // if(time > long_time)
          // {
          //   state =4;
          // }
          break;
    case 4: /* Tap Closing */
          s2f = cm2 ;
          tapClose(servo1);
          state =1;
          break;
    }


    delay(1000);
    /*-------------------------LCD Display-----------------------------------*/
      lcd.setCursor(0, 1);
}
