ifdef USE_GCC
# Use GNU's GCC Compiler
CC = gcc
else
# Use LLVM's frontend CLANG
CC = clang
endif

# Setup the Windows Compiler (In this cross-compiling using mingw64)
MINGW64 = x86_64-w64-mingw32-gcc-10-win32

# Setup the basic compilation flags
# Warn all, extra and compile for c2x
CFLAGS := -Wall -Wextra -std=c2x -Iinclude/
SDLFLAGS = `sdl2-config --cflags --libs`
LDFLAGS = -lm

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
endif

ifdef WIN32
BINARY := gamegirl.exe
endif

ifdef UNIX
BINARY := gamegirl
endif

all: clean $(BINARY)

$(BINARY): *.c
	@echo "🚧 Building..."
ifdef UNIX
	$(CC) $(CFLAGS) $(SDLFLAGS) $^ -o $@ $(SDLFLAGS) $(LDFLAGS)
endif
ifdef WIN32
	$(MINGW64) $(CFLAGS) -I$(Win32SDL2Headers) -L$(Win32SDL2Libs) $^ -o $@ -lmingw32 -lSDL2main -lSDL2
endif

clean:
	@echo "🧹 Cleaning..."
	-@rm $(BINARY)
