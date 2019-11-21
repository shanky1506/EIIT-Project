#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>


/*---------------Global Scope--------------------------*/

Servo servo1;  // create servo instance to control a servo
int pos = 0;    // variable to store the servo position
long distance;
float temp1;
int margin1 = 15; // Sensor 1 - Margin
int state =1;
long duration1,cm1,gcm1;
int a=0;


/*--------------------------Pin Connections-----------*/
#define TEMP_PIN 8        // Temp Sensor Pin
#define TRIG_PIN_1 7      // Trigger Pin of Ultrasonic Sensor 1
#define ECHO_PIN_1 6      // Echo Pin of Ultrasonic Sensor 1
#define SERVOMD_PIN 13    // Servo Pin

/*--------LCD PINS---*/
#define LCD_PIN_RS  12
#define LCD_PIN_E  11
#define LCD_PIN_DB4 5
#define LCD_PIN_DB5 4
#define LCD_PIN_DB6 3
#define LCD_PIN_DB7 2

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
    sensors.begin();   // Start up the library
/*----------------------LCD beginning------------------------------------- */
    lcd.begin(16, 2); // set up the LCD's number of columns and rows:
    lcd.print("Arduino Tutorial"); //// Print a message to the LCD.
}

/*----------------------Main LOOP---------------------------------------------------------------*/
void loop() {

/*------------------------- Distance Sensor 1 --------------------------*/
   pinMode(TRIG_PIN_1, OUTPUT);
   digitalWrite(TRIG_PIN_1, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIG_PIN_1, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN_1, LOW);
   pinMode(ECHO_PIN_1, INPUT);

   duration1 = pulseIn(ECHO_PIN_1, HIGH);
   gcm1 = microsecondsToCentimeters(duration1);
   Serial.print(gcm1);
   Serial.print("cm1");
   Serial.println();
   if(gcm1 < 500 || gcm1 != 0)  // For filtering the Junk values
   {
     cm1 = gcm1;
   }

/*-------------------------Temperature sensor-----------------------------------*/
   
   sensors.requestTemperatures(); // Send the command to get temperatures

   Serial.print("Temperature is: ");
   temp1 = sensors.getTempCByIndex(0); 
   Serial.print(temp1);

   

lcd.clear();
lcd.setCursor(1,1);
lcd.print(temp1);
  

  /*------------------Finite State Machine ---------------------*/  
  Serial.println(state);
  switch (state)
    {
     case 1: /* IDLE State with tap Closed */

          tapClose(servo1);
          if(cm1 > margin1)
          {
            a =0;
          }
          if(cm1<margin1 && cm1 != 0) //An object is present
          {
            a++;
          }
          if(a == 3)
          {
            state = 2 ;
          }
          lcd.setCursor(1,0);
          lcd.print("STAY HYDRATED");
                             
          break;

    case 2: /* Tap opening */

          tapOpen(servo1);
          a = 0;
          state = 3;
          // s2i = cm2; // Taking the initial reading
          lcd.setCursor(1,0);
          lcd.print("Tap opening");
     
          break;    
    case 3: /* IDLE Tap open  */

          if(cm1 > margin1)  // No Object is Placed at the Station
          {
            state = 4;
          }
          lcd.setCursor(1,0);
          lcd.print("Hold Still");      
         break;

    case 4: /* Tap Closing */
          lcd.setCursor(1,0);
          lcd.print("Tap Closing ");
          
          tapClose(servo1);
          state = 1;
          break;
    }


 delay(500);
}
