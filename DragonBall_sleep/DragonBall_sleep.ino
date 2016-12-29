#include "LowPower.h"

//Setup Pins RGB led
int Rojo = 9;
int Verde = 10;
int Azul = 11;
//Pin Interruption PIR sensor
const int PIRPin= 2;

//Setup pins
void setup(){
  
 pinMode(Rojo, OUTPUT);
 pinMode(Verde, OUTPUT);
 pinMode(Azul, OUTPUT); 
 pinMode(PIRPin, INPUT);

}

//Function to set Led colour
void EstablecerColor(int R, int G, int B){
  
 analogWrite(Rojo, 255-R);
 analogWrite(Verde, 255-G);
 analogWrite(Azul, 255-B); 

}

//Glow effect, function 
void GlowEffect (){
    for (int i=0; i <= 255; i++){
     EstablecerColor(i,i,i);
     //delay in microseconds because delay() or millis() are not allowed inside an interruption
     delayMicroseconds(10000);
    }
    for (int i=255; i >= 0; i--){
     EstablecerColor(i,i,i);
     delayMicroseconds(8000);
    }
}

void loop(){
    EstablecerColor(0,0,0);
    // Allow wake up pin to trigger interrupt on RISING value (from LOW to HIGH). and launch function GlowEffect
    attachInterrupt(0, GlowEffect, RISING);
    
    // Enter power down state with ADC and BOD module disabled.
    // Wake up when wake up pin is low.
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
}
