# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated-declarations
# Source file
SRC = fractal_mountains_2d.cpp
# Output executable
OUT = fm

# Default target
all: $(OUT)

# Compile the program
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# Clean build files
clean:
	rm -f $(OUT)

