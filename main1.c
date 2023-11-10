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
    digitalWrite(TransistorPin, 1023); 
    int TMPValue = analogRead(TMPin);  
 
    float voltage = TMPValue * 5.0;
    voltage /= 1024.0; 
 
    Serial.print(voltage); Serial.println(" volts");
    
    float temp = (voltage - 0.5) * 100 ;  

    Serial.print(temp); Serial.println(" degrees C");
    delay(1000);
}