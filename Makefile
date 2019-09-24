CC	= gcc
CXX	= g++

CXX_STANDARD		= -std=c++11
CXX_STANDARD_FLAGS	= -Wall -Wextra
CXX_EXTRA_FLAGS		= -Wshadow -Wnon-virtual-dtor -pedantic

CXX_FLAGS 	= $(CXX_STANDARD) $(CXX_STANDARD_FLAGS) $(CXX_EXTRA_FLAGS)

STATIC_CXX	= -static-libgcc -static-libstdc++
LINK_FLAGS	= -Wl,-Bstatic -lstdc++ -lpthread

INCLUDE_PATH	= -Iinclude -Iexternal/include

EXTERNALS	= glad.o

C_OS		:=
LIBS		:=
SHARED		:=
ifeq ($(OS),Windows_NT)
	C_OS = Windows
	LIBS = -lglfw3 -lgdi32
	SHARED = hsgil-window.dll
	LIBRARY_PATH = -Lexternal/win_x64
else
	C_OS = Linux
	LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
	SHARED = hsgil-window.so
	LIBRARY_PATH = -Lexternal/linux_x64
endif

all: os $(EXTERNALS) $(SHARED) test trash

os:
	@echo $(C_OS)

test: test.o
	$(CXX) $(CXX_FLAGS) test.o $(SHARED) $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o test $(STATIC_CXX) $(LINK_FLAGS)

test.o: test.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) -c test.cpp

window.o: src/window/window.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) -fPIC -c src/window/window.cpp

hsgil-window.dll: window.o
	$(CXX) -shared $(CXX_FLAGS) window.o glad.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o hsgil-window.dll $(STATIC_CXX) $(LINK_FLAGS)

hsgil-window.so: window.o
	$(CXX) -shared $(CXX_FLAGS) window.o glad.o $(INCLUDE_PATH) $(LIBRARY_PATH) $(LIBS) -o hsgil-window.so $(STATIC_CXX) $(LINK_FLAGS)

glad.o: external/src/glad/glad.c
	$(CC) $(INCLUDE_PATH) -fPIC -c external/src/glad/glad.c

trash:
	rm -rf *.o

clean:
	rm -rf *.o test.exe
