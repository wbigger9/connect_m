# Compiler
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Executable name
TARGET = connectM

# Source files
SRC = main.cpp board.cpp connectM.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default rule to build the executable
all: $(TARGET)

# Link object files to create the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Compile each .cpp file into an .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(TARGET)
