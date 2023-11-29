#include <iostream>
#include <wiringPiI2C.h>
#include <cstdint>
#include <unistd.h>
#include <cstring>

#define DEVICE_ID 0x08

typedef uint8_t byte;

void printByteArray(const byte* array, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        std::cout << std::hex << std::nouppercase;
        std::cout << (array[i] >> 4);  // Print the high nibble.
        std::cout << (array[i] & 0x0F); // Print the low nibble.
        std::cout << ' ';  // Separator space.
    }
    std::cout << std::dec << std::endl; // End with a newline.
}


float *readFloatFromI2C(int fileDescriptor, uint8_t numberOfVariables) {
  // Allocate memory dynamically for two floats
  float *value = (float *)malloc(numberOfVariables * sizeof(float));
  if (value == NULL) {
    return NULL;
  }

  // Create a buffer to hold 8 bytes
  byte buffer[numberOfVariables*4];

  // Read bytes into buffer from the I2C device
  read(fileDescriptor, buffer, sizeof(buffer));

  // Print the buffer contents
  printByteArray(buffer, sizeof(buffer));

  // Copy the buffer into the float array
  memcpy(value, buffer, sizeof(buffer));

  // Return the pointer to the dynamically allocated floats
  return value;
}

int main(int argc, char **argv) {
  int fileDescriptor = wiringPiI2CSetup(DEVICE_ID);
  if (fileDescriptor == -1) {
      std::cout << "Failed to init I2C communication.\n";
      return -1;
  }
  std::cout << "I2C communication has been successfully setup.\n";

  float* i2cArray = readFloatFromI2C(fileDescriptor, 2);
  float temperature = i2cArray[0];
  float humidity = i2cArray[1];

  std::cout << "Data: \n";
  std::cout << "Humidity: " << humidity << "%\n";
  std::cout << "Temperature: " << temperature << " °C\n";

  free(i2cArray);

  return 0;
}

