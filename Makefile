# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude -std=c++17 -Wall -Wextra

# Directories
SRC_DIR = src
APP_DIR = app
BUILD_DIR = build

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp $(APP_DIR)/*.cpp)
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))

# Output binary
TARGET = $(BUILD_DIR)/app

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(APP_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean