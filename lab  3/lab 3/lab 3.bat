@echo off
mkdir "Not hidden folder"
mkdir "Hidden folder"
attrib +h "Hidden folder"
xcopy /? > "Not hidden folder\copyhelp.txt"
xcopy "Not hidden folder\copyhelp.txt" "Hidden folder\copied_copyhelp.txt"
