#pragma once

#include <iostream>
#include <Windows.h>

void SetWindowSize(SHORT width, SHORT height);
void color(int color);
void setConsoleFontSize(int size);
void gotoxy(int x, int y);
void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
void DisableCtrButton(bool Close, bool Min, bool Max);
void SetScreenBufferSize(SHORT width, SHORT height);
void ShowConsoleCursor(bool showFlag);