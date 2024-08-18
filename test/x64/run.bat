@echo off

for /f "tokens=1,* delims==" %%a in (local.ini) do (
  set %%a=%%b
)

set CUR_DIR=%~dp0
set CUR_PATH=%PATH%

set PATH=%PATH%;%QtBinPath%;%ProjectPath%\build\msvc2019_64-Qt5.15.2-debug\debug

copy %ProjectPath%\test\x64\build\debug\nppx64test.exe %DominoProgDir%

cd /d %DominoDataDir%
%DominoProgDir%\nppx64test.exe

del %DominoProgDir%\nppx64test.exe
set PATH=%CUR_PATH%

cd /d %CUR_DIR%
