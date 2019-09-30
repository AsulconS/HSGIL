# -----------------------------------------------------------------------------------------
# Colors and Styles For Highlighted Commands ----------------------------------------------
# -----------------------------------------------------------------------------------------

NO_COLOR    = \x1b[0m
OK_COLOR    = \x1b[1;32m
ERROR_COLOR = \x1b[1;31m
WARN_COLOR  = \x1b[1;33m
BUILD_COLOR = \x1b[0;34m
OS_COLOR    = \x1b[0;35m
LIB_COLOR   = \x1b[0;36m

LINE_STRING  = @for _ in {0..63}; do printf "-"; done

SKIP_TO_RIGHT = \x1b[A\x1b[31C
OK_STRING     = $(OK_COLOR)$(SKIP_TO_RIGHT)[OK]$(NO_COLOR)
ERROR_STRING  = $(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING   = $(WARN_COLOR)[WARNINGS]$(NO_COLOR)

# Operative System Detection
# -----------------------------------------------------------------------------------------
ifeq ($(OS), Windows_NT)
    C_OS = WINDOWS
else
    ifeq ($(OS), Linux)
        C_OS = LINUX
    endif
endif
# -----------------------------------------------------------------------------------------

OS_STRING    = $(OS_COLOR)[$(C_OS)]$(NO_COLOR)
LIB_STRING   = $(LIB_COLOR)HSGIL - Handy Scalable Graphics Integration Library$(NO_COLOR)
BUILD_PRINT  = $(BUILD_COLOR)Building $@:$(NO_COLOR)

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# C++ Flags and MACROS --------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

CC  = @gcc
CXX = @g++

CXX_STANDARD      = -std=c++11
CXX_WSTD_FLAGS    = -Wall -Wextra
CXX_EXTRA_FLAGS   = -Wshadow -Wnon-virtual-dtor -pedantic
CXX_WARNING_FLAGS = $(CXX_WSTD_FLAGS) $(CXX_EXTRA_FLAGS)

CXX_FLAGS = $(CXX_STANDARD) $(CXX_WARNING_FLAGS)

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Building Macros -------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

STATIC_LIBS = -static-libgcc -static-libstdc++
LINK_FLAGS  = -Wl,-Bstatic -lstdc++ -lpthread

INCLUDE_PATH = -Iinclude -Iexternal/include

EXTERNAL_DEPENDENCIES = glad.o

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Libraries and Building Flags depending on the OS ----------------------------------------
# -----------------------------------------------------------------------------------------

ifeq ($(C_OS), WINDOWS)
    LIBS = -lglfw3 -lgdi32
    SHARED_FILES = hsgil-window.dll
    LIBRARY_PATH = -Lexternal/bin/win_x64
else
    ifeq ($(C_OS), LINUX)
        LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
        SHARED_FILES = hsgil-window.so
        LIBRARY_PATH = -Lexternal/bin/linux_x64
    endif
endif

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Rules -----------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

all: prompt $(EXTERNAL_DEPENDENCIES) $(SHARED_FILES) test trash

# HSGIL Welcome Prompt and OS
# -----------------------------------------------------------------------------------------

prompt:
	$(LINE_STRING)
	@printf "\n$(LIB_STRING)\n"
	$(LINE_STRING)
	@printf "\n$(OS_STRING)\n\n"

# -----------------------------------------------------------------------------------------

# Test Building
# -----------------------------------------------------------------------------------------

test: test.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CXX) $(CXX_FLAGS) test.o $(SHARED_FILES) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o test $(STATIC_LIBS) $(LINK_FLAGS)
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Object Files
# -----------------------------------------------------------------------------------------

test.o: test.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) -c test.cpp
	@printf "$(OK_STRING)\n"

window.o: src/window/window.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC -c src/window/window.cpp
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Shared Files
# -----------------------------------------------------------------------------------------

hsgil-window.dll: window.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CXX) -shared $(CXX_FLAGS) window.o glad.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o hsgil-window.dll $(STATIC_LIBS) $(LINK_FLAGS)
	@printf "$(OK_STRING)\n"

hsgil-window.so: window.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CXX) -shared $(CXX_FLAGS) window.o glad.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o hsgil-window.so $(STATIC_LIBS) $(LINK_FLAGS)
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# External Dependencies
# -----------------------------------------------------------------------------------------

glad.o: external/src/glad/glad.c
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CC) $(INCLUDE_PATH) -fPIC -c external/src/glad/glad.c
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Cleaning Rules
# -----------------------------------------------------------------------------------------

trash:
	@rm -rf *.o

clean:
	@rm -rf *.o test.exe

# -----------------------------------------------------------------------------------------

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------
