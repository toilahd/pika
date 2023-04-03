

#include "console.h"

using namespace std;

// Each block will have the size of 7×3 characters,
// outer board margin of 4 characters

// Both dimension should be odd
const int BLOCK_WIDTH = 7;
const int BLOCK_HEIGHT = 3;

const int MARGIN = 4;

void drawBlock(int x, int y, string content){
    int cont = stoi(content);
    
    if (content == "0")
        return;
    
    gotoxy(x, y);
    cout << dye(rainbow[cont % 16], "╭─   ─╮");
    
    gotoxy(x, y + 1);
    cout << setw(BLOCK_WIDTH) << setfill(' ') << dye(rainbow[cont % 16], "");
    
    gotoxy(x + ((int)BLOCK_WIDTH - content.size()) / 2, y + 1);
    cout << dye(rainbow[cont % 16], content);
    
    gotoxy(x, y + 2);
    cout << dye(rainbow[cont % 16], "╰─   ─╯");
}

void boardPrint(int **map, int m, int n){
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            drawBlock(MARGIN + j*(int)BLOCK_WIDTH, MARGIN - 3 +  i*(int)BLOCK_HEIGHT, to_string(map[i][j]));
            
    cout << endl;
}

