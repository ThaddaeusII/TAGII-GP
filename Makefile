CXX := g++
CXXFLAGS := -std=c++20 -Wall

SRC_COMMON := \
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
	-IGUI \
	-isystem ./Third-Party/Empirical/include/

OUT_TERMINAL := evolve_terminal
OUT_GUI := evolve_gui

# Sources for each version
SRC_TERMINAL := main_terminal.cpp \
	$(SRC_COMMON)
SRC_GUI := main_gui.cpp \
	GUI/*.cpp \
	$(SRC_COMMON)

.PHONY: all terminal gui clean

all: terminal gui

# Terminal version
terminal: CXXFLAGS += -O3 -DNDEBUG
terminal:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC_TERMINAL) -o $(OUT_TERMINAL)

# GUI version with wxWidgets flags
gui: CXXFLAGS += `wx-config --cxxflags`
gui: WX_LIBS := `wx-config --libs`
gui:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC_GUI) $(WX_LIBS) -o $(OUT_GUI)

# Optional debug build
debug_terminal: CXXFLAGS += -O0 -g
debug_terminal:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC_TERMINAL) -o $(OUT_TERMINAL)

debug_gui: CXXFLAGS += -O0 -g `wx-config --cxxflags`
debug_gui: WX_LIBS := `wx-config --libs`
debug_gui:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SRC_GUI) $(WX_LIBS) -o $(OUT_GUI)

clean:
	rm -f $(OUT_TERMINAL) $(OUT_GUI)