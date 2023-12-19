@echo off

if not exist ".\build" mkdir .\build\

cmake -S . -B ./build
if %errorlevel% neq 0 exit

cmake --build ./build
if %errorlevel% neq 0 exit

echo compiled successfully, running opgl.exe ...
echo:
.\build\src\Debug\opgl.exe