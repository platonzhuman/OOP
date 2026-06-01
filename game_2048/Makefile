CXX     = g++
CXXFLAGS = -Iinclude

SRC = main.cpp src/board.cpp src/renderer.cpp src/input.cpp src/color.cpp src/game.cpp
OUT = program

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
