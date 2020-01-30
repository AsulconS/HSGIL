# -----------------------------------------------------------------------------------------
# Colors and Styles For Highlighted Commands ----------------------------------------------
# -----------------------------------------------------------------------------------------

NO_COLOR    = \x1b[0m
ERROR_COLOR = \x1b[1;31m
OK_COLOR    = \x1b[1;32m
WARN_COLOR  = \x1b[1;33m
MODE_COLOR  = \x1b[0;33m
BUILD_COLOR = \x1b[0;34m
OS_COLOR    = \x1b[0;35m
LIB_COLOR   = \x1b[0;36m

LINE_STRING  = @for _ in {0..63}; do printf "-"; done

VISIBILITY    = @
SKIP_TO_RIGHT = \x1b[A\x1b[31C
OK_STRING     = $(OK_COLOR)$(SKIP_TO_RIGHT)[OK]$(NO_COLOR)
ERROR_STRING  = $(ERROR_COLOR)$(SKIP_TO_RIGHT)[ERRORS]$(NO_COLOR)
WARN_STRING   = $(WARN_COLOR)$(SKIP_TO_RIGHT)[WARNINGS]$(NO_COLOR)

ifeq ($(VERBOSE), true)
    VISIBILITY =
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

SAMPLES_STRING = $(LIB_COLOR)Building Samples$(NO_COLOR)

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# C/C++ Flags and MACROS ------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

CC  = gcc
CXX = g++

CC_CXX_MODE =
MODE_STRING = $(MODE_COLOR)[RELEASE]$(NO_COLOR)
ifeq ($(MODE), debug)
    CC_CXX_MODE = -g
    MODE_STRING = $(MODE_COLOR)[DEBUG]$(NO_COLOR)
endif

CC_STANDARD       = -std=c11
CXX_STANDARD      = -std=c++11
CXX_WSTD_FLAGS    = -Wall -Wextra
CXX_EXTRA_FLAGS   = -Wshadow -Wnon-virtual-dtor -pedantic
CXX_WARNING_FLAGS = $(CXX_WSTD_FLAGS) $(CXX_EXTRA_FLAGS)

CC_FLAGS   = $(CC_STANDARD) $(CC_CXX_MODE)
CXX_FLAGS  = $(CXX_STANDARD) $(CC_CXX_MODE) $(CXX_WARNING_FLAGS)

CXX_LIBS  = -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Building Macros -------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

INCLUDE_PATH = -Iinclude -Iinclude/HSGIL/external

EXTERNAL_DEPENDENCIES = glad.o

OS_DEPENDENT_WINDOW_MANAGER =
ifeq ($(C_OS), WINDOWS)
    OS_DEPENDENT_WINDOW_MANAGER = win32WindowManager.o
else
    OS_DEPENDENT_WINDOW_MANAGER = linuxWindowManager.o
endif

CORE_OBJECT_FILES     = $(EXTERNAL_DEPENDENCIES) timer.o
MATH_OBJECT_FILES     = mUtils.o
WINDOW_OBJECT_FILES   = window.o $(OS_DEPENDENT_WINDOW_MANAGER) eventHandler.o inputControl.o inputTrigger.o wUtils.o
GRAPHICS_OBJECT_FILES = shader.o mesh.o model.o gUtils.o

SHARED_TARG = hsgil-core hsgil-math hsgil-window hsgil-graphics
SHARED_LIBS = -lhsgil-core -lhsgil-math -lhsgil-window -lhsgil-graphics

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Libraries and Building Flags depending on the OS ----------------------------------------
# -----------------------------------------------------------------------------------------

ifeq ($(C_OS), WINDOWS)
    STATIC_LIBS = -lgdi32 -lopengl32
    LIBRARY_PATH = -L.
    EXTENSION = dll
else
    STATIC_LIBS = -lX11 -lGL -ldl
    LIBRARY_PATH = -L.
    EXTENSION = so
endif

LIBS = $(SHARED_LIBS) $(STATIC_LIBS)

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Rules -----------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

all: lprompt $(SHARED_TARG) trash
	@printf "\n$(SUCCESS_STRING)\n"

samples: tprompt tests trash
	@printf "\n$(SUCCESS_STRING)\n"

full: all samples

# HSGIL Welcome Prompt and OS
# -----------------------------------------------------------------------------------------

lprompt:
	$(LINE_STRING)
	@printf "\n$(LIB_STRING)\n"
	$(LINE_STRING)
	@printf "\n$(OS_STRING)$(MODE_STRING)\n\n"

# -----------------------------------------------------------------------------------------

# Test Building
# -----------------------------------------------------------------------------------------

tprompt:
	$(LINE_STRING)
	@printf "\n$(SAMPLES_STRING)\n"
	$(LINE_STRING)
	@printf "\n$(OS_STRING)\n\n"

tests: test ball finn simple
	@printf "$(OK_STRING)\n"

test: test.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) test.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o test $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

ball: ball.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) ball.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o ball $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

finn: finn.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) finn.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o finn $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

simple: simple.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) simple.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o simple $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Object Files
# -----------------------------------------------------------------------------------------

test.o: test.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) test.cpp
	@printf "$(OK_STRING)\n"

ball.o: ball.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) ball.cpp
	@printf "$(OK_STRING)\n"

finn.o: finn.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) finn.cpp
	@printf "$(OK_STRING)\n"

simple.o: simple.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) simple.cpp
	@printf "$(OK_STRING)\n"

timer.o: src/core/timer.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/core/timer.cpp
	@printf "$(OK_STRING)\n"

mUtils.o: src/math/mUtils.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/math/mUtils.cpp
	@printf "$(OK_STRING)\n"

window.o: src/window/window.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/window/window.cpp
	@printf "$(OK_STRING)\n"

win32WindowManager.o: src/window/win32WindowManager.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/window/win32WindowManager.cpp
	@printf "$(OK_STRING)\n"

linuxWindowManager.o: src/window/linuxWindowManager.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/window/linuxWindowManager.cpp
	@printf "$(OK_STRING)\n"

eventHandler.o: src/window/eventHandler.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/window/eventHandler.cpp
	@printf "$(OK_STRING)\n"

inputControl.o: src/window/inputControl.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/window/inputControl.cpp
	@printf "$(OK_STRING)\n"

inputTrigger.o: src/window/inputTrigger.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/window/inputTrigger.cpp
	@printf "$(OK_STRING)\n"

wUtils.o: src/window/wUtils.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/window/wUtils.cpp
	@printf "$(OK_STRING)\n"

shader.o: src/graphics/shader.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/graphics/shader.cpp
	@printf "$(OK_STRING)\n"

mesh.o: src/graphics/mesh.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/graphics/mesh.cpp
	@printf "$(OK_STRING)\n"

model.o: src/graphics/model.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/graphics/model.cpp
	@printf "$(OK_STRING)\n"

gUtils.o: src/graphics/gUtils.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC src/graphics/gUtils.cpp
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Shared Files
# -----------------------------------------------------------------------------------------

hsgil-core: $(CORE_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) $(CORE_OBJECT_FILES) $(INCLUDE_PATH) -o hsgil-core.$(EXTENSION) $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

hsgil-math: $(MATH_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) $(MATH_OBJECT_FILES) $(INCLUDE_PATH) $(LIBRARY_PATH) -lhsgil-core $(STATIC_LIBS) -o $@.$(EXTENSION) $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

hsgil-window: $(WINDOW_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) $(WINDOW_OBJECT_FILES) $(INCLUDE_PATH) $(LIBRARY_PATH) -lhsgil-core -lhsgil-math $(STATIC_LIBS) -o $@.$(EXTENSION) $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

hsgil-graphics: $(GRAPHICS_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) $(GRAPHICS_OBJECT_FILES) $(INCLUDE_PATH) $(LIBRARY_PATH) -lhsgil-core -lhsgil-math $(STATIC_LIBS) -o $@.$(EXTENSION) $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# External Dependencies
# -----------------------------------------------------------------------------------------

glad.o: external/src/glad/glad.c
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CC) -c $(CC_FLAGS) $(INCLUDE_PATH) -fPIC external/src/glad/glad.c
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Cleaning Rules
# -----------------------------------------------------------------------------------------

trash:
	@rm -rf *.o

clean:
	@rm -rf *.dll *.so *.o *.exe

# -----------------------------------------------------------------------------------------

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------
