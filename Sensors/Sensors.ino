#include <DHT.h>
#include <Wire.h>

#define DHTPIN 2         // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11    // DHT 11
#define SLAVE_ADDRESS 0x08 // I2C Address for the Arduino

DHT dht(DHTPIN, DHTTYPE);

// Global variables to store the latest readings
float lastHumidity = 0.0;
float lastTemperature = 0.0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(sendData);
}

void loop() {
  // Wait 2 seconds between measurements to avoid maxing out the DHT sensor
  delay(2000);
  
  // Reading temperature or humidity takes about 250 milliseconds
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and only update the global variables if they didn't
  if (!isnan(h) && !isnan(t)) {
    lastHumidity = h;
    lastTemperature = t;

  Serial.println("Humedad: " + String(h) + " %\tTemperatura: " + String(t) + " °C");

  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
}

// This function will be called when the Raspberry Pi requests data
void sendData() {
  byte buffer[4];

  // Send the humidity
  floatToBytes(lastHumidity, buffer);
  Wire.write(buffer, 4);

  // Send the temperature
  floatToBytes(lastTemperature, buffer);
  Wire.write(buffer, 4);
}

// Helper function to convert a float to a 4-byte array
void floatToBytes(float val, byte* bytes_array) {
  // Create a union of shared memory space
  union {
    float float_variable;
    byte temp_array[4];
  } u;
  // Overwrite bytes of union with float variable
  u.float_variable = val;
  // Assign bytes to input array
  memcpy(bytes_array, u.temp_array, 4);
}

