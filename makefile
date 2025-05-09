# Makefile for DataStructureVisualization Project

# --- Compiler and Flags ---
CXX = g++
# CXXFLAGS for Debug: -Wall -Wextra -std=c++17 -g -Iinclude -Iexternal -D_DEBUG
# CXXFLAGS for Release: -Wall -Wextra -std=c++17 -O2 -Iinclude -Iexternal -DNDEBUG -s # -s strips symbols
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -Iinclude -Iexternal -DNDEBUG -s

# --- Project Structure ---
TARGET_NAME = ds_visualizer
INCLUDE_DIR = include
EXTERNAL_DIR = external
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
LIB_DIR = lib

# --- Source Files ---
SOURCES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*/*/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# --- Platform Detection and Linker Flags ---
# Default to Linux
PLATFORM ?= Linux
TARGET_EXT =
LDFLAGS =

ifeq ($(OS),Windows_NT)
	PLATFORM = Window
	TARGET_EXT = .exe
	# Example LDFLAGS for MinGW static linking with raylib in lib/Window
	# Adjust paths and library names as needed (e.g., libraylib.a)
	LDFLAGS = -L$(LIB_DIR)/$(PLATFORM) -lraylib -lopengl32 -lgdi32 -lwinmm -static # Add -static if linking static raylib
	# If using shared raylib.dll, you might need different flags or ensure DLL is findable at runtime
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		PLATFORM = Linux
		TARGET_EXT =
		# Example LDFLAGS for Linux static linking with raylib in lib/Linux
		LDFLAGS = -L$(LIB_DIR)/$(PLATFORM) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 # Common libs
		# If raylib is installed system-wide, you might just use: -lraylib -lGL ...
	endif
	ifeq ($(UNAME_S),Darwin)
		PLATFORM = MacOS
		TARGET_EXT =
		# Example LDFLAGS for MacOS linking with raylib in lib/MacOS
		LDFLAGS = -L$(LIB_DIR)/$(PLATFORM) -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio # Remove -framework CoreFoundation, -framework CoreVideo if not needed
		# If using raylib via a package manager (like Homebrew), adjust LDFLAGS, e.g., -L/opt/homebrew/lib -lraylib ...
	endif
endif

TARGET = $(BIN_DIR)/$(TARGET_NAME)$(TARGET_EXT)

# --- Build Rules ---

# Default target: Build the executable
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking target: $@"
	@mkdir -p $(BIN_DIR) # Ensure bin directory exists
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS) # CXXFLAGS usually not needed for linking unless specific linker options are passed via it
	@echo "Build complete: $@"

# Rule to compile .cpp files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) 
	@echo "Compiling: $< -> $@"
	@mkdir -p $(dir $@) # Ensure subdirectory in obj exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to create the main build directory
$(OBJ_DIR):
	@mkdir -p $@

# --- Utility Rules ---

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete."

# Run the built executable
run: $(TARGET)
	@echo "Running executable: $(TARGET)"
	./$(BIN_DIR)/$(TARGET_NAME)$(TARGET_EXT) # Change directory before running

# Rebuild (clean then build)
re: clean all

# Phony targets prevent conflicts with files named 'all', 'clean', 'run', 're'
.PHONY: all clean run re