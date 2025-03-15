CXX := g++
CXXFLAGS := -std=c++20 -Wall
SRC := main.cpp \
	System/*.cpp \
	Program/*.cpp \
	Instructions/*.cpp \
	GeneticOperators/*.cpp \
	Environments/*.cpp
INCLUDE := -ISystem \
	-IProgram \
	-IEnvironments \
	-IGeneticOperators \
	-IInstructions \
	-isystem Third-Party/Empirical/include/
OUT := evolve

all: O3

slow: CXXFLAGS += -O0
slow: build

O3: CXXFLAGS += -O3
O3: build

parallel: CXXFLAGS += -O3 -fopenmp -pthread
parallel: build

build:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)