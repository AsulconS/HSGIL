@ECHO OFF

SET CXX=cl
SET CXX_FLAGS=/EHsc
SET INCLUDE_PATH=/I ".\include" /I ".\include\HSGIL\external"

SET LIBMKR=lib
SET LINKER=link

SET RTMLIBS=user32.lib opengl32.lib gdi32.lib

REM Libary Building:

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/core/timer.cpp

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/math/mUtils.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/math/vecArithmetic.cpp

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/renderingWindow.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/win32WindowManager.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/eventHandler.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/inputControl.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/inputTrigger.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/wmLazyPtr.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/wUtils.cpp

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/graphics/shader.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/graphics/mesh.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/graphics/model.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/graphics/gUtils.cpp

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /c external/src/glad/glad.c

%LIBMKR% /out:hsgil-core.lib timer.obj glad.obj %RTMLIBS%
%LIBMKR% /out:hsgil-math.lib mUtils.obj vecArithmetic.obj
%LIBMKR% /out:hsgil-window.lib renderingWindow.obj win32WindowManager.obj eventHandler.obj inputControl.obj inputTrigger.obj wmLazyPtr.obj wUtils.obj
%LIBMKR% /out:hsgil-graphics.lib shader.obj mesh.obj model.obj gUtils.obj

REM Example Building:

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/etest.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/ball.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/finn.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/simple.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/head.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/volcano.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/doubleWindow.cpp

%CXX% %CXX_FLAGS% etest.obj         hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/etest.exe
%CXX% %CXX_FLAGS% ball.obj          hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/ball.exe
%CXX% %CXX_FLAGS% finn.obj          hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/finn.exe
%CXX% %CXX_FLAGS% simple.obj        hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/simple.exe
%CXX% %CXX_FLAGS% head.obj          hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/head.exe
%CXX% %CXX_FLAGS% volcano.obj       hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/volcano.exe
%CXX% %CXX_FLAGS% doubleWindow.obj  hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib /link /out:examples/doubleWindow.exe

DEL *.obj
