CC  = gcc
CXX = g++

CXX_STANDARD        = -std=c++11
CXX_STANDARD_FLAGS  = -Wall -Wextra
CXX_EXTRA_FLAGS     = -Wshadow -Wnon-virtual-dtor -pedantic

CXX_FLAGS = $(CXX_STANDARD) $(CXX_STANDARD_FLAGS) $(CXX_EXTRA_FLAGS)

STATIC_CXX = -static-libgcc -static-libstdc++
LINK_FLAGS = -Wl,-Bstatic -lstdc++ -lpthread

INCLUDE_PATH = -Iinclude -Iexternal/include

EXTERNALS = glad.o

ifeq ($(OS),Windows_NT)
    C_OS = Windows
    LIBS = -lglfw3 -lgdi32
    SHARED = hsgil-window.dll
    LIBRARY_PATH = -Lexternal/bin/win_x64
else
    C_OS = Linux
    LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
    SHARED = hsgil-window.so
    LIBRARY_PATH = -Lexternal/bin/linux_x64
endif

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m
BLUE_COLOR=\e[1;34m

BUILD_PRINT = $(BLUE_COLOR)Building $<\e[0m

OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)[WARNINGS]$(NO_COLOR)

all: os $(EXTERNALS) $(SHARED) test trash

os:
	@printf "\n*************\n"
	@printf "$(OK_COLOR)$(C_OS)\e[0m\n"
	@printf "*************\n\n"

test: test.o
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CXX) $(CXX_FLAGS) test.o $(SHARED) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o test $(STATIC_CXX) $(LINK_FLAGS)
	@printf "$(OK_STRING)\n\n"

test.o: test.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) -c test.cpp
	@printf "$(OK_STRING)\n\n"

window.o: src/window/window.cpp
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC -c src/window/window.cpp
	@printf "$(OK_STRING)\n\n"

hsgil-window.dll: window.o
	@printf "$(BLUE_COLOR)Building hsgil-window.dll\n$(WARN_COLOR)"
	$(CXX) -shared $(CXX_FLAGS) window.o glad.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o hsgil-window.dll $(STATIC_CXX) $(LINK_FLAGS)
	@printf "$(OK_STRING)\n\n"

hsgil-window.so: window.o
	@printf "$(BLUE_COLOR)Building hsgil-window.so\n$(WARN_COLOR)"
	$(CXX) -shared $(CXX_FLAGS) window.o glad.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o hsgil-window.so $(STATIC_CXX) $(LINK_FLAGS)
	@printf "$(OK_STRING)\n\n"

glad.o: external/src/glad/glad.c
	@printf "$(BUILD_PRINT)\n$(WARN_COLOR)"
	$(CC) $(INCLUDE_PATH) -fPIC -c external/src/glad/glad.c
	@printf "$(OK_STRING)\n\n"

trash:
	@rm -rf *.o

clean:
	@rm -rf *.o test.exe
