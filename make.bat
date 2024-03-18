@echo off

if not exist ".\build" mkdir .\build\

cmake -S . -B ./build
if %errorlevel% neq 0 exit

cmake --build ./build
if %errorlevel% neq 0 exit

echo running opgl.exe ...
echo:
.\build\src\Debug\opgl.exe

if %errorlevel% neq 0 echo error