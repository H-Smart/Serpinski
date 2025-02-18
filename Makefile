# Compiler
CXX = g++
# Compiler flags
XFLAGS = -framework OpenGL -framework GLUT -Wno-deprecated-declarations
# Source files
SRC_MOUNT = fractal_mountains_2d.cpp
SRC_TURT = turtle.cpp
SRC_SIERP_3D = sierpinski_3d.cpp
SRC_TURT_SIERP_2D = turtle_sierpinski_2d.cpp
# Output executables
OUT_MOUNT = fm
OUT_TURT = turt
OUT_SIERP_3D = sp_3d
OUT_TURT_SIERP_2D = turt_sp_2d
# Default target
all: $(OUT_MOUNT) $(OUT_TURT) $(OUT_SIERP_3D) $(OUT_TURT_SIERP_2D) 

# Compile the program
$(OUT_MOUNT): $(SRC_MOUNT)
	$(CXX) $(XFLAGS) $(SRC_MOUNT) -o $(OUT_MOUNT)

$(OUT_TURT): $(SRC_TURT)
	$(CXX) $(XFLAGS) $(SRC_TURT) -o $(OUT_TURT)

$(OUT_SIERP_3D): $(SRC_SIERP_3D)
	$(CXX) $(XFLAGS) $(SRC_SIERP_3D) -o $(OUT_SIERP_3D)

$(OUT_TURT_SIERP_2D): $(SRC_TURT_SIERP_2D)
	$(CXX) $(XFLAGS) $(SRC_TURT_SIERP_2D) -o $(OUT_TURT_SIERP_2D)
# Clean build files
clean:
	rm -f  $(OUT_MOUNT) $(OUT_TURT) $(OUT_SIERP_3D) $(OUT_TURT_SIERP_2D) 
