@echo off
echo Building Space Invaders...
c++ -std=c++14 utilities.cpp form.cpp audio.cpp settings.cpp leaderboard.cpp menu.cpp game.cpp -lwinmm -o a.exe
if %errorlevel% equ 0 (
    echo Build successful: a.exe created in src folder
) else (
    echo Build failed with error %errorlevel%
)
pause
