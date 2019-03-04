
/**
 * @file
 * @author Tyson Dennis-Sharma
 */
 
#include <Wire.h>
/**------------Left Colour Sensor Pre Setup Code------*/
// TCS230 or TCS3200 pins wiring to Arduino
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;
// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int left_empty=1;

/**------------Right Colour Sensor Pre Setup Code------*/
// TCS230 or TCS3200 pins wiring to Arduino
#define S4 7
#define S5 8
#define S6 9
#define S7 10
#define sOUT 11
int right_empty=1;

/**--------------Left Ultrasonic Sensor Pre Setup Code-----*/
const int pingPin = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 13; // Echo Pin of Ultrasonic Sensor

/**--------------Right Ultrasonic Sensor Pre Setup Code----*/
const int ping = 14; // Trigger Pin of Ultrasonic Sensor
const int echo = 15; // Echo Pin of Ultrasonic Sensor


/**----------------Both Ultrasonic Sensors Pre Setup Code-----*/
const int comPin=16; //communication pin

/**---------------------Pre I2C Setup Code-----------------*/
volatile unsigned char outputchar='0';

void setup(){

  /** -----------I2C setup code---------------*/
    Wire.begin(8); // Join I2C bus with address 8
  
    // Register callback functions
    Wire.onReceive(receiveEvent); // Called when this slave device receives a data transmission from master
    Wire.onRequest(requestEvent); // Called when master requests data from this slave device
  
    // Open serial port to PC (hardware UART)
    Serial.begin(9600); 
         
  /** -------------Left Colour Sensor Setup Code------*/
    // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
   //Serial.begin(9600); //this sets the data rate
  /**---------------------Right Colour Sensor Setup Code-----*/
   // Setting the outputs
  pinMode(S4, OUTPUT);
  pinMode(S5, OUTPUT);
  pinMode(S6, OUTPUT);
  pinMode(S7, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sOUT, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S4,HIGH);
  digitalWrite(S5,LOW);
  
   // Begins serial communication 
  
  //Serial.begin(9600); //this sets the data rate

  /**-----------------------Both Ultrasonic Sensors Setup Code--------*/
  //Serial.begin(9600); // Starting Serial Terminal
  
}
/**-----------------I2C  Intermediary Code-----------*/
volatile bool send_to_pic = false;
volatile uint8_t incomingByte;

void loop(){

  pinMode(comPin, OUTPUT);
/**------------------Left Colour Sensor Loop Code-------- */
// Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // redColor = map(redFrequency, 70, 120, 255,0);
  redColor = map(redFrequency, 20, 70, 255,0);
  
  // Printing the RED (R) value
  //Serial.print("R = ");
  //Serial.print(redColor);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  greenColor = map(greenFrequency, 50, 100, 255, 0);
  
  // Printing the GREEN (G) value  
  //Serial.print(" G = ");
  //Serial.print(greenColor);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  blueColor = map(blueFrequency, 5, 110, 255, 0);

  // Printing the BLUE (B) value 
  //Serial.print(" B = ");
  //Serial.print(blueColor);
  delay(100);
  
  // Checks the current detected color and prints
  // a message in the serial monitor
  if(redColor > greenColor && redColor > blueColor){
      //Serial.print(" - RED detected!");
  }
  if(greenColor > redColor && greenColor > blueColor){
    //Serial.print(" - GREEN detected!");
  }
  if(blueColor > redColor && blueColor > greenColor){
    //Serial.print(" - BLUE detected!");
  }
  if (redColor<-600 && blueColor<-1000 && greenColor>50){left_empty=0; }
  //Note to self: You will need to do more work in order to actually determine these parameters
  else{left_empty=1; }

/**-------------------Right Colour Sensor Loop Code----- */
 // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S6,LOW);
  digitalWrite(S7,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sOUT, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // redColor = map(redFrequency, 70, 120, 255,0);
  redColor = map(redFrequency, 20, 70, 255,0);
  
  // Printing the RED (R) value
  //Serial.print("R = ");
  //Serial.print(redColor);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S6,HIGH);
  digitalWrite(S7,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sOUT, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  greenColor = map(greenFrequency, 50, 100, 255, 0);
  
  // Printing the GREEN (G) value  
  //Serial.print(" G = ");
  //Serial.print(greenColor);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S6,LOW);
  digitalWrite(S7,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sOUT, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  // You must replace with your own values. Here's an example: 
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  blueColor = map(blueFrequency, 5, 110, 255, 0);
  
  // Printing the BLUE (B) value 
  //Serial.print(" B = ");
  //Serial.print(blueColor);
  delay(100);
  
  // Checks the current detected color and prints
  // a message in the serial monitor
  if(redColor > greenColor && redColor > blueColor){
      //Serial.print(" - RED detected!");
  }
  if(greenColor > redColor && greenColor > blueColor){
    //Serial.print(" - GREEN detected!");
  }
  if(blueColor > redColor && blueColor > greenColor){
    //Serial.print(" - BLUE detected!");
  }
  if (redColor<-600 && blueColor<-1000 && greenColor>50){right_empty=0;}
  //Note to self: You will need to do more work in order to actually determine these parameters
  else{
    right_empty=1;}
  



/**-------------------Left Ultrasonic Sensor Loop Code---*/

   int i=0;
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
  // Serial.print(inches);
  //Serial.print("in, ");
  // Serial.print(cm);
  // Serial.print("cm");
  // Serial.println();
   delay(100);
   if (3<cm<22){
      i=i+1;}
   else {
      i=0; }
   if (i==6){
     // Serial.print("Canister, LEFT");
     if (right_empty==1){
       outputchar='1';
       //Serial.print("1");
    }
    else{
      outputchar='0';
      //Serial.print("0");
    }
    i=0;}
   /** Determine this more carefully later */    


/**-------------------Right Ultrasonic Sensor Loop Code--*/
 i=0;
 pinMode(ping, OUTPUT);
 digitalWrite(ping, LOW);
 delayMicroseconds(2);
 digitalWrite(ping, HIGH);
 delayMicroseconds(10);
 digitalWrite(ping, LOW);
 pinMode(echo, INPUT);
 duration = pulseIn(echo, HIGH);
 inches = microsecondsToInches(duration);
 cm = microsecondsToCentimeters(duration);
  // Serial.print(inches);
  //Serial.print("in, ");
  // Serial.print(cm);
  // Serial.print("cm");
  // Serial.println();
 delay(100);
 if (3<cm<22){
    i=i+1;}
 else {
    i=0; }
 if (i==6){
    //Serial.print("Canister, RIGHT");
    digitalWrite(comPin,HIGH);
    if (right_empty==1){
       outputchar='2';
       //Serial.print("2");
    }
    else{
      outputchar='0';
      //Serial.print("0");
    }
    i=0;}
   /** Determine this more carefully later */   

/**------------------I2C Loop Code------------------*/  
    // If we should send to the PIC, then we wait to receive a byte from the PC
    if (!incomingByte){
       incomingByte=outputchar;
    }
  /*previous version  if (send_to_pic && Serial.available() > 0 && !incomingByte) {
        incomingByte = Serial.read();
    } */


}

/*-------------------I2C Functions Code--------------*/

/** @brief Callback for when the master transmits data */
void receiveEvent(int){
     /** Akino said hers only works with void receiveEvent(int) so try this if you need */
     /**The previous version had (void) but gave a warning */
     
    static uint8_t buf[3] = {0};
    static uint8_t counter = 0;
    
    uint8_t x = Wire.read(); // Receive byte
    Serial.println((char)x); // Print to serial output as char (ASCII representation)
    digitalWrite(comPin,LOW);
    delay(700);
    
    /*
    buf[counter++] = x;
    counter = (counter == 3) ? 0 : counter;
    
    if(buf[0]=='A' && buf[1]=='A' && buf[2]=='A'){
        send_to_pic = true;
    } */
}

/** @brief Callback for when the master requests data */
void requestEvent(void){
    Wire.write(incomingByte); // Respond with message of 1 byte
    incomingByte = 0; // Clear output buffer
}

/**-----------------------------Ultrasonic Sensors Functions----------------*/

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
