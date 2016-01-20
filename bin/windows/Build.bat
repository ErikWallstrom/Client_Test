@echo off
g++ ../../src/Main.cpp ../../src/Texture_Handler.cpp ../../src/Core.cpp ../../src/Vector2d.cpp ../../src/Game_Object.cpp ../../src/Player.cpp ../../src/Enemy.cpp -Wall -Wextra -Wfatal-errors -ggdb3 -o Program -std=c++11 -lSDL2 -lSDL2_net -lSDL2_ttf -lSDL2_mixer -lSDL2_image -llua53
echo(
pause
