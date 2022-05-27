@echo off
set editor=%1
if "%editor%" == "" set /p editor= your ProjectEditor: 

premake\premake5.exe %editor%
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)