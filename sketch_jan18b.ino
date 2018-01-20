#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTTYPE DHT11
#define DHTPIN 8
SoftwareSerial ESPserial(10,11); // RX | TX

int trigPin=13;
int echoPin=12;
long duration;
float cm,inches;

DHT dht(DHTPIN, DHTTYPE);
void setup() {
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
  ESPserial.begin(115200);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Remember to to set Both NL & CR in the serial monitor.");
  Serial.println("Ready");
  Serial.println("");   
}

void DistanceRead(){
      Serial.println("Reading WATER LEVEL....");
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);
      Serial.print(duration);
      
      cm = (duration/2) / 29.1;
      inches = (duration/2) / 29.1*0.393701;
     

}

int TemperatureValue;
int HumidityValue;
String dataString = "";

void loop() {
 
  
      
      if(ESPserial.available()>0){
         TemperatureValue=dht.readTemperature();
        HumidityValue=dht.readHumidity();
      DistanceRead();
        dataString.concat(TemperatureValue);
        dataString.concat(",");
        dataString.concat(HumidityValue);
        dataString.concat(",");
        dataString.concat(cm);
        
       Serial.println(ESPserial.readStringUntil('\n'));
       delay(300);
       ESPserial.println(dataString);
       Serial.println(dataString);
       dataString = "";
       Serial.println(TemperatureValue);
       Serial.println(HumidityValue);
       Serial.println(cm);
  
}

}
