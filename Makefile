CXX := g++
CXXFLAGS := -std=c++20 -Wall
SRC := main.cpp \
	System/*.cpp \
	Operators/*.cpp \
	SelectionMethods/*.cpp \
	MutationMethods/*.cpp \
	CrossoverMethods/*.cpp \
	Environments/*.cpp
INCLUDE := -ISystem \
	-IEnvironments \
	-ISelectionMethods \
	-IMutationMethods \
	-ICrossoverMethods \
	-IOperators \
	-isystem ./Third-Party/Empirical/include/
OUT := evolve

all: O3

slow: CXXFLAGS += -O0
slow: build

O3: CXXFLAGS += -O3 -DNDEBUG
O3: build

debug: CXXFLAGS += -O0 -g
debug: build

parallel: CXXFLAGS += -O3 -fopenmp -pthread
parallel: build

build:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)