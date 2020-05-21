@ECHO OFF
@ECHO off

SET CXX=cl
SET CXX_FLAGS=/EHsc
SET INCLUDE_PATH=/I ".\include" /I ".\include\HSGIL\external" /I "C:\Program Files\MySQL\Connector C++ 8.0\include" /I "C:\boost_1_66_0"

%CXX% %CXX_FLAGS% %INCLUDE_PATH% /D HSGIL_STATIC_BUILD /c bd.cpp

%CXX% %CXX_FLAGS% bd.obj hsgil-core.lib hsgil-math.lib hsgil-window.lib hsgil-graphics.lib "C:\Program Files\MySQL\Connector C++ 8.0\lib64\vs14\mysqlcppconn-static.lib" /link /out:bd.exe
