@ECHO off

SET CXX=cl
SET CXX_FLAGS=/EHsc
SET INCLUDE_PATH=/I ".\include" /I ".\include\HSGIL\external"

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c examples/bd/bd.cpp

%CXX% %CXX_FLAGS% bd.obj hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib mysqlcppconn.lib /link /out:examples/bd/bd.exe

clean.bat
