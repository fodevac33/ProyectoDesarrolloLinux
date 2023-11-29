#include <iostream>
#include <wiringPiI2C.h>
#include <cstdint>
#include <unistd.h>
#include <cstring>

#define DEVICE_ID 0x08

typedef uint8_t byte;

void printByteArray(const byte* array, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        // Output each byte as a hexadecimal number.
        // Use the stream manipulators hex and nouppercase to format the output.
        std::cout << std::hex << std::nouppercase;
        // Cast to unsigned int and output as hexadecimal.
        std::cout << (array[i] >> 4);  // Print the high nibble.
        std::cout << (array[i] & 0x0F); // Print the low nibble.
        std::cout << ' ';  // Separator space.
    }
    std::cout << std::dec << std::endl; // End with a newline.
}


float readFloatFromI2C(int fileDescriptor) {
  float value[2];
  byte buffer[sizeof(value)*2];

  int buffer_size = sizeof(buffer) / sizeof(byte);

  // Read bytes into buffer
  read(fileDescriptor, buffer, sizeof(buffer));


  printByteArray(buffer, buffer_size);

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

  float i2cArray = readFloatFromI2C(fileDescriptor);
  float temperature = i2cArray[0];
  float humidity = i2cArray[1];

  std::cout << "Data received: \n";
  std::cout << "Humidity: " << humidity << "%\n";
  std::cout << "Temperature: " << temperature << " °C\n";

  return 0;
}

