/*
   Energia sketch for an encoder with push button that provides for coarse/fine adjustment.
   
   The button is coded to increase/decrease the coarseness that results from turning the encoder. 
   For example, the encoder can be set to increase or decrease the value by 100 with a turn
   of the knob. When the button is pushed it can be made to increase or decrease the value that 
   results from turning the knob. This allows the user to rapidly change values or achieve fine
   control as desired.
   
   Includes code and ideas from the following:
      - Encoder sketch by m3tr0g33k at playground.arduino.cc/Main/RotaryEncoders
   
   Connections
   There are 5 pins on the encoder.  On one side are 3 pins denoted here as 1, 2, and 3 that
   control the rotary encoder.  The two on the other side (pins 4 and 5) are the push button.   
   -------------------------------------------------------
   Encoder      MSP430 Pin
   Pin 1        3               // outside encoder pin
   Pin 2        GND             // middle encoder pin
   Pin 3        4               // outside encoder pin
   Pin 4        5               // push button
   Pin 5        GND             // push button
   
   Placing a 0.1 uF capacitor between the push button and ground; and 1 nF capacitors between
   the encoder pins and ground reduced bounce.
   
   Notes:  Connect encoder pins 1, 3, and 4 to microcontroller pins that accept external 
           interrupts Ports 1 and 2 generally have interrupt capability on the MSP430 series).
           If the encoder is turning the wrong way, swap pins or swap the pin definition below.

   Created by Frank Milburn    January 2015
   Tested on MSP-EXP430FR6989 and Energia V17
             EK-TM4123GXL and Energia V17
             MSP-EXP432P401R and Energia V17
             
*/

// pin assignments
const int buttonPin     = 11;               // connect the pushbutton to this LP pin
const int encoderPin1   = 13;               // connect one encoder pin to this LP pin
const int encoderPin2   = 12;               // connect the other encoder pin to this LP pin

// variables used to control program behavior
const long startVal     = 0;                // set this to whatever starting value is desired
const long minVal       = 0;                // minimum value that will be allowed as input
const long maxVal       = 40000000;         // maximum value that will be allowed as input
const long startInc     = 1000;             // values increase/decrease by this value to start
const long minInc       = 1;                // minimum increment/decrement allowed when turning
const long maxInc       = 1000000;          // maximum increment/decrement allowed when turning
const long divInc       = 10;               // factor for decreasing the increment for improved
                                            // control when the pushbutton is pushed
// variables used in ISRs
volatile long encoderVal = startVal;
volatile long encoderInc = startInc;
volatile boolean encoderLH1 = false;
volatile boolean encoderLH2 = false;

void setup() {
  Serial.begin (115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(encoderPin1, INPUT_PULLUP); 
  pinMode(encoderPin2, INPUT_PULLUP); 
  attachInterrupt(encoderPin1, ISR_Encoder1, CHANGE);  // interrupt for encoderPin1
  attachInterrupt(encoderPin2, ISR_Encoder2, CHANGE);  // interrupt for encoderPin2
  attachInterrupt(buttonPin, ISR_Button, FALLING);     // interrupt for encoder button
}

void loop(){ 
  // variables used to track whether or not a change has occurred
  static long lastEncoderVal = 1;                         
  static long lastEncoderInc = 0;
  
  // check for change in encoder
  if (lastEncoderVal != encoderVal) {
    if (encoderVal > maxVal) encoderVal = maxVal ;     // do not exceed max input value
    if (encoderVal < minVal) encoderVal = minVal;      // do not drop beneath min input value                
    Serial.print("Value: "); Serial.println(encoderVal, DEC);
    lastEncoderVal = encoderVal;
  }
  // check for change in button
  if (lastEncoderInc != encoderInc) {
    if (encoderInc < minInc) encoderInc = maxInc;      // if below min increment, set to max
    Serial.print("Inc/Dec: "); Serial.println(encoderInc, DEC);
    lastEncoderInc = encoderInc;
  } 
  delay(50);
}

void ISR_Button() {                                    
  encoderInc /= divInc;                                // change the increment amount
}

void ISR_Encoder1(){                                   
  // Low to High transition?
  if (digitalRead(encoderPin1) == HIGH) { 
    encoderLH1 = true;
    if (!encoderLH2) {
      encoderVal += encoderInc;                        // increase the value+
    }        
  }
  // High-to-low transition?
  if (digitalRead(encoderPin1) == LOW) {
    encoderLH1 = false;
  }
}

void ISR_Encoder2(){
  // Low-to-high transition?
  if (digitalRead(encoderPin2) == HIGH) {  
    encoderLH2 = true;
    if (!encoderLH1) {
      encoderVal -= encoderInc;                       // decrease the value
    }
  }
  // High-to-low transition?
  if (digitalRead(encoderPin2) == LOW) {
    encoderLH2 = false;
  }
}
