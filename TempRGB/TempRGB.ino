/* TERMOMETRE DHT11 - LED RGB
Codi arreplegat de mil llocs

Sensor DHT11
Boto per canviar de estat (0 = Temperatura, 1 = random, 2 = Pending microfon
Led RGB
Codi colors: 
http://www.cambridgebaby.co.uk/catalog/index.php?main_page=essentials&productID=40&fullsiteoverride=mobile

Temperatura Xafogor (Humidex):
http://www.acom.cat/utilitats/humidex.html

*/


//DHT11 Setup
#include <DHT.h>
#define DHTTYPE DHT11  
const int DHTPin = 2;     // what digital pin we're connected to
DHT dht(DHTPin, DHTTYPE);
 
//Led RFBGB
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int botoPin = 3;

//Interruptor per triar mode
int pulsador=0;                   //almacena el estado del botón
int estado=0;                      //0=termometre, 1=random colors
int pulsadorAnt=0; 

void setup() {
 Serial.begin(9600);
 Serial.println("DHTxx test!");
 dht.begin();
 // Start off with the LED off.
 setColourRgb(0,0,0);
 pinMode(botoPin, INPUT);  
}

void loop() {
  
  pulsador = digitalRead(botoPin);
  
  if((pulsador==HIGH)&&(pulsadorAnt==LOW)){  //si el boton es pulsado y antes no lo estaba
    estado=1-estado;
    delay(40);               //pausa de 40 ms
  }
  pulsadorAnt=pulsador;      //actualiza el nuevo estado del boton     

  unsigned int rgbColour[3];

//DHT agafar valors
  int h = dht.readHumidity();    // Lee la humedad
  int t = dht.readTemperature();
  int x = dht.computeHeatIndex(t, h, false);
//Print results DHT
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  Serial.print("Xafogor: ");
  Serial.print(x);
  Serial.print(" *C ");

  //Button To Change STATE 
  // 
  if(estado==1) {                 //si el estado es 1 random colors
    // Start off with red.
    rgbColour[0] = 255;
    rgbColour[1] = 0;
    rgbColour[2] = 0;  
  
    // Choose the colours to increment and decrement.
    for (int decColour = 0; decColour < 3; decColour += 1) {
      int incColour = decColour == 2 ? 0 : decColour + 1;
  
      // cross-fade the two colours.
      for(int i = 0; i < 255; i += 1) {
        rgbColour[decColour] -= 1;
        rgbColour[incColour] += 1;
        Serial.println(rgbColour[0]);
                Serial.println(rgbColour[1]);
                        Serial.println(rgbColour[2]);
        setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
        delay(100);
      }
    }
  }
  //si el estado es 0 termometre color
  else{
    //TEST x per forçar temperatura
    //x=15;
    //vermell
    if (x > 29 ) setColourRgb(255,0,0);
    //taronja
    if (x > 26 && x <= 29 ) setColourRgb(229,26,0);
    //groc
    if (x > 23 && x <= 26 ) setColourRgb(166,89,0);
    //verd
    if (x > 18 && x <= 23) setColourRgb(0,255,0);
    //blau clar
    if (x > 15 && x <= 18 ) setColourRgb(0,185,70);
    //blau
    if (x > 12 && x <= 15 ) setColourRgb(0,0,255);
    //lilaa
    if (x <= 12 ) setColourRgb(40,0,216);
    delay(1000);
  }


}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, 255-red);
  analogWrite(greenPin, 255-green);
  analogWrite(bluePin, 255-blue);
}
