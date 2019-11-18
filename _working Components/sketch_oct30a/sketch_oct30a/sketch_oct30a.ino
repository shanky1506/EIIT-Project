//CODING /*13 pin - D0, gnd - gnd, 5v to vcc, a0 to output of sensor*/ 
const int AOUTpin=0;
//the AOUT pin of the Moisture sensor goes into analog pin A0 of the arduino 
const int ledPin=13;
//the anode of the LED connects to digital pin D13 of the arduino 
int value; 
void setup() 
{ Serial.begin(9600);
//sets the baud rate 
pinMode(ledPin, OUTPUT);
//sets the pin as an output of the arduino 
pinMode(AOUTpin,INPUT); } 
void loop() 
{ value= analogRead(AOUTpin);
//reads the analaog value from the moisture sensor's AOUT 
Serial.print("Moisture value: "); 
Serial.println(value);
//prints the moisture value 
delay(1000); 
if (value<900)
//soil is dry pump will be on 
{ 
  digitalWrite(ledPin, LOW);
// led on = pump on 
}
else{ 
  digitalWrite(ledPin, HIGH);
// led off = pump off 
} }
