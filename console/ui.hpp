#include <iomanip>

#include "console.h"
#include "../engine/dataType.hpp"

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
    cout << dye(rainbow[cont % 15], "╭─   ─╮");
    
    gotoxy(x, y + 1);
    string bunchOfSpaces(BLOCK_WIDTH, ' ');
    cout << bunchOfSpaces;
    
    gotoxy(x + ((int)BLOCK_WIDTH - content.size()) / 2, y + 1);
    cout << dye(rainbow[cont % 15], content);
    
    gotoxy(x, y + 2);
    cout << dye(rainbow[cont % 15], "╰─   ─╯");
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
    cout << tint(rainbow[cont % 15], "╭─   ─╮");
    
    gotoxy(x, y + 1);
    string bunchOfSpaces(BLOCK_WIDTH, ' ');
    cout << tint(rainbow[cont % 15], bunchOfSpaces);
    
    gotoxy(x + ((int)BLOCK_WIDTH - content.size()) / 2, y + 1);
    cout << tint(rainbow[cont % 15], content);
    
    gotoxy(x, y + 2);
    cout << tint(rainbow[cont % 15], "╰─   ─╯");
}

void boardPrint(BoardLayout userBoard, string name = ""){
    char username[30];
    if (name == "" || name.size() > 29)
        strcpy(username, "Player 1");
    else
        strcpy(username, name.c_str());
        
    int **map = userBoard.board;
    int m = userBoard.height, n = userBoard.width;
    pair<int, int> highlight = userBoard.highlight;
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (make_pair(j, i) != userBoard.highlight && make_pair(j, i) != userBoard.point1 && make_pair(j, i) != userBoard.point2)
                drawBlock(MARGIN + j*(int)BLOCK_WIDTH, MARGIN - 2 +  i*(int)BLOCK_HEIGHT, to_string(map[i][j]));
            else
                highlightBlock(MARGIN + j*(int)BLOCK_WIDTH, MARGIN - 2 +  i*(int)BLOCK_HEIGHT, to_string(map[i][j]));
            
    COORD oldPos = GetConsoleCaretPos();
    gotoxy(MARGIN - 2, MARGIN - 3);
    cout << "╭─ " << username << " ";
    for (int i = 0; i < BLOCK_WIDTH*n - 2 - strlen(username); i++)
        cout << "─";
    cout << "─╮";
    int i = 0;
    for (; i < BLOCK_HEIGHT*m; i++){
        gotoxy(MARGIN + BLOCK_WIDTH*n + 1, MARGIN - 2 + i);
        cout << "│";
    }
    gotoxy(MARGIN + BLOCK_WIDTH*n + 1, MARGIN - 2 + i);
    cout << "╯";
    int j = BLOCK_WIDTH*n;
    for (; j >= -1; j--){
        gotoxy(MARGIN + j, MARGIN - 2 + i);
        cout << "─";
    }
    gotoxy(MARGIN + j, MARGIN - 2 + i);
    cout << "╰";
    for (; i > 0; i--){
        gotoxy(MARGIN + j, MARGIN - 3 + i);
        cout << "│";
    }
    
    gotoxy(oldPos.X, oldPos.Y);
    cout << endl;
}

