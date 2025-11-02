# Makefile for termn
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = termn
SRC = src/termn.cpp
BUILD_DIR = build

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $(SRC)

install: all
	sudo cp $(BUILD_DIR)/$(TARGET) /usr/local/bin/termn
	@echo "Installed successfully! You can now run 'termn' from anywhere."

uninstall:
	sudo rm -f /usr/local/bin/termn
	@echo "termn uninstalled."

clean:
	rm -rf $(BUILD_DIR)
