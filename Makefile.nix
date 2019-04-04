CC=g++
CCFLAGS=-g -Wall
INCLUDE=-I include
SRC_PATH=src
BUILD_PATH=build
BIN_PATH=$(BUILD_PATH)/bin
BIN_NAME=enigma
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
	$(CC) $(CFLAGS) $(OBJ) -o $@ -lcurses

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $^ -o $@
