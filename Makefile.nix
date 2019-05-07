CC=g++
CCFLAGS=-g -Wall -static-libgcc
INCLUDE=-Iinclude -I$(PDCURSES_PATH)
SRC_PATH=src
BUILD_PATH=build
BIN_PATH=$(BUILD_PATH)/bin
BIN_NAME=enigma
ifeq ($(STATIC),1)
	LIB=-Wl,-Bdynamic,-lstdc++,-lc,-lX11,-lXaw,-lxcb,-lXau,-lXt,-lXdmcp,-lXpm,-lXmu,-lXext,-static,-lXCurses
else
	LIB=-Wl,-Bdynamic,$(PDCURSES_PATH)/x11/libXCurses.so
endif
MAKE=make -f Makefile.nix

# source
SRC = $(shell find $(SRC_PATH) -name '*.cpp')

# objects
OBJ = $(SRC:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)

.PHONY: default_target
default_target: dirs
	echo $(MAKE)
	@$(MAKE) all

.PHONY: dirs
dirs:
	@mkdir -p $(dir $(OBJ))
	@mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	@$(RM) -r $(BUILD_PATH)

.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)

$(BIN_PATH)/$(BIN_NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $@ $(LIB)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CC) $(CCFLAGS) $(INCLUDE) -c $^ -o $@
