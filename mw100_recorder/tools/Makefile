CC               := gcc
SRC_FILES        := $(wildcard src/*.c)
OBJ_FILES		 := $(addprefix build/,$(notdir $(SRC_FILES:.c=.o)))
LIB_FILE		 := ../lib/mw100_recorder.a
BIN_FILES        := $(addprefix bin/,$(notdir $(OBJ_FILES:.o=)))

LD_FLAGS         := -lpthread
CC_FLAGS         := -O2 -std=c99 -Wall -pedantic

all: $(OBJ_FILES) $(BIN_FILES)

build/%.o: src/%.c
	mkdir -p build
	$(CC) -c $(CC_FLAGS) -o $@ $<

bin/%: build/%.o
	mkdir -p bin
	$(CC) $(CC_FLAGS) $< $(LIB_FILE) $(LD_FLAGS) -o $@

clean:
	rm -rf build/
	rm -rf bin/
