@echo off
cd /D "%~dp0"

echo Setting up OpenCV...
echo    downloading...
curl -fsSL -o opencv.exe https://github.com/opencv/opencv/releases/download/4.7.0/opencv-4.7.0-windows.exe
echo    extracting...
opencv.exe -otmp -y
if not exist dependencies\opencv mkdir dependencies\opencv
move /y tmp\opencv\build\*.cmake dependencies\opencv\ >nul
move /y tmp\opencv\build\x64 dependencies\opencv\ >nul
move /y tmp\opencv\build\include dependencies\opencv\ >nul
echo    cleanup...
rmdir /s /q tmp
del opencv.exe

echo Done.
