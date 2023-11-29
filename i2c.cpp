#include <iostream>
#include <wiringPiI2C.h>
#include <cstdint>
#include <unistd.h>
#include <cstring>

#define DEVICE_ID 0x08

// Function to read a float from I2C
float readFloatFromI2C(int fd) {
    float value;
    char buffer[sizeof(value)];

    // Read bytes into buffer
    read(fd, buffer, sizeof(buffer));

    // Copy the buffer into a float
    memcpy(&value, buffer, sizeof(buffer));

    return value;
}

int main(int argc, char **argv) {
    // Setup I2C communication
    int fd = wiringPiI2CSetup(DEVICE_ID);
    if (fd == -1) {
        std::cout << "Failed to init I2C communication.\n";
        return -1;
    }
    std::cout << "I2C communication has been successfully setup.\n";

    // Assume the Arduino sends humidity first, then temperature
    float humidity = readFloatFromI2C(fd);
    float temperature = readFloatFromI2C(fd);

    std::cout << "Data received: \n";
    std::cout << "Humidity: " << humidity << "%\n";
    std::cout << "Temperature: " << temperature << " °C\n";

    return 0;
}

