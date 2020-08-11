@ECHO off

SET CXX=cl
SET CXX_FLAGS=/EHsc
SET INCLUDE_PATH=/I ".\include" /I ".\include\HSGIL\external"

SET LIBMKR=lib
SET LINKER=link

SET RTMLIBS=user32.lib opengl32.lib gdi32.lib

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/core/timer.cpp

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/math/mUtils.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/math/vecArithmetic.cpp

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/renderingWindow.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/formWindow.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/win32WindowManager.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/eventHandler.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/inputControl.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/inputTrigger.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/inputButton.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/window/wUtils.cpp

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/graphics/shader.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/graphics/mesh.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/graphics/model.cpp
%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c src/graphics/gUtils.cpp

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /c external/src/glad/glad.c

%LIBMKR% /out:hsgil-core.lib timer.obj glad.obj %RTMLIBS%
%LIBMKR% /out:hsgil-math.lib mUtils.obj vecArithmetic.obj
%LIBMKR% /out:hsgil-window.lib renderingWindow.obj formWindow.obj win32WindowManager.obj eventHandler.obj inputControl.obj inputTrigger.obj inputButton.obj wUtils.obj
%LIBMKR% /out:hsgil-graphics.lib shader.obj mesh.obj model.obj gUtils.obj

examples_build.bat
clean.bat
