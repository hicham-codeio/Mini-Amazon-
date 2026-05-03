CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRC = $(wildcard src/*/*.cpp) src/main.cpp
OUT = app

all:
\t$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
\trm -f $(OUT)
