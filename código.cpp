#include <ArduinoJson.h>
#include <DHT.h> //Adafruit_DHT
#define trigPin 10
#define echoPin 9
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
int sensorLDR = A5;
int counter;
float duration;
unsigned long time;



void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sensorLDR, INPUT);
  dht.begin();
}

void loop() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = 0;
  counter = 0;
  while (--counter != 0) 
  {
    if (PINB & 2) 
    {
      time = micros();
      break;
    }
  }
  while (--counter != 0) 
  {
    if ((PINB & 2) == 0) 
    {
      duration = micros() - time;
      break;
    }
  }


  StaticJsonDocument<100> json; // Tamanho do buffer para o JSON
  float distancy = (duration / 2) * 0.0344;
  int humidity = dht.readHumidity(); // Lê a umidade do sensor
  float temperature = dht.readTemperature(); // Lê a temperatura do sensor em Celsius
  int light = analogRead(sensorLDR);
  json["distancia"] = distancy;
  json["luminosidade"] = light;
  json["umidade"] = humidity;
  json["temperatura"] = temperature;

 

  String jsonString;
  serializeJson(json, jsonString);
  Serial.println(jsonString); // Envia o JSON via serial

  delay(1000);
}