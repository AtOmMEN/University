@echo off
setlocal enabledelayedexpansion

REM Check for the presence of arguments
if "%~1"=="" (
    echo Usage: %0 DIRECTORY_PATH...
    exit /b 1
)

:loop
if "%~1"=="" goto :eof
call :calculateFolderSize "%~1"
shift
goto :loop

REM Function to recursively calculate the size of a directory
:calculateFolderSize
set "totalSize=0"

rem Iterate through each file and subdirectory in the current directory
for /r "%~1" %%A in (*) do (
    REM Check if the item is a file, not hidden and not system
    if not "%%~aA"=="d--hs" (
        set /a "totalSize+=%%~zA"
    )
)

echo Size of directory "%~1": !totalSize! bytes
exit /b
