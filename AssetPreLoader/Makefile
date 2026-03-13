# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -fPIC -Wall -Wextra -I.

# Sources for the asset library
SOURCES := \
    attackFront.cpp \
	attackBack.cpp \
	attackLeft.cpp \
	attackRight.cpp \
	roll.cpp \
	rollOther.cpp \
	playerFront.cpp \
	playerBack.cpp \
	playerLeft.cpp \
	playerRight.cpp \
	lightPillar.cpp \
	squidEnemy.cpp \
    AssetLib.cpp

HEADERS := AssetLib.h

# Output shared library
TARGET := libAssetLib.so

# SFML libraries
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Default rule
all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -shared -o $@ $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)

