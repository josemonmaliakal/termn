# Makefile for termn
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = termn
SRC = src/main.cpp src/file_utils.cpp
BUILD_DIR = build

# Test-related variables
TEST_TARGET = runTests
TEST_SRC = tests/test_file_utils.cpp src/file_utils.cpp
GTEST_FLAGS = -lgtest -lgtest_main -pthread



all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $(SRC)

# Build and run tests
test: $(BUILD_DIR)/$(TEST_TARGET)
	./$(BUILD_DIR)/$(TEST_TARGET)

$(BUILD_DIR)/$(TEST_TARGET): $(TEST_SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TEST_TARGET) $(TEST_SRC) $(GTEST_FLAGS)

install: all
	sudo cp $(BUILD_DIR)/$(TARGET) /usr/local/bin/termn
	@echo "Installed successfully! You can now run 'termn' from anywhere."

uninstall:
	sudo rm -f /usr/local/bin/termn
	@echo "termn uninstalled."

clean:
	rm -rf $(BUILD_DIR)
