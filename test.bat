@echo off
set editor=%1

if "%editor%" == "" set /p editor=your editor:

echo "%editor%"
pause