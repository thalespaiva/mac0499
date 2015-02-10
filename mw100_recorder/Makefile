CC               := gcc
SRC_FILES        := src/mw100_recorder.c src/cpu_profiler.c
HEAD_FILES       := src/mw100_recorder.h src/cpu_profiler.h
OBJ_FILES		 := build/mw100_recorder.o build/cpu_profiler.o
LIB_FILE		 := lib/mw100_recorder.a
SRC_TOOLS		 := $(wildcard tools/src/*.c)

LD_FLAGS         := -lpthread
CC_FLAGS         := -O2 -std=c99 -Wall

all: $(LIB_FILE) $(OBJ_FILES) tools

build/mw100_recorder.o: src/mw100_recorder.c src/mw100_recorder.h build/cpu_profiler.o
	mkdir -p build
	$(CC) -c $(CC_FLAGS) $(LD_FLAGS) -o $@ $<

build/cpu_profiler.o: src/cpu_profiler.c src/cpu_profiler.h
	mkdir -p build
	$(CC) -c $(CC_FLAGS) $(LD_FLAGS) -o $@ $<

lib/mw100_recorder.a: $(OBJ_FILES)
	mkdir -p lib
	ar -rcs $@ $(OBJ_FILES)

tools: $(SRC_TOOLS) $(LIB_FILE)
	make -C tools/

clean:
	rm -rf build/
	rm -rf lib/
	make -C tools/ clean
