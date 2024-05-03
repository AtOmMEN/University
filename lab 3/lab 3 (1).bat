@echo off
mkdir "PT-23-1\Dovzhenko P.G\batch"
mkdir "PT-23-1\Dovzhenko P.G\batch\Not hidden folder"
mkdir "PT-23-1\Dovzhenko P.G\batch\Hidden folder"
attrib +h "PT-23-1\Dovzhenko P.G\batch\Hidden folder"
xcopy /? > "PT-23-1\Dovzhenko P.G\batch\Not hidden folder\copytext.txt"
xcopy "PT-23-1\Dovzhenko P.G\batch\Not hidden folder\copytext.txt" "PT-23-1\Dovzhenko P.G\batch\Hidden folder\copied_copytext.txt"
