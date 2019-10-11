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

MODE          = @
SKIP_TO_RIGHT = \x1b[A\x1b[31C
OK_STRING     = $(OK_COLOR)$(SKIP_TO_RIGHT)[OK]$(NO_COLOR)
ERROR_STRING  = $(ERROR_COLOR)$(SKIP_TO_RIGHT)[ERRORS]$(NO_COLOR)
WARN_STRING   = $(WARN_COLOR)$(SKIP_TO_RIGHT)[WARNINGS]$(NO_COLOR)

ifeq ($(silentOff), true)
    MODE =
    SKIP_TO_RIGHT =
endif

# Operative System Detection
# -----------------------------------------------------------------------------------------
ifeq ($(OS), Windows_NT)
    C_OS = WINDOWS
else
    C_OS = LINUX
endif
# -----------------------------------------------------------------------------------------

OS_STRING      = $(OS_COLOR)[$(C_OS)]$(NO_COLOR)
LIB_STRING     = $(LIB_COLOR)HSGIL - Handy Scalable Graphics Integration Library$(NO_COLOR)
SUCCESS_STRING = $(OK_COLOR)Everything Built Successfully!$(NO_COLOR)
BUILD_PRINT    = $(BUILD_COLOR)Building $@:$(NO_COLOR)

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# C/C++ Flags and MACROS ------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

CC  = gcc
CXX = g++

CC_STANDARD       = -std=c11
CXX_STANDARD      = -std=c++11
CXX_WSTD_FLAGS    = -Wall -Wextra
CXX_EXTRA_FLAGS   = -Wshadow -Wnon-virtual-dtor -pedantic
CXX_WARNING_FLAGS = $(CXX_WSTD_FLAGS) $(CXX_EXTRA_FLAGS)

CC_FLAGS  = $(CC_STANDARD)
CXX_FLAGS = $(CXX_STANDARD) $(CXX_WARNING_FLAGS)

CXX_LIBS  = -static-libgcc -lstdc++ -lpthread

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Building Macros -------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

INCLUDE_PATH = -Iinclude -Iexternal/include

EXTERNAL_DEPENDENCIES = glad.o

WINDOW_OBJECT_FILES   = window.o
GRAPHICS_OBJECT_FILES = shader.o

SHARED_TARG = hsgil-core hsgil-window hsgil-graphics
SHARED_LIBS = -lhsgil-core -lhsgil-window -lhsgil-graphics

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Libraries and Building Flags depending on the OS ----------------------------------------
# -----------------------------------------------------------------------------------------

ifeq ($(C_OS), WINDOWS)
    STATIC_LIBS = -Wl,-Bstatic -lglfw3 -lgdi32 $(CXX_LIBS)
    LIBRARY_PATH = -Lexternal/bin/win_x64 -L.
    EXTENSION = dll
else
    STATIC_LIBS = -Wl,-Bstatic -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl $(CXX_LIBS)
    LIBRARY_PATH = -Lexternal/bin/linux_x64 -L.
    EXTENSION = so
endif

LIBS = $(SHARED_LIBS) $(STATIC_LIBS)

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Rules -----------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

all: prompt $(SHARED_TARG) test trash
	@printf "\n$(SUCCESS_STRING)\n"

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
	$(MODE)$(CXX) $(CXX_FLAGS) test.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o test
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Object Files
# -----------------------------------------------------------------------------------------

test.o: test.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(MODE)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) test.cpp
	@printf "$(OK_STRING)\n"

window.o: src/window/window.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(MODE)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/window/window.cpp
	@printf "$(OK_STRING)\n"

shader.o: src/graphics/shader.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(MODE)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/graphics/shader.cpp
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Shared Files
# -----------------------------------------------------------------------------------------

hsgil-core: $(EXTERNAL_DEPENDENCIES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(MODE)$(CXX) -shared $(CXX_FLAGS) $(EXTERNAL_DEPENDENCIES) $(INCLUDE_PATH) -o hsgil-core.$(EXTENSION)
	@printf "$(OK_STRING)\n"

hsgil-window: $(WINDOW_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(MODE)$(CXX) -shared $(CXX_FLAGS) $(WINDOW_OBJECT_FILES) $(INCLUDE_PATH) $(LIBRARY_PATH) -lhsgil-core $(STATIC_LIBS) -o $@.$(EXTENSION)
	@printf "$(OK_STRING)\n"

hsgil-graphics: $(GRAPHICS_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(MODE)$(CXX) -shared $(CXX_FLAGS) $(GRAPHICS_OBJECT_FILES) $(INCLUDE_PATH) $(LIBRARY_PATH) -lhsgil-core $(STATIC_LIBS) -o $@.$(EXTENSION)
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# External Dependencies
# -----------------------------------------------------------------------------------------

glad.o: external/src/glad/glad.c
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(MODE)$(CC) -c $(CC_FLAGS) $(INCLUDE_PATH) -fPIC external/src/glad/glad.c
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Cleaning Rules
# -----------------------------------------------------------------------------------------

trash:
	@rm -rf *.o

clean:
	@rm -rf *.dll *.so *.o test.exe test

# -----------------------------------------------------------------------------------------

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------
