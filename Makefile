# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable
TARGET = trie_program

# Source files
SRCS = main.cpp trie.cpp invader.cpp

# Object files (generated from source files)
OBJS = $(SRCS:.cpp=.o)

# Libraries and include paths
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE = -I/opt/homebrew/include -I. # Added SFML include path

# Default target to build the program
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS) -L/opt/homebrew/lib # Added SFML library path

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (do not correspond to actual files)
.PHONY: all clean
