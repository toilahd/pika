

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
    
    if (content == "0"){
        gotoxy(x, y);
        string bunchOfSpaces(BLOCK_WIDTH, ' ');
        cout << bunchOfSpaces;
        
        gotoxy(x, y + 1);
        cout << bunchOfSpaces;
        
        gotoxy(x + ((int)BLOCK_WIDTH - content.size()) / 2, y + 1);
        cout << bunchOfSpaces;
        
        gotoxy(x, y + 2);
        cout << bunchOfSpaces;
        return;
    }
        
    
    gotoxy(x, y);
    cout << dye(rainbow[cont % 16], "╭─   ─╮");
    
    gotoxy(x, y + 1);
    string bunchOfSpaces(BLOCK_WIDTH, ' ');
    cout << bunchOfSpaces;
    
    gotoxy(x + ((int)BLOCK_WIDTH - content.size()) / 2, y + 1);
    cout << dye(rainbow[cont % 16], content);
    
    gotoxy(x, y + 2);
    cout << dye(rainbow[cont % 16], "╰─   ─╯");
}

void highlightBlock(int x, int y, string content){
    int cont = stoi(content);
    
    if (content == "0"){
        gotoxy(x, y);
        cout << "╭─   ─╮";
    
        gotoxy(x, y + 1);
        string bunchOfSpaces(BLOCK_WIDTH, ' ');
        cout << bunchOfSpaces;
        
        gotoxy(x, y + 2);
        cout << "╰─   ─╯";
        return;
    }
    
    gotoxy(x, y);
    cout << fill(rainbow[cont % 16], "╭─   ─╮");
    
    gotoxy(x, y + 1);
    string bunchOfSpaces(BLOCK_WIDTH, ' ');
    cout << fill(rainbow[cont % 16], bunchOfSpaces);
    
    gotoxy(x + ((int)BLOCK_WIDTH - content.size()) / 2, y + 1);
    cout << fill(rainbow[cont % 16], content);
    
    gotoxy(x, y + 2);
    cout << fill(rainbow[cont % 16], "╰─   ─╯");
}

void boardPrint(int **map, int m, int n, pair<int, int> highlight){
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (i != highlight.second || j != highlight.first)
                drawBlock(MARGIN + j*(int)BLOCK_WIDTH, MARGIN - 3 +  i*(int)BLOCK_HEIGHT, to_string(map[i][j]));
            else
                highlightBlock(MARGIN + j*(int)BLOCK_WIDTH, MARGIN - 3 +  i*(int)BLOCK_HEIGHT, to_string(map[i][j]));
            
    cout << endl;
}

