#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <iomanip>
#include <fstream>
#include "color.hpp"
#include "console.cpp"
#include "cstdlib"

using namespace std;

COORD GetConsoleCaretPos(HANDLE hConsoleOutput);
void SetWindowSize(SHORT width, SHORT height);
void setConsoleFontSize(int size);
void gotoxy(int x, int y);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
void DisableCtrButton(bool Close, bool Min, bool Max);
void SetScreenBufferSize(SHORT width, SHORT height);
void ShowConsoleCursor(bool showFlag);