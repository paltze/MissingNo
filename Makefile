CC := gcc

SRC := $(wildcard src/*.c)

ifeq ($(OS),Windows_NT)
	TARGET := bin/main.exe
	RUN := $(TARGET)
else
	TARGET := bin/main
	RUN := ./$(TARGET)
endif

CFLAGS := -Wall -Wextra -Wpedantic -Iinclude

ifneq ($(filter release,$(MAKECMDGOALS)),)
	CFLAGS += -O2 -DNDEBUG
endif

.PHONY: all run release clean

all:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	$(RUN) $(ROM)

release: all

clean:
	rm -rf bin