#include "DHT.h"

#define DHTPIN1 2   // Room
#define DHTPIN2 3   // Rack
#define DHTTYPE DHT11

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht1.begin();
  dht2.begin();
}

void loop() {
  delay(5000);

  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();

  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();

  if (isnan(h1) || isnan(t1) || isnan(h2) || isnan(t2)) {
    Serial.println("Erro");
    return;
  }

  Serial.print(h1);
  Serial.print(";");
  Serial.print(t1);
  Serial.print(";");
  Serial.print(h2);
  Serial.print(";");
  Serial.println(t2);
}