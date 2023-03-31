#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "../console.h"

using namespace std;

#define BLOCK_WIDTH 7
#define BLOCK_HEIGHT 3

// Each block will have the size of 7×3 characters,
// outer board margin of 4 characters

void drawBlock(string content, int x, int y){
    gotoxy(x, y);
    cout << "╭─   ─╮";
    
    gotoxy(x, y + 1);
    cout << setw(BLOCK_WIDTH) << left << "";
}