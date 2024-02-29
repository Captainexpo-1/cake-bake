# Makefile for compiling a simple C++ program

# Compiler settings - Can change to clang++ if you prefer
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -O2

# build directory
BUILD_DIR = build

# Create build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

# Build target executable:
TARGET = $(BUILD_DIR)/cake-bake

# Default target
all: $(TARGET)

$(TARGET): cake-bake.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) cake-bake.cpp

# Clean the build
clean:
	rm -f $(TARGET)

.PHONY: all clean
