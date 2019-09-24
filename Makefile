CC 	= gcc
CXX = g++

CXX_STANDARD		= -std=c++11
CXX_STANDARD_FLAGS	= -Wall -Wextra
CXX_EXTRA_FLAGS		= -Wshadow -Wnon-virtual-dtor -pedantic

CXX_FLAGS 	= $(CXX_STANDARD) $(CXX_STANDARD_FLAGS) $(CXX_EXTRA_FLAGS)

STATIC_CXX	= -static-libgcc -static-libstdc++
LINK_FLAGS	= -Wl,-Bstatic -lstdc++ -lpthread

INCLUDE 	= -Iinclude
OBJECTS 	= main.o window.o glad.o

C_OS		:=
LIBS		:=
ifeq ($(OS),Windows_NT)
	C_OS = Windows
	LIBS = -lglfw3 -lgdi32
else
	C_OS = Linux
	LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
endif

ifndef ARGS
	ARGS = NOARGS
endif

all: os build trash

os:
	@echo $(C_OS)

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(INCLUDE) $(LIBS) -o main $(STATIC_CXX) $(LINK_FLAGS)

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -D$(ARGS) $(INCLUDE) -c main.cpp

window.o: src/window/window.cpp
	$(CXX) $(CXX_FLAGS) -D$(ARGS) $(INCLUDE) -c src/window/window.cpp

glad.o: glad.c
	$(CC) -c glad.c

trash:
	rm -rf *.o

clean:
	rm -rf *.o main.exe
