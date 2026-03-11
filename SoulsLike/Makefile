CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD -MP -I. -I../Manager -I../AssetPreLoader

# Link flags: look for .so files in their folders, set rpath for runtime
LDFLAGS = -L../Manager -lManager -Wl,-rpath=../Manager \
          -L../AssetPreLoader -lAssetLib -Wl,-rpath=../AssetPreLoader \
          -lsfml-graphics -lsfml-window -lsfml-system \
          -lsfml-audio -lsfml-network \
          -lX11 -lXrandr -lXcursor -lXrender -lXext -lXfixes -lGL

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)

TARGET = sim

all: $(TARGET)

# Build the executable
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Compile each cpp into object
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files for automatic header tracking
-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)

run: $(TARGET)
	LD_LIBRARY_PATH=Manager:AssetPreLoader ./$(TARGET)