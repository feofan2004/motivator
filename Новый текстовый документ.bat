<<<<<<< HEAD


REM Here is where you type remark - which will NOT interfere with program / file execution

qmake -o Makefile player_lab.pro
make
Start "" "release\player_lab.exe"
set /P vers= < version.txt
git add -all
git commit -m "New  %vers%"
git tag %vers%
git push -u origin master
=======
@ECHO Off

REM Here is where you type remark - which will NOT interfere with program / file execution

Start "" "C:\Users\vlad2_000\Downloads\build-player_lab-Desktop_Qt_5_2_1_MinGW_32bit-Debug\debug\player_lab.exe"

Exit
>>>>>>> 1cc405a32d2e037764fbcd83d36353b2e055d184
