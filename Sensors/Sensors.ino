#include <DHT.h>
#include <Wire.h>

#define DHTPIN 2         // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11    // DHT 11
#define SLAVE_ADDRESS 0x08 // I2C Address for the Arduino

DHT dht(DHTPIN, DHTTYPE);

float lastHumidity = 0.0;
float lastTemperature = 0.0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(sendData);
}

void loop() {
  delay(2000);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) && !isnan(t)) {
    lastHumidity = h;
    lastTemperature = t;

  Serial.println("Humedad: " + String(h) + " %\tTemperatura: " + String(t) + " °C");

  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
}

void sendData() {
  byte buffer[4];

  floatToBytes(lastTemperature, buffer);
  Wire.write(buffer, 4);

  floatToBytes(lastHumidity, buffer);
  Wire.write(buffer, 4);
}

void floatToBytes(float val, byte* bytes_array) {
  union {
    float float_variable;
    byte temp_array[4];
  } u;
  u.float_variable = val;
  memcpy(bytes_array, u.temp_array, 4);
}
