# Makefile for termn
CXX = g++
CXXFLAGS = -Wall -std=c++17
LDFLAGS = -lncurses
TARGET = termn
SRC = src/main.cpp src/file_utils.cpp src/ui.cpp
BUILD_DIR = build

# Test-related variables
GTEST_FLAGS = -lgtest -lgtest_main -pthread

# FileUtils test
TEST_TARGET_FILEUTILS = runTestsFile
TEST_SRC_FILEUTILS = tests/file_utils_test.cpp src/file_utils.cpp  

# UI test
TEST_TARGET_UI = runTestsUI
TEST_SRC_UI = tests/ui_test.cpp src/ui.cpp

# Default target
all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $(SRC) $(LDFLAGS)

# Build and run all tests
test: test-ui test-fileutils

# Individual test builds
test-ui: $(BUILD_DIR)/$(TEST_TARGET_UI)
	@echo "Running UI tests..."
	./$(BUILD_DIR)/$(TEST_TARGET_UI)

test-fileutils: $(BUILD_DIR)/$(TEST_TARGET_FILEUTILS)
	@echo "Running File Utils tests..."
	./$(BUILD_DIR)/$(TEST_TARGET_FILEUTILS)

# Build rules
$(BUILD_DIR)/$(TEST_TARGET_UI): $(TEST_SRC_UI)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_FLAGS) $(LDFLAGS)

$(BUILD_DIR)/$(TEST_TARGET_FILEUTILS): $(TEST_SRC_FILEUTILS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_FLAGS) $(LDFLAGS)

# Install binary to system path
install: all
	sudo cp $(BUILD_DIR)/$(TARGET) /usr/local/bin/termn
	@echo "Installed successfully! You can now run 'termn' from anywhere."

# Uninstall binary
uninstall:
	sudo rm -f /usr/local/bin/termn
	@echo "termn uninstalled."

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
