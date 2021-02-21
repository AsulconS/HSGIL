@ECHO off

SET CXX=cl
SET CXX_FLAGS=/EHsc
SET INCLUDE_PATH=/I ".\include" /I ".\include\HSGIL\external"

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/etest.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/ball.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/finn.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/simple.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/head.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/volcano.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/doubleWindow.cpp

%CXX% %CXX_FLAGS% head.obj    hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/head.exe
%CXX% %CXX_FLAGS% test.obj    hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/test.exe
%CXX% %CXX_FLAGS% ball.obj    hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/ball.exe
%CXX% %CXX_FLAGS% finn.obj    hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/finn.exe
%CXX% %CXX_FLAGS% simple.obj  hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/simple.exe
%CXX% %CXX_FLAGS% volcano.obj hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/volcano.exe

clean.bat
