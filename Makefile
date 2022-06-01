# Setup the Windows Compiler (In this cross-compiling using mingw64)
MINGW64 = x86_64-w64-mingw32-gcc-10-win32

# Setup the basic compilation flags
# Warn all, extra and compile for c2x
CFLAGS := -Wall -Wextra -Iinclude/
SDLFLAGS = `sdl2-config --cflags --libs`
LDFLAGS = -lm

ifdef USE_GCC
# Use GNU's GCC Compiler
CC = gcc
CFLAGS += -DUSE_GCC -DPREC23
else
# Use LLVM's frontend CLANG
CC = clang
endif

ifdef DBG_OPCODE
CFLAGS += -DOPCODE_DEBUG
endif
ifdef DGB
CFLAGS += -g
endif
ifdef ASAN
CFLAGS += -fsanitize=address
endif
ifdef PREC23
CFLAGS += -DPREC23
else
CFLAGS += -std=c2x
endif

ifdef WIN32
BINARY := gamegirl.exe
endif

ifdef UNIX
BINARY := gamegirl
endif

ifdef UNIX
SOURCES := $(shell find . -name '*.c')
OBJECTS = $(SOURCES:.c=.o)
endif

all: clean $(BINARY)

$(BINARY): $(OBJECTS)
	@echo "🚧 Building..."
ifdef UNIX
	@echo " \033[0;36mLD \033[0mgamegirl"
	@$(CC) $(CFLAGS) $(SDLFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)
endif
ifdef WIN32
	$(MINGW64) $(CFLAGS) -I$(Win32SDL2Headers) -L$(Win32SDL2Libs) $^ -o $@ -lmingw32 -lSDL2main -lSDL2
endif

%.o: %.c
	@$(CC) $(CFLAGS) $(SDLCFLAGS) -c $< -o $@
	@echo " \033[0;35mCC\033[0m $<"

clean:
	@echo "🧹 Cleaning..."
	-@rm -rf $(BINARY) ||:
	-@rm -rf $(OBJECTS) ||:
