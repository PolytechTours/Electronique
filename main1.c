const int TransistorPin = 11;
const int TMPin = 23;

void setup()
{
    Serial.begin(9600);  
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