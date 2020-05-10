#include <DHT.h>
#include <Servo.h>

#define soilHumidiySensorPower 7
#define soilHumidiySensorPin A0

#define temperatureSensorPin 2
#define DHTTYPE DHT11

#define servoPin 8
#define servoVentsOpen 45
#define servoVentsClosed 0

#define maxAirHumidity 70
#define minAirHumidity 60

DHT dht(temperatureSensorPin, DHTTYPE);
 
int soilHumiditySensorValue;    
int temperatureSensorValue;  
int servoAngle = 0;
int loopCounter = 0;
Servo servo;

void setup() {
 initHumiditySensor();
 initTemperatureSensor();
 initServo(servo);
 Serial.begin(9600);
 }

void loop() {
 if (loopCounter = 0){ //Read soil humidity every +- 1 hour to prevent oxidation of the sensor
  soilHumiditySensorValue = getSoilHumiditySensorValue();
 }

 ManageAirHumidity(getHumiditySensorValue());
 temperatureSensorValue = getTemperatureSensorValue();

 setLoopCounter();
 delayM(0.1); 
}

void ManageAirHumidity(int airHumiditySensorValue){ 
 if (airHumiditySensorValue > maxAirHumidity){
  servoAngle = openVents(servoAngle);
 }

 if (airHumiditySensorValue < minAirHumidity){
  servoAngle = closeVents(servoAngle);
 } 
}

void setLoopCounter(){
 loopCounter++;

 if (loopCounter = 360){ //Reset every hour
  loopCounter = 0; 
 }
}

int openVents(int currentAngle){
  for (int angle = currentAngle; angle < servoVentsOpen + 1; angle++)  
  {                                  
    servo.write(angle);         
    delay(15);                   
  } 

  return servoVentsOpen;
}

int closeVents(int currentAngle){
  for (int angle = currentAngle; angle > servoVentsClosed - 1; angle--)  
  {                                  
    servo.write(angle);            
    delay(15);                   
  } 

  return servoVentsClosed;
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

void initServo(Servo s) {
  s.attach(servoPin);
  
  servoAngle = openVents(servoAngle);
  servoAngle = closeVents(servoAngle);
}

void delayM(double value){
  delay(round((value * 60) * 1000));
}
