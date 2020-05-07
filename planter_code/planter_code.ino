#include "DHT.h"

#define soilHumidiySensorPower 7
#define soilHumidiySensorPin A0

#define temperatureSensorPin 2
#define DHTTYPE DHT11
DHT dht(temperatureSensorPin, DHTTYPE);
 
int soilHumiditySensorValue;   
int humiditySensorValue;  
int temperatureSensorValue;  

void setup() {
 initHumiditySensor();
 initTemperatureSensor();
 Serial.begin(9600);
 }

void loop() {
 soilHumiditySensorValue = getSoilHumiditySensorValue();
 humiditySensorValue = getHumiditySensorValue();
 temperatureSensorValue = getTemperatureSensorValue();
 delayM(1); 
}
 
int getSoilHumiditySensorValue(){
  digitalWrite(soilHumidiySensorPower, HIGH);
  delay(10);
  int sensorValue = analogRead(soilHumidiySensorPin);
  digitalWrite(soilHumidiySensorPower, LOW);

  Serial.print("Soil Humidity: ");
  Serial.println(sensorValue);

  return sensorValue;
}

int getHumiditySensorValue(){
  int sensorValue = dht.readHumidity();

  Serial.print("Air Humidity: ");
  Serial.print(sensorValue);
  Serial.println("%");

  return sensorValue;
}

int getTemperatureSensorValue(){
  int sensorValue = dht.readTemperature();

  Serial.print("Temperature: ");
  Serial.print(sensorValue);
  Serial.println("°C");

  return sensorValue;
}

void initHumiditySensor(){
  pinMode(soilHumidiySensorPower, OUTPUT);
  digitalWrite(soilHumidiySensorPower, LOW);
}

void initTemperatureSensor(){
  dht.begin();
}

void delayM(double value){
  delay(round((value * 60) * 1000));
}
