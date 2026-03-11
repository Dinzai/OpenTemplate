# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -fPIC -Wall -Wextra -I.

# Sources for the asset library
SOURCES := \
    CollisionManager.cpp \
	InputManager.cpp \
	Scene.cpp\
	SignalManager.cpp \
	ManagerLib.cpp

HEADERS := ManagerLib.h

# Output shared library
TARGET := libManager.so

# SFML libraries
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Default rule
all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -shared -o $@ $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)
