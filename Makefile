# Usage:
# make			// Full rebuild
# make run      // Full rebuild and execute
# make clean	// Clean all binaries and objects

.PHONY: all run clean

CMP = g++
GFLAGS = -Wall -std=c++20 -Os
LFLAGS = -l ws2_32 -static
CPP = $(wildcard src/*.cpp) $(wildcard src/ID3/v1/*.cpp) $(wildcard src/ID3/v2/*.cpp)

all: linker

run: all
	@clear
	@./tags

linker: ${CPP} ${OBJ}
	@echo "Creating linked program" 
	@${CMP} ${GFLAGS} ${CPP} -o tags ${LFLAGS}
	@echo "Building finished"

clean:
	@echo "Cleaning up build..."
	@rm tags.exe
	@echo "Cleaning up finished"

