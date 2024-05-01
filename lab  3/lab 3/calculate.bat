@echo off
setlocal enabledelayedexpansion

REM Check for the presence of arguments
if "%~1"=="" (
    echo Usage: %0 DIRECTORY_PATH...
    exit /b 1
)

REM Check if the specified directory exists
if not exist "%~1" (
    echo Directory "%~1" not found.
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

for /r "%~1" %%A in (*) do (
    REM Check if the file is not hidden
    attrib "%%A" | find /i "H" >nul && (
        REM If the file is hidden, skip it
        ) || (
        set /a "totalSize+=%%~zA"
    )
)

echo Size of directory "%~1": !totalSize! bytes
exit /b

exit /b 0
