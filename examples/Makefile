
#examples makefile

PQS_ROOT ?= ../src/include
CXX      = g++-9
CXXFLAGS = -fmax-errors=1 -std=c++2a -fconcepts -I$(PQS_ROOT) -Wno-stringop-overflow -Wno-literal-suffix
BUILD_DIR = build
BIN_DIR = bin

.PHONY : all test clean

all : test

test  :  $(patsubst %.o,$(BIN_DIR)/%.exe , \
   box_example.o \
   wiki_ex1_base_dimension_exponent.o \
   capacitor_time_curve.o \
   conversion_factor_relation.o \
   pi_as_conversion_factor.o \
   clcpp_response.o \
	feet_and_inches.o \
   feet_and_inches_imp.o \
   fountain.o \
)

$(BIN_DIR)/%.exe : $(BUILD_DIR)/%.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -O3 -o $@ $<
	@echo .......................
	./$@
	@echo ....... OK ............


$(BUILD_DIR)/%.o : %.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -O3 -c $< -o $@


clean :
	rm -rf $(BUILD_DIR)
	rm -rf $(BIN_DIR)
