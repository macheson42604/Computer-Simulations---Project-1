# Terminal Run Command: 'mingw32-make' 
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Target executable
TARGET = SIM

# For deleting the target
# TARGET_DEL = SIM.exe

# Source files
SRCS = GamePlay.cpp Card.cpp Player.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: $(TARGET)
# all: $(TARGET) run

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	$(TARGET)

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJS)


# Dependencies
GamePlay.o: GamePlay.cpp GamePlay.hpp Player.hpp Card.hpp
Player.o: Player.cpp Player.hpp Card.hpp
Card.o: Card.cpp Card.hpp
