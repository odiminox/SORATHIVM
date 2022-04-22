@echo off

mkdir ..\build
pushd ..\build
cl /Zi ..\blueprint\blueprint\source\*.cpp  user32.lib gdi32.lib opengl32.lib
popd
