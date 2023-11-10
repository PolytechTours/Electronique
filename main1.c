#include <SoftwareSerial.h>
#define rxPin 11 // Broche 11 en tant que RX, à raccorder sur TX du HC-05
#define txPin 10 // Broche 10 en tant que TX, à raccorder sur RX du HC-05
SoftwareSerial mySerial(rxPin, txPin);

const int TransistorPin = 11;
const int TMPin = 23;

void setup()
{
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    mySerial.begin(38400);
    Serial.begin(38400);  
    pinMode(TransistorPin, OUTPUT);
    pinMode(TMPin, INPUT);
}
 
void loop()                     
{
    int TMPValue = analogRead(TMPin);  
 
    float voltage = TMPValue * 5.0;
    voltage /= 1024.0; 
 
    Serial.print(voltage); Serial.println(" volts");
    
    float temp = (voltage - 0.5) * 100 ;  

    Serial.print(temp); Serial.println(" degrees C");
    delay(1000);

    digitalWrite(TransistorPin, 0); 
    //decroissance proportionelle de la tension a la temperature

    if (temp > 27) {
        digitalWrite(TransistorPin, 200);
    }
    if (temp > 28) {
        digitalWrite(TransistorPin, 500);
    }
    if (temp > 29) {
        digitalWrite(TransistorPin, 800);
    }
    if (temp > 29.8) {
        digitalWrite(TransistorPin, 1023);
    }
}

//void loop() //BLE
//{
//    int i = 0;
//    char someChar[32] = {0};
//    if(Serial.available()) {
//    do{
//    someChar[i++] = Serial.read();
//    delay(3);
//    }while (Serial.available() > 0);
//    mySerial.println(someChar);
//    Serial.println(someChar);
//    }
//    while(mySerial.available())
//    Serial.print((char)mySerial.read());
//}