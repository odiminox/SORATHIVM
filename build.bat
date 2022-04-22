@echo off

mkdir ..\build
pushd ..\build
cl /Zi ..\blueprint\blueprint\source\*.cpp /GL /Os /GF /Gy /GA /O1 /GX /Os /Og /D NODEFAULTLIB=0 /D _ITERATOR_DEBUG_LEVEL=0 user32.lib gdi32.lib opengl32.lib
popd
