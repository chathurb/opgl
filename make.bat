@echo off

if not exist ".\build\bin" mkdir .\build\bin

cmake -S . -B build/bin

msbuild .\build\bin\opgl.sln

echo running opgl.exe ...
echo:
.\build\bin\Debug\opgl.exe