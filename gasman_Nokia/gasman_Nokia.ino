#include <NokiaLCD.h>
NokiaLCD NokiaLCD(8,9,10,12,11); // (SCK, MOSI, DC, RST, CS)

const int gasPin = A7;//GAS sensor output pin to Arduino analog A7 pin
int maxGas = 0;

void setup() {
  Serial.begin(9600); 
  NokiaLCD.init();   // Init screen.
  NokiaLCD.clear();  // Clear screen.
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  NokiaLCD.setCursor(15,1);
  NokiaLCD.print("LOADING");
  
  NokiaLCD.setCursor(10,2);
  NokiaLCD.print("PETOMETRE");
  
  NokiaLCD.setCursor(13,3);
  NokiaLCD.print("PARUFITO");

  NokiaLCD.setCursor(17,4);
  NokiaLCD.print("Start!");
  delay (10000);
  NokiaLCD.clear(); 
}

void loop() {
  int gasValue = analogRead(gasPin);
  if (maxGas > gasValue) {
    gasValue = maxGas;
  }
  else {
    maxGas = gasValue;
  }
  String stringOne = "";
  stringOne += gasValue;
  char charBuf[4];
  stringOne.toCharArray(charBuf, 4);

  NokiaLCD.setCursor(12,1);
  NokiaLCD.print("<PEDACO>");
  
  NokiaLCD.setCursor(30,3);
  NokiaLCD.print(charBuf);

  NokiaLCD.setCursor(12,4);
  NokiaLCD.print("--------");
  delay (500);
}
