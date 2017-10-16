ECHO OFF
qmake -o Makefile player_lab.pro
make
Start "" "release\player_lab.exe"
set /P vers= < version.txt
git add .
git commit -m "New  %vers%"
git tag %vers%
git push -u origin master
pause
exit