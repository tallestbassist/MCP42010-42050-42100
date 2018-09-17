/* 
Connection diagram on nano/uno (Mega and some others use different pins - always check you boards connections)

Pins:
MCP42***  <->   Arduino
1.  CS    <->  10. CS (can be assinged to any pin but mostly first one is used as pin 10 since its close to the others)
2.  SCK   <->  13. SCK
3.  SI    <->  11. MOSI
13. SO    <->  12. MISO  (not actually sure if this is needed for this chip)


NOTE: This is example how to control multiple digipots but i havent gotten it to work with multiple encoders.

By Kender Tasa 17.09.2018
*/
#include "SPI.h"   

#define outputA 3   // define encoder pin A
#define outputB 4   // define encoder pin B
#define led 6       // Currently in this code i set 1 led to show if i reached the minium value of "counter"
int counter = 0;    // This intiates the start up value of the counter. Change this value anywhere between 1-254 to start the MCP42*** at a different resistance value
int aState;
int aLastState;

byte address = 0xDF;    // Address line. currently set to 11011111. Check datasheet page 18. First two digits "11" are dummy's second to "01" tell it to write data. Then again two dummies. And last two digits "11" tell to write to both pots inside the chip.
int CS1= 10;            // the chip select pin. Set it low to write to it and set it high aftert you have finished sending the address and value.
// int CS2= 9;          // If you want more than one digipot to be controlled by your arduino trough SPI. Grayed out cause not it use at the moment. 


void setup() {
  pinMode (CS1, OUTPUT);
//  pinMode (CS2, OUTPUT);   // Grayed out cause not it use at the moment. 
  SPI.begin();              // For talking to the chip
  Serial.begin(9600);       // For if you want to see the encoder "counter" value in your serial monitor
  
  aLastState = digitalRead(outputA);
  pinMode(led, OUTPUT);
}

void loop() {

  aState = digitalRead(outputA);
  
  counter = constrain(counter, 1 , 254);  // Constrained the value of the counter so when you keep turning you wouldn't fo from Max value back to min value if you over turn. Also its 1-254 not 0-255 because my encoder would sometimes still make the resistor value jump over from min to max or max to min.
 

  if (aState != aLastState) {

    if (digitalRead(outputB) != aState) {
      counter ++;
      digitalWrite(CS1, LOW);         // if you have more then 1 chip just assing a new CS pin ( or uncomment the CS2 lines from above) and use these 4 lines of code to send the new value to the chip.
      SPI.transfer(address);          // This is the "byte address = 0xDF; " line
      SPI.transfer(counter);          // This is the value for the digipot but you can rename the counter to any other string or value you want to send to your digipot
      digitalWrite(CS1, HIGH);        // Always end with this so your chip communications dont mess up.
 
    }
    else {
      counter --;
      digitalWrite(CS1, LOW);
      SPI.transfer(address);
      SPI.transfer(counter);
      digitalWrite(CS1, HIGH);

    }

    if (counter <= 3) {
      digitalWrite(led, HIGH);     // this led just show if you have reached  the low point.  you can add code "if (counter >= 253) { }" do make it also light up when at the high end of the counter value"
      }
    else {
      digitalWrite(led, LOW);  // turns the led off if the statement isin't true.

    }

    Serial.print("Position: "); 
    Serial.println(counter);      // displays the counter value in serial monitor.
    aLastState = aState;


  }}
