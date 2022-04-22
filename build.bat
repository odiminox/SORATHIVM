@echo off

mkdir ..\build
pushd ..\build
cl /Zi ..\blueprint\blueprint\source\*.cpp  user32.lib
popd
