@echo off
setlocal

rem Set the compiler and flags
set CC=gcc
set CFLAGS=-finput-charset=UTF-8 -fexec-charset=UTF-8
set TARGET=encrypt
set SOURCES=cipher.c caeser.c

rem Compile the program
%CC% %CFLAGS% -o %TARGET% %SOURCES%

rem Check if the compilation was successful
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)

rem Run the program
%TARGET%

endlocal