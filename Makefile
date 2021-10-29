# Setup the Linux Compiler (In this case GNU GCC)
CC = gcc

# Setup the basic compilation flags
# Warn all, extra and compile for c2x
CFLAGS = -Wall -Wextra -std=c2x

BINARY := gamegirl

all: $(BINARY)
$(BINARY): *.c
ifdef DEBUG
	@echo "🚧 Building..."
ifdef OPCODE_DEBUG
	$(CC) $(CFLAGS) $(SDLFLAGS) $^ -o $@ $(LDFLAGS) -g -DOPCODE_DEBUG
else
	$(CC) $(CFLAGS) $(SDLFLAGS) $^ -o $@ $(LDFLAGS) -g
endif
else
ifdef OPCODE_DEBUG
	$(CC) $(CFLAGS) $(SDLFLAGS) $^ -o $@ $(LDFLAGS) -DOPCODE_DEBUG
else
	$(CC) $(CFLAGS) $(SDLFLAGS) $^ -o $@ $(LDFLAGS)
endif

endif

clean:
	@echo "🧹 Cleaning..."
	-@rm $(BINARY)