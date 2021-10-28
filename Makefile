# Setup the Linux Compiler (In this case GNU GCC)
CC = gcc

# Setup the basic compilation flags
# Warn all, extra and compile for c2x
CFLAGS = -Wall -Wextra -std=c2x

BINARY := gamegirl

all: $(BINARY)
$(BINARY): *.c
	@echo "🚧 Building..."
	$(CC) $(CFLAGS) $(SDLFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	@echo "🧹 Cleaning..."
	-@rm $(BINARY)