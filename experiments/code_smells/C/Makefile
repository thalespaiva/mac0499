#EXECUTABLE      :=

CC               := gcc
SRC_FILES        := $(wildcard src/*.c)
BIN_FILES        := $(addprefix bin/,$(notdir $(SRC_FILES:.c=)))

LD_FLAGS         :=
CC_FLAGS         := -O0 -ansi -pedantic

all: $(BIN_FILES)

bin/%: src/%.c
	mkdir -p bin
	$(CC) $(CC_FLAGS) $(LD_FLAGS) -o $@ $<

clean:
	rm -rf bin
