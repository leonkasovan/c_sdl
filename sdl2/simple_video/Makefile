# Makefile for SDL 2 sample code

# Compiler and linker
# CC = gcc

# Compiler and linker flags
CFLAGS = -std=c99 -Wall `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

# Source files and the executable
SOURCES = simple_video1.c
EXECUTABLE = simple_video1

# Default target
all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
