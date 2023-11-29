# Define compiler and flags
CXX=g++
CXXFLAGS=-Wall -lwiringPi

# Define target and source
TARGET=i2c
SOURCE=i2c.cpp

# Default target
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) -o $(TARGET) $(SOURCE) $(CXXFLAGS)

# Clean the built target
clean:
	rm -f $(TARGET)

.PHONY: all clean

