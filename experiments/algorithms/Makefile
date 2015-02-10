CC               := gcc
SRC_FILES 		 := $(wildcard src/*.c)
OBJ_FILES		 := $(addprefix build/,$(notdir $(SRC_FILES:.c=.o)))
OBJ2BIN		     := $(filter-out build/main.o, $(OBJ_FILES))
BIN_FILES        := $(addprefix bin/,$(notdir $(OBJ2BIN:.o=bench)))

LIB_FILES	     := ../../mw100_recorder/lib/mw100_recorder.a ../../../mw100_recorder/include/mw100_recorder.h
LD_FLAGS         := ../../mw100_recorder/lib/mw100_recorder.a -lpthread -lm
CC_FLAGS         := -Wall -std=c99 -pedantic

all: $(OBJ_FILES) $(BIN_FILES)

build/%.o: src/%.c src/sortbench.h
	mkdir -p build
	$(CC) -c $(CC_FLAGS) -o $@ $<

bin/%bench: build/%.o build/main.o
	mkdir -p bin
	$(CC) $(CC_FLAGS) -o $@ build/main.o $< $(LD_FLAGS)

clean:
	rm -rf bin
	rm -rf build
