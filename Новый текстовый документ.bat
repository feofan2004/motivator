ECHO OFF
qmake -o Makefile player_lab.pro
make

Start "" "release\player_lab.exe"
set /P v= < version.txt
git add .
git commit -m "New  %v%"
git tag %v%
git push -u origin master
pause
exit