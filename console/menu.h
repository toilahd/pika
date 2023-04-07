#pragma once
#include "console.h"
#include "menu.cpp"
void playGame();
void gameMode();
void leaderBoards();
void credits();
void drawBox(string menu, int x, float y, int z);
void drawMenu();
int  GetRandom(int min, int max);
void drawTitle(int x, int y, string filename);