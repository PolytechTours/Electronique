#include <Servo.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#define rxPin 11 // Broche 11 en tant que RX, à raccorder sur TX du HC-05
#define txPin 10 // Broche 10 en tant que TX, à raccorder sur RX du HC-05
SoftwareSerial mySerial(rxPin, txPin);

const int TransistorPin = 10;
const int TMPin = 23;
const int LEDPin = 6;
String incomingMessage = "";
float target = 29;
float targetAvg = 10;
bool showChange = true;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo myservo;

void setup()
{ //init du bluetooth
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);

    //init temperature
    mySerial.begin(38400);
    Serial.begin(38400);  
    pinMode(TransistorPin, OUTPUT);
    pinMode(TMPin, INPUT);

    //init servo et led
    myservo.attach(9);
    pinMode(LEDPin, OUTPUT);

    
    digitalWrite(TransistorPin, 0); 

    lcd.begin(16, 2);
    lcd.print("hello, world!");
}
 
void loop()                     
{
    //temperature
    int TMPValue = analogRead(A0);  
 
    float voltage = TMPValue * 5.0;
    voltage /= 1024.0; 
 
    //Serial.print(voltage); Serial.println(" volts");
    
    float temp = (voltage - 0.5) * 100 ;  

    Serial.print(temp); Serial.println(" degrees C");
    delay(1000);

    //Serial.println(target +(target/100)*targetAvg);
    //Serial.println(target -(target/100)*targetAvg);
    //Serial.println(temp);
    //Serial.println("---");

    if(temp<target-(target/100)*targetAvg && showChange) {
      analogWrite(TransistorPin, 255);
      Serial.print("Temperature actuelle : "); Serial.print(temp); Serial.println(" degrees C");
      Serial.println("Four : préchauffage");
      showChange = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Four : ");
      lcd.setCursor(0, 1);
      lcd.print("Prechauffage");      
    }
    else if (temp > target +(target/100)*targetAvg && showChange){
      analogWrite(TransistorPin, 0);
      Serial.print("Temperature actuelle : "); Serial.print(temp); Serial.println(" degrees C");
      Serial.println("Four : Poulet cuit");
      showChange = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Four : ");
      lcd.setCursor(0, 1);
      lcd.print("Poulet cuit");
    }
    else if (temp < target+1 && temp > target-1){
      showChange = true;
    }

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingMessage = Serial.readString();

    lcd.clear();

    // say what you got:
    if(incomingMessage == "temp up\n"){
      target = target + 1;
      Serial.print("New target temp : "); Serial.println(target);
      lcd.setCursor(0, 0);
      lcd.print("New temp : ");
      lcd.setCursor(0, 1);
      lcd.print(target);
    }
    else if(incomingMessage == "temp down\n"){
      target = target - 1;
      Serial.print("New target temp : "); Serial.println(target);
      lcd.setCursor(0, 0);
      lcd.print("New temp : ");
      lcd.setCursor(0, 1);
      lcd.print(target);
    }
    else if(incomingMessage == "temp monit\n"){
      Serial.println("---");
      Serial.println(target); Serial.println(target +(target/100)*targetAvg); Serial.println(target -(target/100)*targetAvg);
      Serial.println("---");
      lcd.setCursor(0, 0);
      lcd.print("Temp : ");
      lcd.setCursor(0, 1);
      lcd.print(target);
    }
    else if(incomingMessage == "servo 0\n"){
      myservo.write(0);
      lcd.setCursor(0, 0);
      lcd.print("Servo : ");
      lcd.setCursor(0, 1);
      lcd.print("0");
    }
    else if(incomingMessage == "servo 90\n"){
      myservo.write(90);
      lcd.setCursor(0, 0);
      lcd.print("Servo : ");
      lcd.setCursor(0, 1);
      lcd.print("90");
    }
    else if(incomingMessage == "servo 180\n"){
      myservo.write(180);
      lcd.setCursor(0, 0);
      lcd.print("Servo : ");
      lcd.setCursor(0, 1);
      lcd.print("180");
    }
    else if(incomingMessage == "servo 270\n"){
      myservo.write(270);
      lcd.setCursor(0, 0);
      lcd.print("Servo : ");
      lcd.setCursor(0, 1);
      lcd.print("270");
    }
    else if(incomingMessage == "servo 360\n"){
      myservo.write(360);
      lcd.setCursor(0, 0);
      lcd.print("Servo : ");
      lcd.setCursor(0, 1);
      lcd.print("360");
    }
    else if(incomingMessage == "led on\n"){
      analogWrite(LEDPin, 255);
      lcd.setCursor(0, 0);
      lcd.print("Led : ");
      lcd.setCursor(0, 1);
      lcd.print("ON");
    }
    else if(incomingMessage == "led off\n"){
      analogWrite(LEDPin, 0);
      lcd.setCursor(0, 0);
      lcd.print("Led : ");
      lcd.setCursor(0, 1);
      lcd.print("OFF");
    }
    else{
      Serial.print("Unknown command : ");
      Serial.println(incomingMessage);
      lcd.setCursor(0, 0);
      lcd.print("ERROR : ");
      lcd.setCursor(0, 1);
      lcd.print("418");
    }

    incomingMessage = "";
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