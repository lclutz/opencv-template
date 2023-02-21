@echo off
cd /D "%~dp0"

echo Setting up OpenCV...
echo    downloading...
curl -fsSL -o opencv.exe https://github.com/opencv/opencv/releases/download/4.7.0/opencv-4.7.0-windows.exe
echo    validating...
call :Validate opencv.exe , 7fab7be68a4ab7f1b70759b0e58d4c4ffc2b8aee72642df6f2dfcc6c161b2465
echo    extracting...
opencv.exe -otmp -y
if exist dependencies\opencv rmdir /s /q dependencies\opencv
mkdir dependencies\opencv
move /y tmp\opencv\build\*.cmake dependencies\opencv\ >nul
move /y tmp\opencv\build\x64 dependencies\opencv\ >nul
move /y tmp\opencv\build\include dependencies\opencv\ >nul
echo    cleanup...
rmdir /s /q tmp
del opencv.exe

echo Done.
exit /b %ERRORLEVEL%


:Validate
setlocal enabledelayedexpansion

set filepath=%~1
set checksum=%~2
set idx=0

for /f %%F in ('certutil -hashfile %filepath% SHA256') do (
    set "out!idx!=%%F"
    set /a idx += 1
)
set filechecksum=%out1%

if /i %checksum%==%filechecksum% (
    echo    validated.
) else (
    echo Checksum validation falied.
    exit 1
)
exit /b 0
