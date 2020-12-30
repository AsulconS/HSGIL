#********************************************************************************
#*                                                                              *
#* HSGIL - Handy Scalable Graphics Integration Library                          *
#* Copyright (c) 2020 Adrian Bedregal and Gabriela Chipana                      *
#*                                                                              *
#* This software is provided 'as-is', without any express or implied            *
#* warranty. In no event will the authors be held liable for any damages        *
#* arising from the use of this software.                                       *
#*                                                                              *
#* Permission is granted to anyone to use this software for any purpose,        *
#* including commercial applications, and to alter it and redistribute it       *
#* freely, subject to the following restrictions:                               *
#*                                                                              *
#* 1. The origin of this software must not be misrepresented; you must not      *
#*    claim that you wrote the original software. If you use this software      *
#*    in a product, an acknowledgment in the product documentation would be     *
#*    appreciated but is not required.                                          *
#* 2. Altered source versions must be plainly marked as such, and must not be   *
#*    misrepresented as being the original software.                            *
#* 3. This notice may not be removed or altered from any source distribution.   *
#*                                                                              *
#********************************************************************************/

# -----------------------------------------------------------------------------------------
# Colors and Styles For Highlighted Commands ----------------------------------------------
# -----------------------------------------------------------------------------------------

NO_COLOR    = \e[0m
ERROR_COLOR = \e[1;31m
OK_COLOR    = \e[1;32m
WARN_COLOR  = \e[1;33m
MODE_COLOR  = \e[0;33m
BUILD_COLOR = \e[0;34m
OS_COLOR    = \e[0;35m
LIB_COLOR   = \e[0;36m

LINE_STRING  = @for _ in {0..63..1}; do printf "-"; done

VISIBILITY    = @
SKIP_TO_RIGHT = \e[A\e[31C
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
    OS_STRING = $(OS_COLOR)[WINDOWS]$(NO_COLOR)
else
    C_OS = LINUX
    DISTRO = $(shell lsb_release -si)
    OS_STRING = $(OS_COLOR)[LINUX][$(DISTRO)]$(NO_COLOR)
endif
# -----------------------------------------------------------------------------------------

LIB_STRING     = $(LIB_COLOR)HSGIL - Handy Scalable Graphics Integration Library$(NO_COLOR)
SUCCESS_STRING = $(OK_COLOR)Everything Built Successfully!$(NO_COLOR)
BUILD_PRINT    = $(BUILD_COLOR)Building $@:$(NO_COLOR)

TEST_STRING    = $(LIB_COLOR)Building Tests$(NO_COLOR)
SAMPLES_STRING = $(LIB_COLOR)Building Examples$(NO_COLOR)

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# C/C++ Flags and MACROS ------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

AR  = ar
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

ifeq ($(C_OS), WINDOWS)
    CXX_LIBS = -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread
else
    CXX_LIBS =
endif

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Building Macros -------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

INCLUDE_PATH = -Iinclude -Iinclude/HSGIL/external

EXTERNAL_DEPENDENCIES = glad.o

OS_DEPENDENT_FORM_WINDOW =
OS_DEPENDENT_WINDOW_MANAGER =
ifeq ($(C_OS), WINDOWS)
    OS_DEPENDENT_FORM_WINDOW = formWindow.o
    OS_DEPENDENT_WINDOW_MANAGER = win32WindowManager.o
else
    OS_DEPENDENT_WINDOW_MANAGER = linuxWindowManager.o
endif

CORE_OBJECT_FILES     = $(EXTERNAL_DEPENDENCIES) timer.o
MATH_OBJECT_FILES     = mUtils.o vecArithmetic.o
WINDOW_OBJECT_FILES   = renderingWindow.o $(OS_DEPENDENT_FORM_WINDOW) $(OS_DEPENDENT_WINDOW_MANAGER) eventHandler.o inputControl.o inputTrigger.o inputButton.o wUtils.o
GRAPHICS_OBJECT_FILES = shader.o mesh.o model.o gUtils.o

ifeq ($(C_OS), WINDOWS)
    LIB_TARG = win32_hsgil-core win32_hsgil-math win32_hsgil-window win32_hsgil-graphics
else
    LIB_TARG = linux_hsgil-core linux_hsgil-math linux_hsgil-window linux_hsgil-graphics
endif
LIB_ARGS = -lhsgil-core -lhsgil-math -lhsgil-window -lhsgil-graphics

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Libraries and Building Flags depending on the OS ----------------------------------------
# -----------------------------------------------------------------------------------------

ifeq ($(C_OS), WINDOWS)
    STATIC_LIBS = -lgdi32 -lopengl32
    LIBRARY_PATH = -L.
    B_FPIC = -fPIC
    EXTENSION = dll
else
    STATIC_LIBS = -lX11 -lGL -ldl
    LIBRARY_PATH =
    B_FPIC = -fPIC
    EXTENSION = so

    LIB_DIR_LINK = /usr/lib
    ifeq ($(DISTRO), Ubuntu)
        LIB_DIR_LINK = /usr/lib/x86_64-linux-gnu
    else
        ifeq ($(DISTRO), ManjaroLinux)
            LIB_DIR_LINK = /usr/lib
        endif
	endif
endif

LIBS = $(LIB_ARGS) $(STATIC_LIBS)

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------




# -----------------------------------------------------------------------------------------
# Rules -----------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------

all: lprompt $(LIB_TARG) trash
	@printf "\n$(SUCCESS_STRING)\n"

examples: lprompt eprompt example_files trash
	@printf "\n$(SUCCESS_STRING)\n"

test: lprompt tprompt _test trash
	@printf "\n$(SUCCESS_STRING)\n"

full: lprompt $(LIB_TARG) eprompt example_files tprompt _test trash

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
	@printf "\n$(TEST_STRING)\n"
	$(LINE_STRING)
	@printf "\n$(OS_STRING)\n\n"

_test: unit_test.o functional_test.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) unit_test.o $(LIBRARY_PATH) $(LIBS) -lgtest -o run_unit_tests $(CXX_LIBS)
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) functional_test.o $(LIBRARY_PATH) $(LIBS) -lgtest -o run_functional_tests $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Example Building
# -----------------------------------------------------------------------------------------

eprompt:
	$(LINE_STRING)
	@printf "\n$(SAMPLES_STRING)\n"
	$(LINE_STRING)
	@printf "\n$(OS_STRING)\n\n"

example_files: etest ball finn simple cp_libs_to_examples_$(C_OS)
	@printf "$(OK_STRING)\n"

etest: etest.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) etest.o $(LIBRARY_PATH) $(LIBS) -o examples/etest $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

ball: ball.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) ball.o $(LIBRARY_PATH) $(LIBS) -o examples/ball $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

finn: finn.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) finn.o $(LIBRARY_PATH) $(LIBS) -o examples/finn $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

simple: simple.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) $(CXX_FLAGS) simple.o $(LIBRARY_PATH) $(LIBS) -o examples/simple $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Object Files
# -----------------------------------------------------------------------------------------

unit_test.o: src/test/unit_test.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/test/unit_test.cpp
	@printf "$(OK_STRING)\n"

functional_test.o: src/test/functional_test.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/test/functional_test.cpp
	@printf "$(OK_STRING)\n"

etest.o: examples/etest.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) examples/etest.cpp
	@printf "$(OK_STRING)\n"

ball.o: examples/ball.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) examples/ball.cpp
	@printf "$(OK_STRING)\n"

finn.o: examples/finn.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) examples/finn.cpp
	@printf "$(OK_STRING)\n"

simple.o: examples/simple.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) examples/simple.cpp
	@printf "$(OK_STRING)\n"

timer.o: src/core/timer.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/core/timer.cpp
	@printf "$(OK_STRING)\n"

mUtils.o: src/math/mUtils.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/math/mUtils.cpp
	@printf "$(OK_STRING)\n"

vecArithmetic.o: src/math/vecArithmetic.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/math/vecArithmetic.cpp
	@printf "$(OK_STRING)\n"

renderingWindow.o: src/window/renderingWindow.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/window/renderingWindow.cpp
	@printf "$(OK_STRING)\n"

formWindow.o: src/window/formWindow.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/window/formWindow.cpp
	@printf "$(OK_STRING)\n"

win32WindowManager.o: src/window/win32WindowManager.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/window/win32WindowManager.cpp
	@printf "$(OK_STRING)\n"

linuxWindowManager.o: src/window/linuxWindowManager.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/window/linuxWindowManager.cpp
	@printf "$(OK_STRING)\n"

eventHandler.o: src/window/eventHandler.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/window/eventHandler.cpp
	@printf "$(OK_STRING)\n"

inputControl.o: src/window/inputControl.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/window/inputControl.cpp
	@printf "$(OK_STRING)\n"

inputTrigger.o: src/window/inputTrigger.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/window/inputTrigger.cpp
	@printf "$(OK_STRING)\n"

inputButton.o: src/window/inputButton.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/window/inputButton.cpp
	@printf "$(OK_STRING)\n"

wUtils.o: src/window/wUtils.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/window/wUtils.cpp
	@printf "$(OK_STRING)\n"

shader.o: src/graphics/shader.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/graphics/shader.cpp
	@printf "$(OK_STRING)\n"

mesh.o: src/graphics/mesh.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/graphics/mesh.cpp
	@printf "$(OK_STRING)\n"

model.o: src/graphics/model.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/graphics/model.cpp
	@printf "$(OK_STRING)\n"

gUtils.o: src/graphics/gUtils.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) $(B_FPIC) src/graphics/gUtils.cpp
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Shared Files
# -----------------------------------------------------------------------------------------

win32_hsgil-core: $(CORE_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) $(CORE_OBJECT_FILES) -o hsgil-core.$(EXTENSION) $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

win32_hsgil-math: $(MATH_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) $(MATH_OBJECT_FILES) $(LIBRARY_PATH) -lhsgil-core $(STATIC_LIBS) -o hsgil-math.$(EXTENSION) $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

win32_hsgil-window: $(WINDOW_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) $(WINDOW_OBJECT_FILES) $(LIBRARY_PATH) -lhsgil-core -lhsgil-math $(STATIC_LIBS) -o hsgil-window.$(EXTENSION) $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

win32_hsgil-graphics: $(GRAPHICS_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) $(GRAPHICS_OBJECT_FILES) $(LIBRARY_PATH) -lhsgil-core -lhsgil-math $(STATIC_LIBS) -o hsgil-graphics.$(EXTENSION) $(CXX_LIBS)
	@printf "$(OK_STRING)\n"

# Static Files
# -----------------------------------------------------------------------------------------

linux_hsgil-core: $(CORE_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) -Wl,-soname,libhsgil-core.so.1 $(CORE_OBJECT_FILES) -o libhsgil-core.so.1.0
	@mv libhsgil-core.so.1.0 $(LIB_DIR_LINK)
	@ln -sf $(LIB_DIR_LINK)/libhsgil-core.so.1.0 $(LIB_DIR_LINK)/libhsgil-core.so.1
	@ln -sf $(LIB_DIR_LINK)/libhsgil-core.so.1.0 $(LIB_DIR_LINK)/libhsgil-core.so
	@printf "$(OK_STRING)\n"

linux_hsgil-math: $(MATH_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) -Wl,-soname,libhsgil-math.so.1 $(MATH_OBJECT_FILES) -lhsgil-core -o libhsgil-math.so.1.0
	@mv libhsgil-math.so.1.0 $(LIB_DIR_LINK)
	@ln -sf $(LIB_DIR_LINK)/libhsgil-math.so.1.0 $(LIB_DIR_LINK)/libhsgil-math.so.1
	@ln -sf $(LIB_DIR_LINK)/libhsgil-math.so.1.0 $(LIB_DIR_LINK)/libhsgil-math.so
	@printf "$(OK_STRING)\n"

linux_hsgil-window: $(WINDOW_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) -Wl,-soname,libhsgil-window.so.1 $(WINDOW_OBJECT_FILES) -lhsgil-core -lhsgil-math -o libhsgil-window.so.1.0
	@mv libhsgil-window.so.1.0 $(LIB_DIR_LINK)
	@ln -sf $(LIB_DIR_LINK)/libhsgil-window.so.1.0 $(LIB_DIR_LINK)/libhsgil-window.so.1
	@ln -sf $(LIB_DIR_LINK)/libhsgil-window.so.1.0 $(LIB_DIR_LINK)/libhsgil-window.so
	@printf "$(OK_STRING)\n"

linux_hsgil-graphics: $(GRAPHICS_OBJECT_FILES)
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CXX) -shared $(CXX_FLAGS) -Wl,-soname,libhsgil-graphics.so.1 $(GRAPHICS_OBJECT_FILES) -lhsgil-core -lhsgil-math -o libhsgil-graphics.so.1.0
	@mv libhsgil-graphics.so.1.0 $(LIB_DIR_LINK)
	@ln -sf $(LIB_DIR_LINK)/libhsgil-graphics.so.1.0 $(LIB_DIR_LINK)/libhsgil-graphics.so.1
	@ln -sf $(LIB_DIR_LINK)/libhsgil-graphics.so.1.0 $(LIB_DIR_LINK)/libhsgil-graphics.so
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# External Dependencies
# -----------------------------------------------------------------------------------------

glad.o: external/src/glad/glad.c
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(VISIBILITY)$(CC) -c $(CC_FLAGS) $(INCLUDE_PATH) $(B_FPIC) external/src/glad/glad.c
	@printf "$(OK_STRING)\n"

# -----------------------------------------------------------------------------------------

# Miscelaneous Rules
# -----------------------------------------------------------------------------------------

cp_libs_to_examples_WINDOWS:
	@cp -f *.dll examples

cp_libs_to_examples_LINUX:
	@true

# -----------------------------------------------------------------------------------------

# Cleaning Rules
# -----------------------------------------------------------------------------------------

trash:
	@rm -rf *.o

clean:
	@rm -rf *.dll examples/*.dll *.so.1.0 *.o examples/*.exe

# -----------------------------------------------------------------------------------------

# -----------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------
