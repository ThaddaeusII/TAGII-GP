# Compiler
CXX := g++
BASE_CXXFLAGS := -std=c++20 -Wall

# Directories
SRC_DIR := src
BUILD_DIR_RELEASE := build/release
BUILD_DIR_DEBUG := build/debug

# Output files
OUT_TERMINAL := evolve_terminal
OUT_GUI := evolve_gui
OUT_TERMINAL_DEBUG := evolve_terminal_debug
OUT_GUI_DEBUG := evolve_gui_debug

# Include directories
INCLUDE_SRC := -I$(SRC_DIR)/System \
               -I$(SRC_DIR)/Environments \
               -I$(SRC_DIR)/SelectionMethods \
               -I$(SRC_DIR)/MutationMethods \
               -I$(SRC_DIR)/CrossoverMethods \
               -I$(SRC_DIR)/Operators

INCLUDE_GUI := -I$(SRC_DIR)/GUI \
               -I$(SRC_DIR)/Third-Party/wxMathPlot

INCLUDE_EMPIRICAL := -isystem $(SRC_DIR)/Third-Party/Empirical/include

WX_FLAGS := `wx-config --cxxflags`
WX_LIBS := `wx-config --libs`

# Suppress warnings for mathplot
MATHPLOT_FLAGS := -Wno-deprecated-declarations

# Source files
SRC_SYSTEM := $(wildcard $(SRC_DIR)/System/*.cpp) \
              $(wildcard $(SRC_DIR)/Environments/*.cpp) \
              $(wildcard $(SRC_DIR)/SelectionMethods/*.cpp) \
              $(wildcard $(SRC_DIR)/MutationMethods/*.cpp) \
              $(wildcard $(SRC_DIR)/CrossoverMethods/*.cpp) \
              $(wildcard $(SRC_DIR)/Operators/*.cpp)

SRC_TERMINAL := $(SRC_DIR)/main_terminal.cpp \
                $(SRC_SYSTEM)
SRC_GUI :=      $(SRC_DIR)/main_gui.cpp \
                $(wildcard $(SRC_DIR)/GUI/*.cpp) \
                $(SRC_SYSTEM)

# Build modes
.PHONY: all terminal gui debug_terminal debug_gui clean

all: terminal gui

#
# Release version
#
CXXFLAGS_RELEASE := $(BASE_CXXFLAGS) -O3 -DNDEBUG

OBJ_TERMINAL_RELEASE := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR_RELEASE)/%.o,$(SRC_TERMINAL))
OBJ_GUI_RELEASE :=      $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR_RELEASE)/%.o,$(SRC_GUI)) \
                        $(BUILD_DIR_RELEASE)/Third-Party/mathplot.o

terminal: $(OBJ_TERMINAL_RELEASE)
	$(CXX) $(CXXFLAGS_RELEASE) $(INCLUDE_SRC) $(INCLUDE_EMPIRICAL) $^ -o $(OUT_TERMINAL)

gui: $(OBJ_GUI_RELEASE)
	$(CXX) $(CXXFLAGS_RELEASE) $(INCLUDE_SRC) $(INCLUDE_EMPIRICAL) $(INCLUDE_GUI) $^ $(WX_FLAGS) $(WX_LIBS) -o $(OUT_GUI)

$(BUILD_DIR_RELEASE)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< $(CXXFLAGS_RELEASE) $(INCLUDE_SRC) $(INCLUDE_EMPIRICAL) $(INCLUDE_GUI) $(WX_FLAGS) -o $@

$(BUILD_DIR_RELEASE)/Third-Party/mathplot.o: $(SRC_DIR)/Third-Party/wxMathPlot/mathplot.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< $(CXXFLAGS_RELEASE) $(INCLUDE_SRC) $(INCLUDE_GUI) $(MATHPLOT_FLAGS) $(WX_FLAGS) -o $@

#
# Debug version
#
CXXFLAGS_DEBUG := $(BASE_CXXFLAGS) -O0 -g

OBJ_TERMINAL_DEBUG :=   $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR_DEBUG)/%.o,$(SRC_TERMINAL))
OBJ_GUI_DEBUG :=        $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR_DEBUG)/%.o,$(SRC_GUI)) \
                        $(BUILD_DIR_DEBUG)/Third-Party/mathplot.o

debug: debug_terminal debug_gui

debug_terminal: $(OBJ_TERMINAL_DEBUG)
	$(CXX) $(CXXFLAGS_DEBUG) $(INCLUDE_SRC) $(INCLUDE_EMPIRICAL) $^ -o $(OUT_TERMINAL_DEBUG)

debug_gui: $(OBJ_GUI_DEBUG)
	$(CXX) $(CXXFLAGS_DEBUG) $(INCLUDE_SRC) $(INCLUDE_EMPIRICAL) $(INCLUDE_GUI) $^ $(WX_FLAGS) $(WX_LIBS) -o $(OUT_GUI_DEBUG)

$(BUILD_DIR_DEBUG)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< $(CXXFLAGS_DEBUG) $(INCLUDE_SRC) $(INCLUDE_EMPIRICAL) $(INCLUDE_GUI) $(WX_FLAGS) -o $@

$(BUILD_DIR_DEBUG)/Third-Party/mathplot.o: $(SRC_DIR)/Third-Party/wxMathPlot/mathplot.cpp
	@mkdir -p $(dir $@)
	$(CXX) -c $< $(CXXFLAGS_DEBUG) $(INCLUDE_SRC) $(INCLUDE_GUI) $(MATHPLOT_FLAGS) $(WX_FLAGS) -o $@

#
# Clean object files and executable
#
clean:
	rm -rf build $(OUT_TERMINAL) $(OUT_GUI) $(OUT_TERMINAL_DEBUG) $(OUT_GUI_DEBUG)
