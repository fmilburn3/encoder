# encoder


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
             
