# Setup the Linux Compiler (In this case GNU GCC)
CC = gcc

# Setup the basic compilation flags
# Warn all, extra and compile for c2x
CFLAGS := -Wall -Wextra -std=c2x -Iinclude/
SDLFLAGS = `sdl2-config --cflags --libs`
OPENGLFLAGS = -lGL

ifdef OPCODE_DEBUG
CFLAGS += -DOPCODE_DEBUG
endif
ifdef DEBUG
CFLAGS += -g
endif
ifdef FSANITIZE
CFLAGS += -fsanitize=address
endif

BINARY := gamegirl

all: clean $(BINARY)
$(BINARY): *.c
	@echo "🚧 Building..."
	$(CC) $(CFLAGS) $(SDLFLAGS) $^ -o $@ $(SDLFLAGS) $(OPENGLFLAGS) $(LDFLAGS)

clean:
	@echo "🧹 Cleaning..."
	-@rm $(BINARY)
