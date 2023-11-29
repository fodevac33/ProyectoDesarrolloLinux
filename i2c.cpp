#include <iostream>
#include <wiringPiI2C.h>
#include <cstdint>
#include <unistd.h>
#include <cstring>

#define DEVICE_ID 0x08

typedef uint8_t byte;

void printByteArray(const byte* array, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%02X ", array[i]);
    }
    printf("\n");
}


float readFloatFromI2C(int fileDescriptor) {
  float value;
  byte buffer[sizeof(value)];

  // Read bytes into buffer
  read(fileDescriptor, buffer, sizeof(buffer));

  // Copy the buffer into a float
  memcpy(&value, buffer, sizeof(buffer));

  return value;
}

int main(int argc, char **argv) {
  int fileDescriptor = wiringPiI2CSetup(DEVICE_ID);
  if (fileDescriptor == -1) {
      std::cout << "Failed to init I2C communication.\n";
      return -1;
  }
  std::cout << "I2C communication has been successfully setup.\n";

  float humidity = readFloatFromI2C(fileDescriptor);
  float temperature = readFloatFromI2C(fileDescriptor);

  std::cout << "Data received: \n";
  std::cout << "Humidity: " << humidity << "%\n";
  std::cout << "Temperature: " << temperature << " °C\n";

  return 0;
}

