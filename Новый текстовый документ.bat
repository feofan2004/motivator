ECHO OFF
qmake -o Makefile player_lab.pro
make
cd C:\Qt\5.2.1\mingw48_32\bin
windeployqt.exe C:\Users\vlad2_000\Downloads\PPPO\release\player_lab.exe
cd C:\Users\vlad2_000\Downloads\PPPO
Start "" "release\player_lab.exe"
set /P v= < version.txt
set /a v+=1
copy nul version.txt
ECHO %v% >>version.txt
compil32 /cc ins.iss
git add .
git commit -m "New  %v%"
git tag %v%
git push -u origin master
pause
exit