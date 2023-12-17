@echo off

if not exist ".\build" mkdir .\build\

cmake -S . -B ./build

cmake --build ./build

echo running opgl.exe ...
echo:
.\build\src\Debug\opgl.exe