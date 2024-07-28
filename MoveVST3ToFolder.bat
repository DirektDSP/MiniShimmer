@echo off
setlocal enabledelayedexpansion

:: Get the full path of the current directory
set "FOLDER_PATH=%~dp0"

:: Remove the trailing backslash
set "FOLDER_PATH=%FOLDER_PATH:~0,-1%"

:: Extract the name of the current directory
for %%i in ("%FOLDER_PATH%") do set "PROJECT_NAME=%%~nxi"

:: Define source and destination
set SOURCE="%FOLDER_PATH%\Builds\VisualStudio2022\x64\Release\VST3\!PROJECT_NAME!.vst3\Contents\x86_64-win\!PROJECT_NAME!.vst3"
set DEST="C:\Program Files\Common Files\VST3\DirektDSP\!PROJECT_NAME!.vst3"

echo Copying VST3 build file to VST3 directory...
copy %SOURCE% %DEST%

if %ERRORLEVEL% == 0 (
    echo Success: The file was copied successfully.
) else (
    echo Error: The file could not be copied.
)

pause
endlocal
