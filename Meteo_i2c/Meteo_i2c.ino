//Includes LCD - i2c - temp.
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

//1602 i2c
#define I2C_ADDR    0x27
LiquidCrystal_I2C             lcd(I2C_ADDR,2, 1, 0, 4, 5, 6, 7);

//Temperatura
#define DHTPIN 4 //Conectamos el Sensor al pin digital 4
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

//Boto led
const int buttonPin = 5;
int buttonState = 0; 


void setup()
   {
       lcd.begin (16,2);    // Inicializar el display con 16 caraceres 2 lineas
       lcd.setBacklightPin(3,POSITIVE);
       lcd.setBacklight(HIGH);

       lcd.home ();                   // go home
       lcd.print("Parufito");
       lcd.setCursor ( 0, 1 );        // go to the 2nd line
       lcd.print("Meteo-Station");
       delay(2000);
       lcd.setBacklight(LOW);
   }
void loop() 
   {
       buttonState = digitalRead(buttonPin);
       if (buttonState == HIGH) {     
          // turn LED on:    
          lcd.setBacklight(HIGH);
          delay(2000);
          lcd.setBacklight(LOW);
        } 
        int h = dht.readHumidity();    // Lee la humedad
        int t = dht.readTemperature();
        int x = dht.computeHeatIndex(t, h, false);
        delay(1000); //wait a sec (recommended for DHT11)
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("H: ");
        lcd.setCursor(3,0);
        lcd.print(h);
        lcd.print("%");
        lcd.setCursor(8,0);
        lcd.print("T: ");
        lcd.setCursor(11,0);
        lcd.print(t);
        lcd.print("c");
        lcd.setCursor(0,1);
        lcd.print("Xafogor! ");
        lcd.print(x);
        lcd.print("c");
   }
