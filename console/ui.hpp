#pragma once

#include <iomanip>

#include "console.h"
#include "../engine/dataType.hpp"
#include "../ansiart.hpp"

using namespace std;

// Each block will have the size of 7×3 characters,
// outer board margin of 4 characters

// Both dimension should be odd
const int BLOCK_WIDTH = 7;
const int BLOCK_HEIGHT = 3;

const int MARGIN = 4;

void drawHorizonMatch(int x, int y, int x2, int y2, int content = 0){
    if (x > x2){
        swap(x, x2);
        swap(y, y2);
    }
    
    int fromX = MARGIN + x*(int)BLOCK_WIDTH + 4;
    int fromY = MARGIN - 1 +  y*(int)BLOCK_HEIGHT;
    
    int toX = MARGIN + x2*(int)BLOCK_WIDTH + 2;
    int toY = MARGIN - 1 +  y2*(int)BLOCK_HEIGHT;
    
    for (; fromX <= toX; fromX++){
        gotoxy(fromX, fromY);
        // if ()
        cout << dyeAll(rainbow[0]);
        cout << tint(rainbow[content % 15], "─") << COLOR_RESET;
        
        // COORD origin = GetConsoleCaretPos();
        // gotoxy(70, 10);
        // cout << tint(rainbow[content % 15], to_string(content));
        // gotoxy(origin.X,origin.Y);
    }
    
    Sleep(150);
}

void drawVerticalMatch(int x, int y, int x2, int y2, int content = 0){
    if (y > y2){
        swap(x, x2);
        swap(y, y2);
    }
    
    int fromX = MARGIN + x*(int)BLOCK_WIDTH + 3;
    int fromY = MARGIN - 1 +  y*(int)BLOCK_HEIGHT + 1;
    
    int toX = MARGIN + x2*(int)BLOCK_WIDTH + 3;
    int toY = MARGIN - 1 +  y2*(int)BLOCK_HEIGHT - 1;
    
    for (; fromY <= toY; fromY++){
        gotoxy(fromX, fromY);
        // if ()
        cout << dyeAll(rainbow[0]);
        cout << tint(rainbow[content % 15], "│") << COLOR_RESET;
        
        // COORD origin = GetConsoleCaretPos();
        // gotoxy(70, 10);
        // cout << tint(rainbow[content % 15], to_string(content));
        // gotoxy(origin.X,origin.Y);
    }
    
    Sleep(150);
}

void drawUrightMatch(int x, int y, int x2, int y2, int end, int content = 0){
    COORD origin = GetConsoleCaretPos();
    
    if (x > x2){
        swap(x, x2);
        swap(y, y2);
    }
    
    int toX = MARGIN + end*(int)BLOCK_WIDTH + 2;
    
    int fromX = MARGIN + x*(int)BLOCK_WIDTH + 4;
    int fromY = MARGIN - 1 +  y*(int)BLOCK_HEIGHT;
    
    for (; fromX < toX; fromX++){
        gotoxy(fromX, fromY);
        cout << dye(rainbow[0], "─");
    }
    
    int fromX2 = MARGIN + x2*(int)BLOCK_WIDTH + 4;
    int fromY2 = MARGIN - 1 +  y2*(int)BLOCK_HEIGHT;
    
    for (; fromX2 < toX; fromX2++){
        gotoxy(fromX2, fromY2);
        cout << dye(rainbow[0], "─");
    }
    
    for (int i = min(fromY, fromY2); i <= max(fromY, fromY2); i++){
        gotoxy(toX, i);
        if (i == min(fromY, fromY2))
            cout << dye(rainbow[0], "╮");
        else if (i == max(fromY, fromY2))
            cout << dye(rainbow[0], "╯");
        else
            cout << dye(rainbow[0], "│");
    }
    
    gotoxy(origin.X, origin.Y);
}

// Convert string to substrings separated by \n character, based on https://stackoverflow.com/a/15006332
string process(string & s)
{
    string result;
    string::size_type pos = s.find('\n');
    if (pos != string::npos){
        result = s.substr(0, pos);
        s = s.substr(pos + 1);
    }
    else{
        result = s;
        s = "";
    }
    
    return result;
}

// Need more work
void drawBackground(int x, int y, int height = 50, int width = 120){
    return;
    COORD origin = GetConsoleCaretPos();
    
    string fallCopy = fall[0];
    string s = process(fallCopy);
    int count = 0, maxLenght = 0;
    
    while (/* s != "" &&  */count <= height && count < 25){
        s = fall[count];
        gotoxy(x, y + count);
        count++;
        cout << s;
        maxLenght = max(maxLenght, (int)GetConsoleCaretPos().X);
        cout << maxLenght;
        
        // if (maxLenght > width + x){
        //     COORD Current = GetConsoleCaretPos();
        //     gotoxy(width + x, Current.Y);
        //     cout << setw(maxLenght - width) << setfill(' ') << "";
        //     gotoxy(Current.X, Current.Y);
        // }
            
        s = process(fallCopy);
    }
    
    
    gotoxy(origin.X, origin.Y);
}

void drawBlock(int x, int y, string content){
    int cont = stoi(content);
    
    // For board with no image, these lines should be uncommented (Need more work)
    // Drawing blocks with 0 (empty blocks)
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
        
    
    // Drawing normal blocks
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
    
    // Highlighting blocks with 0 (empty blocks)
    // Need more work
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
    
    // Highlighting blocks with 0 (empty blocks)
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
    // Loading username
    char username[30];
    if (name == "" || name.size() > 29)
        strcpy(username, "Player 1");
    else
        strcpy(username, name.c_str());
        
    int **map = userBoard.board;
    int m = userBoard.height, n = userBoard.width;
    pair<int, int> highlight = userBoard.highlight;
    
    // Loop for highlight normal/selected blocks
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (make_pair(j, i) != userBoard.highlight && make_pair(j, i) != userBoard.point1 && make_pair(j, i) != userBoard.point2 && make_pair(j, i) != userBoard.hint1 && make_pair(j, i) != userBoard.hint2)
                drawBlock(MARGIN + j*(int)BLOCK_WIDTH, MARGIN - 2 +  i*(int)BLOCK_HEIGHT, to_string(map[i][j]));
            else
                highlightBlock(MARGIN + j*(int)BLOCK_WIDTH, MARGIN - 2 +  i*(int)BLOCK_HEIGHT, to_string(map[i][j]));
            
    // Ugly a** code for drawing the outer box for the whole board
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

