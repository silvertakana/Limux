del /s **.sln
del /s **.vcxproj**
rmdir /s /d .vs/
rmdir /s /d /bin

IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)