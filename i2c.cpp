#include <iostream>
#include <wiringPiI2C.h>
#include <cstdint>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include "HTTPRequest.hpp"

#define DEVICE_ID 0x08

typedef uint8_t byte;

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

  // Copy the buffer into the float array
  memcpy(value, buffer, sizeof(buffer));

  // Return the pointer to the dynamically allocated floats
  return value;
}

void postI2CData (int *fd) {
  float* i2cArray = readFloatFromI2C(*fd, 4);
  float temperature = i2cArray[0];
  float termistor = i2cArray[1];
  float latitud = i2cArray[2];
  float longitud = i2cArray[3];

  std::ostringstream stream;
  stream << "{\"ambientTemp\": " << temperature
          << ", \"motorTemp\": " << termistor 
          << ", \"latitude\": " << latitud
          << ", \"longitude\": " << longitud << "}";

  try
  {
    std::cout << "Json: " << stream.str() << "\n";
    http::Request request{"http://192.168.171.241:3333/api"};
    const std::string body = stream.str();
    const auto response = request.send("POST", body, {
      {"Content-Type", "application/json"}
    });
    std::cout << "Request Sent" << "\n";
    std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result
  }
  catch (const std::exception& e) 
  {
    std::cerr << "Request failed, error: " << e.what() << '\n';
  }
  free(i2cArray);
}


int main(int argc, char **argv) {
  int fileDescriptor = wiringPiI2CSetup(DEVICE_ID);
  if (fileDescriptor == -1) {
      std::cout << "Failed to init I2C communication.\n";
      return -1;
  }
  std::cout << "I2C communication has been successfully setup.\n";

  postI2CData(&fileDescriptor);

  return 0;
}

