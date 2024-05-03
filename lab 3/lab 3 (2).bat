@echo off
start "" "Report lab 3.docx"
:waitloop
timeout /t 1 /nobreak >nul
tasklist /fi "imagename eq WINWORD.EXE" 2>nul | find /i "WINWORD.EXE" >nul
if errorlevel 1 (
    echo Word закрыт.
    exit /b
) else (
    goto :waitloop
)
