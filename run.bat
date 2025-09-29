@echo off
g++ -std=c++17 -o filemanager mainfunction4.cpp
if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b %errorlevel%
)
echo Compilation successful. Running program...
filemanager.exe
pause
