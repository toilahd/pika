#pragma once

#include <iomanip>

#include "console.h"
#include "../engine/dataType.hpp"
#include "../ansiart.hpp"
#include "../engine/game.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// Each block will have the size of 7×3 characters,
// outer board margin of 4 characters

// Both dimension should be odd
const int BLOCK_WIDTH = 7;
const int BLOCK_HEIGHT = 3;

const int MARGIN = 4;


void boxDrawing(int boxHeight, int boxWidth, int x = -1, int y = -1){
    if (x == -1 && y == -1){
        x = (120 - boxWidth)/2;
        y = (30 - boxHeight)/2;
    }
    
    gotoxy(x, y);
    cout << "╭";
    
    for (int i = 0; i < boxWidth - 2; i++)
        cout << "─";
        
    cout << "╮";
    
    for (int i = 0; i < boxHeight - 2; i++){
        gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y + 1);
        cout << "│";
    }
    
    gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y + 1);
    cout << "╯";
    
    // Sleep(500);
    for (int i = 0; i < boxWidth - 1; i++){
        gotoxy(GetConsoleCaretPos().X - 2, GetConsoleCaretPos().Y);
        cout << "─";
    }
    
    gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y);
    cout << "╰";
    
    for (int i = 0; i < boxHeight - 2; i++){
        gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y - 1);
        cout << "│";
    }
}

void boxEraseLines(int boxHeight, int boxWidth){
    gotoxy((120 - boxWidth)/2, (30 - boxHeight)/2);
    string blankLine(boxWidth, ' ');
    cout << " ";
    
    for (int i = 0; i < boxWidth - 2; i++)
        cout << " ";
        
    cout << " ";
    
    for (int i = 0; i < boxHeight - 2; i++){
        gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y + 1);
        cout << " ";
    }
    
    gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y + 1);
    cout << " ";
    
    // Sleep(500);
    gotoxy(GetConsoleCaretPos().X, GetConsoleCaretPos().Y - 1);
    for (int i = 0; i < boxWidth - 2; i++){
        gotoxy(GetConsoleCaretPos().X - 2, GetConsoleCaretPos().Y);
        cout << " ";
    }
    
    gotoxy(GetConsoleCaretPos().X - 2, GetConsoleCaretPos().Y);
    cout << " ";
    
    for (int i = 0; i < boxHeight - 2; i++){
        gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y - 1);
        cout << " ";
    }
}

void boxErase(int boxHeight, int boxWidth, int x = -1, int y = -1, string color = ""){
    if (x == -1 && y == -1){
        x = (120 - boxWidth)/2;
        y = (30 - boxHeight)/2;
    }
    
    string blankLine(boxWidth, ' ');
    if (color != "")
        blankLine = tint(color, blankLine);
    
    for (int i = 0; i < boxHeight; i++){
        gotoxy(x, y + i);
        cout << blankLine;
    }
}


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

void drawUDownMatch(int x, int y, int x2, int y2, int end, int content = 0){
    COORD origin = GetConsoleCaretPos();
    
    int toY = MARGIN - 1 +  end*(int)BLOCK_HEIGHT;
    
    int fromX = MARGIN + x*(int)BLOCK_WIDTH + 3;
    int fromY = MARGIN - 1 +  y*(int)BLOCK_HEIGHT + 1;
    
    for (; fromY <= toY; fromY++){
        gotoxy(fromX, fromY);
        cout << "│";
    }
    
    int fromX2 = MARGIN + x2*(int)BLOCK_WIDTH + 3;
    int fromY2 = MARGIN - 1 +  y2*(int)BLOCK_HEIGHT + 1;
    
    for (; fromY2 <= toY; fromY2++){
        gotoxy(fromX2, fromY2);
        cout << "│";
    }
    
    for (int a = min(fromX, fromX2); a <= max(fromX, fromX2); a++){
        gotoxy(a, toY);
        if (a == min(fromX, fromX2))
            cout << "╰";
        else if (a == max(fromX, fromX2))
            cout << "╯";
        else
            cout << "─";
    }
    
    gotoxy(origin.X, origin.Y);
    
    Sleep(1000);
}

void drawUUpMatch(int x, int y, int x2, int y2, int end, int content = 0){
    COORD origin = GetConsoleCaretPos();
    
    int toY = MARGIN - 1 +  end*(int)BLOCK_HEIGHT + 1;
    
    int fromX = MARGIN + x*(int)BLOCK_WIDTH + 3;
    int fromY = MARGIN - 1 +  y*(int)BLOCK_HEIGHT - 1;
    
    for (; fromY >= toY; fromY--){
        gotoxy(fromX, fromY);
        cout << "│";
    }
    
    int fromX2 = MARGIN + x2*(int)BLOCK_WIDTH + 3;
    int fromY2 = MARGIN - 1 +  y2*(int)BLOCK_HEIGHT - 1;
    
    for (; fromY2 >= toY; fromY2--){
        gotoxy(fromX2, fromY2);
        cout << "│";
    }
    
    for (int a = min(fromX, fromX2); a <= max(fromX, fromX2); a++){
        gotoxy(a, toY);
        if (a == min(fromX, fromX2))
            cout << "╭";
        else if (a == max(fromX, fromX2))
            cout << "╮";
        else
            cout << "─";
    }
    
    gotoxy(origin.X, origin.Y);
    
    Sleep(1000);
}

void drawUrightMatch(int x, int y, int x2, int y2, int end, int content = 0){
    COORD origin = GetConsoleCaretPos();
    
    if (x > x2){
        swap(x, x2);
        swap(y, y2);
    }
    
    int toX = MARGIN + end*(int)BLOCK_WIDTH + 1;
    
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

void drawULeftMatch(int x, int y, int x2, int y2, int end, int content = 0){
    COORD origin = GetConsoleCaretPos();
    
    if (x < x2){
        swap(x, x2);
        swap(y, y2);
    }
    
    gotoxy(60, 9);
    // cout << "Value of end: " << end;
    
    int toX = MARGIN + end*(int)BLOCK_WIDTH + 3;
    if (end == -1)
        toX+=2;
    
    int fromX = MARGIN + x*(int)BLOCK_WIDTH + 2;
    int fromY = MARGIN - 1 +  y*(int)BLOCK_HEIGHT;
    
    for (; fromX > toX; fromX--){
        gotoxy(fromX, fromY);
        cout << dye(rainbow[0], "─");
    }
    
    // Sleep(2000);
    
    int fromX2 = MARGIN + x2*(int)BLOCK_WIDTH + 2;
    int fromY2 = MARGIN - 1 +  y2*(int)BLOCK_HEIGHT;
    
    for (; fromX2 > toX; fromX2--){
        gotoxy(fromX2, fromY2);
        cout << dye(rainbow[0], "─");
    }
    
    // Sleep(2000);
    
    for (int i = min(fromY, fromY2); i <= max(fromY, fromY2); i++){
        gotoxy(toX, i);
        if (i == min(fromY, fromY2))
            cout << dye(rainbow[0], "╭");
        else if (i == max(fromY, fromY2))
            cout << dye(rainbow[0], "╰");
        else
            cout << dye(rainbow[0], "│");
    }
    
    gotoxy(origin.X, origin.Y);
    
    // Sleep(1500);
}

void drawRightAngleRighSideUpMatch(int x, int y, int x2, int y2, int direction, int content = 0){
    COORD origin = GetConsoleCaretPos();
    
    int fromX = MARGIN + x*(int)BLOCK_WIDTH + 3;
    int fromY = MARGIN - 1 +  y*(int)BLOCK_HEIGHT + 1;
    
    int toX = MARGIN + x2*(int)BLOCK_WIDTH + 3;
    int toY = MARGIN - 1 +  y2*(int)BLOCK_HEIGHT;
    
    for (; fromY <= toY; fromY++){
        gotoxy(fromX, fromY);
        if (fromY != toY)
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "│"/* )) */ << endl;
        else if (direction == 1)
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "╰"/* )) */ << endl;
        else
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "╯"/* )) */ << endl;
    }
    
    fromY--;
    if (direction == 1){
        fromX++;
        for (; fromX < toX - 1; fromX++){
            gotoxy(fromX, fromY);
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "─"/* )) */;
        }
    }
    else{
        fromX--;
        for (; fromX > toX + 1; fromX--){
            gotoxy(fromX, fromY);
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "─"/* )) */;
        }
    }
        
    
    // Sleep(1000);
    
    gotoxy(origin.X, origin.Y);
}

void drawRightAngleUpSideDownMatch(int x, int y, int x2, int y2, int direction, int content = 0){
    COORD origin = GetConsoleCaretPos();
    
    int fromX = MARGIN + x*(int)BLOCK_WIDTH + 3;
    int fromY = MARGIN - 1 +  y*(int)BLOCK_HEIGHT - 1;
    
    int toX = MARGIN + x2*(int)BLOCK_WIDTH + 3;
    int toY = MARGIN - 1 +  y2*(int)BLOCK_HEIGHT;
    
    for (; fromY >= toY; fromY--){
        gotoxy(fromX, fromY);
        if (fromY != toY)
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "│"/* )) */ << endl;
        else if (direction == 1)
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "╭"/* )) */ << endl;
        else
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "╮"/* )) */ << endl;
    }
    
    Sleep(400);
    
    fromY++;
    if (direction == 1){
        fromX++;
        for (; fromX < toX - 1; fromX++){
            gotoxy(fromX, fromY);
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "─"/* )) */;
        }
    }
    else{
        fromX--;
        for (; fromX > toX + 1; fromX--){
            gotoxy(fromX, fromY);
            cout << /* dye(rainbow[0], tint(rainbow[content % 15], */ "─"/* )) */;
        }
    }
        
    
    Sleep(1000);
    
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


void mapPrint(int **map, int m, int n, int mx = -1, int my = -1, int m2x = -1, int m2y = -1){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    
    SetConsoleCursorPosition(hConsole, pos);
    system("cls");
    
    int txtw = 3;
    
    cout << setw(txtw) << " ";
    for (int i = 0; i < m; i++)
        cout << setw(txtw) << i;
        
    cout << endl;
    
    for (int i = 0; i < m; i++){
        SetConsoleTextAttribute(hConsole, 15);
        cout << setw(txtw) << i;
        
        for (int j = 0; j < n; j++){
            SetConsoleTextAttribute(hConsole, *(*(map + i) + j) % 16);
            
            // So -1 se la duong noi 2 vi tri duoc chon
            if ((i == my || i == m2y) && (j == mx || j == m2x))
                cout << setw(txtw) << "[#]";
            else if (*(*(map + i) + j) == 0)
                cout << setw(txtw) << " ";
            else if (*(*(map + i) + j) != -1)
                cout << setw(txtw) << ("[" + to_string(*(*(map + i) + j)) + "]");
                
            else
                cout << setw(txtw) << "[*]";
            
        }    
        cout << endl;
    }
    
}

bool isClear(int **map, int m, int n, int x, int y, int x2, int y2){
    if (y == y2)
        for (int i = min(x, x2) + 1; i < max(x, x2); i++)
            if (map[y][i] != 0)
                return false;
                
    if (x == x2)
        for (int i = min(y, y2) + 1; i < max(y, y2); i++)
            if (map[i][x] != 0)
                return false;
                
    return y == y2 || x == x2;
}

bool pathSearch(int **map, int m, int n, int x, int y, int x2, int y2, bool skip = false){
    
    // Check if the two points are not 0 (while not is debugging mode (skip = false))
    if ((*(*(map + y) + x) == 0 || *(*(map + y2) + x2) == 0) && skip == false)
        return false;
    
    // Check if the 2 points are separated and have the same value
    if ((x == x2 && y == y2) || *(*(map + y) + x) != *(*(map + y2) + x2))
        return false;
        
    // Put your cursor here and ctrl + shift + p -> fold level 2 and 3 to save your brain cells
        
    // Horizontal matching
    if (y == y2){
        bool obstacle = false;
        for (int i = min(x, x2) + 1; i < max(x, x2); i++)
            if (map[y][i] != 0)
                obstacle = true;
                
        if (!obstacle){
            if (!skip){
                drawHorizonMatch(x, y, x2, y2, map[y][x]);
            }
            
            // cout << "Clear path" << endl;
            for (int i = min(x, x2); i <= max(x2, x); i++){
                // mapPrint(map, m, n, x, y, x2, y2);
                // cout << map[y][i] << " ";
                map[y][i] = 0;
            }
            
            // For debugging
            COORD origin = GetConsoleCaretPos();
            gotoxy(70, 16);
            cout << "Hor matching";
            if (!skip)
                Sleep(000);
            gotoxy(70, 16);
            cout << "            ";
            gotoxy(origin.X, origin.Y);
            
            return true;
        }
    }
    
    // Vertical matching
    if (x == x2){
        bool obstacle = false;
        for (int i = min(y, y2) + 1; i < max(y, y2); i++)
            if (map[i][x] != 0)
                obstacle = true;
                
        if (!obstacle){
            if (!skip)
                drawVerticalMatch(x, y, x2, y2, map[y][x]);
            
            // cout << "Clear path" << endl;
            for (int i = min(y, y2); i <= max(y2, y); i++){
                // mapPrint(map, m, n, x, y, x2, y2); // Print map with selected squares
                // cout << map[i][x] << " ";
                map[i][x] = 0;
            }
            
            // For debugging
            COORD origin = GetConsoleCaretPos();
            gotoxy(70, 16);
            cout << "Hor matching";
            if (!skip)
                Sleep(000);
            gotoxy(70, 16);
            cout << "            ";
            gotoxy(origin.X, origin.Y);
            
            return true;
        }
    }
    
    // Right angle matching
    if (x != x2 && y != y2){
        int direction= 0;
        
        // L|⅃
        bool obstacle = false;
        
        if (y > y2){
            swap(y, y2);
            swap(x, x2);
        }
        
        for (int i = y + 1; i <= y2; i++)
            if (map[i][x] != 0){
                obstacle = true;
                break;
            }
            
        if (!obstacle){
            direction = 1;
            if (x2 < x)
                direction = -1;
                
            for (int i = x + direction; i != x2; i+=direction)
                if (map[y2][i] != 0){
                    obstacle = true;
                    break;
            }
        }
        
        if (!obstacle){
            // For debugging
            COORD origin = GetConsoleCaretPos();
            gotoxy(70, 16);
            cout << "L|⅃ matching";
            if (!skip){
                Sleep(000);
                gotoxy(70, 16);
                cout << "            ";
                gotoxy(origin.X, origin.Y);
            }
            
            drawRightAngleRighSideUpMatch(x, y, x2, y2, direction, map[y][x]);
            
            map[y][x] = map[y2][x2] = 0;
            return true;
        }
        
        // Γ|⅂
        obstacle = false;
        if (y < y2){
            swap(y, y2);
            swap(x, x2);
        }
        
        for (int i = y - 1; i >= y2; i--)
            if (map[i][x] != 0){
                // cout << i << ":" << x << map[i][x] << endl;
                obstacle = true;
                break;
            }
            
        if (!obstacle){
            direction = 1;
            if (x2 < x)
                direction = -1;
                
            for (int i = x + direction; i != x2; i+=direction)
                if (map[y2][i] != 0){
                    
                    COORD origin = GetConsoleCaretPos();
                    gotoxy(70, 16);
                    cout << y2 << ":" << i << map[y2][i] << endl;
                    if (!skip)
                        Sleep(000);
                    gotoxy(70, 16);
                    cout << "            ";
                    gotoxy(origin.X, origin.Y);
                    
                    obstacle = true;
                    break;
            }
        }
        
        if (!obstacle){
            // For debugging
            COORD origin = GetConsoleCaretPos();
            gotoxy(70, 16);
            cout << "Γ|⅂ matching";
            if (!skip){
                Sleep(000);
                gotoxy(70, 16);
                cout << "            ";
                gotoxy(origin.X, origin.Y);
                drawRightAngleUpSideDownMatch(x, y, x2, y2, direction, map[y][x]);
            }
            
            
            map[y][x] = map[y2][x2] = 0;
            return true;
        }
    }
    
    // U matching
    if (x != x2 || y  != y2){
        // ⊃
        if (y != y2){
            int i = max(x, x2) + 1;
            
            if (i >= n){
                bool obstacle = false;
                for (int j = x + 1; j < i; j++)
                    if (map[y][j] != 0){
                        obstacle = true;
                        break;
                    }
                    
                for (int j = x2 + 1; j < i; j++)
                    if (map[y2][j] != 0){
                        obstacle = true;
                        break;
                    }
                    
                if (!obstacle){
                    if (!skip)
                        drawUrightMatch(x, y, x2, y2, i, map[y][x]);
                    
                    map[y][x] = map[y2][x2] = 0;
                    
                    // For debugging
                    COORD origin = GetConsoleCaretPos();
                    gotoxy(70, 16);
                    cout << "⊃   matching";
                    if (!skip)
                        Sleep(000);
                    gotoxy(70, 16);
                    cout << "            ";
                    gotoxy(origin.X, origin.Y);
                    
                    return true;
                }
            }
            
            while (i < n && isClear(map, m, n, x, y, i + 1, y) && isClear(map, m, n, x2, y2, i + 1, y2)){
                bool obstacle = false;
                for (int j = min(y, y2); j <= max(y, y2); j++)
                    if (map[j][i] != 0){
                        obstacle = true;
                        break;
                    }
                
                if (obstacle && i < n - 1){
                    i++;
                    continue;
                }
                
                if (obstacle)
                    i++;
                
                if (!skip){
                    drawUrightMatch(x, y, x2, y2, i, map[y][x]);
                }
                
                // For debugging
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 16);
                cout << "⊃matching@" << i;
                if (!skip){
                    Sleep(000);
                    gotoxy(70, 16);
                    cout << "            ";
                    gotoxy(origin.X, origin.Y);
                }
                
                map[y][x] = map[y2][x2] = 0;
                return true;
            }
            
        }
        
        // ⋃
        if (x != x2){
            int i = max(y, y2) + 1;
            
            if (i >= m){
                bool obstacle = false;
                for (int j = y + 1; j < i; j++)
                    if (map[j][x] != 0){
                        obstacle = true;
                        break;
                    }
                    
                for (int j = y2 + 1; j < i; j++)
                    if (map[j][x2] != 0){
                        obstacle = true;
                        break;
                    }
                    
                if (!obstacle){
                    
                    // For debugging
                    COORD origin = GetConsoleCaretPos();
                    gotoxy(70, 16);
                    if (!skip){
                        cout << "⋃   matching";
                        Sleep(000);
                        gotoxy(70, 16);
                        cout << "            ";
                        gotoxy(origin.X, origin.Y);
                        drawUDownMatch(x, y, x2, y2, i, map[y][x]);
                    }
                    
                    map[y][x] = map[y2][x2] = 0;
                    return true;
                }
            }
            
            while (i < m && isClear(map, m, n, x, y, x, i + 1) && isClear(map, m, n, x2, y2, x2, i + 1)){
                bool obstacle = false;
                
                if (!isClear(map, m, n, min(x, x2), i, max(x, x2), i))
                    obstacle = true;
                
                if (obstacle && i < m - 1){
                    i++;
                    continue;
                }
                
                if (obstacle)
                    i++;
                
                // For debugging
                COORD origin = GetConsoleCaretPos();
                
                if (!skip){
                    gotoxy(70, 16);
                    cout << "⋃no matching";
                    Sleep(000);
                    gotoxy(70, 16);
                    cout << "            ";
                    drawUDownMatch(x, y, x2, y2, i, map[y][x]);
                }
                gotoxy(origin.X, origin.Y);
                
                map[y][x] = map[y2][x2] = 0;
                return true;
            }
            
        }
        
        // ⊂ 
        if (y != y2){
            int i = min(x, x2) - 1;
            
            if (i <= -1){
                bool obstacle = false;
                for (int j = x - 1; j > i; j--)
                    if (map[y][j] != 0){
                        obstacle = true;
                        break;
                    }
                    
                for (int j = x2 - 1; j > i; j--)
                    if (map[y2][j] != 0){
                        obstacle = true;
                        break;
                    }
                    
                if (!obstacle){
                    map[y][x] = map[y2][x2] = 0;
                    
                    // For debugging
                    COORD origin = GetConsoleCaretPos();
                    gotoxy(70, 16);
                    if (!skip){
                    cout << "⊂   matching";
                        Sleep(000);
                        gotoxy(70, 16);
                        cout << "            ";
                        gotoxy(origin.X, origin.Y);
                        drawULeftMatch(x, y, x2, y2, i, map[y][x]);
                    }
                    
                    return true;
                }
            }
            
            while (i > -1 && isClear(map, m, n, x, y, i - 1, y) && isClear(map, m, n, x2, y2, i - 1, y2)){
                bool obstacle = false;
                for (int j = min(y, y2); j <= max(y, y2); j++)
                    if (map[j][i] != 0){
                        obstacle = true;
                        break;
                    }
                
                if (obstacle && i > 0){
                    i--;
                    continue;
                }
                
                if (obstacle)
                    i--;
                
                map[y][x] = map[y2][x2] = 0;
                
                // For debugging
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 16);
                if (!skip){
                    cout << "⊂ matching" << obstacle;
                    Sleep(000);
                    gotoxy(70, 16);
                    // cout << "            ";
                    gotoxy(origin.X, origin.Y);
                    drawULeftMatch(x, y, x2, y2, i, map[y][x]);
                }
                
                return true;
            }
            
        }
        
        // ⋂
        if (x != x2){
            int i = min(y, y2) - 1;
            
            if (i <= -1){
                bool obstacle = false;
                for (int j = y - 1; j > i; j--)
                    if (map[j][x] != 0){
                        obstacle = true;
                        break;
                    }
                    
                for (int j = y2 - 1; j > i; j--)
                    if (map[j][x2] != 0){
                        obstacle = true;
                        break;
                    }
                    
                if (!obstacle){
                    
                    // For debugging
                    COORD origin = GetConsoleCaretPos();
                    gotoxy(70, 16);
                    if (!skip){
                        cout << "⋂   matching";
                        Sleep(000);
                        gotoxy(70, 16);
                        cout << "            ";
                        drawUUpMatch(x, y, x2, y2, i, map[y][x]);
                    }
                    
                    gotoxy(origin.X, origin.Y);
                    
                    map[y][x] = map[y2][x2] = 0;
                    return true;
                }
            }
            
            while (i > -1 && isClear(map, m, n, x, y, x, i - 1) && isClear(map, m, n, x2, y2, x2, i - 1)){
                bool obstacle = false;
                    
                for (int j = min(x, x2); j <= max(x, x2); j++)
                    if (map[i][j] != 0){
                        obstacle = true;
                        break;
                    }
                
                if (obstacle && i > 0){
                    i--;
                    continue;
                }
                
                if (obstacle)
                    i--;
                
                
                // For debugging
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 16);
                cout << "⋂   matching";
                if (!skip){
                    Sleep(000);
                    gotoxy(70, 16);
                    cout << "            ";
                    gotoxy(origin.X, origin.Y);
                    drawUUpMatch(x, y, x2, y2, i, map[y][x]);
                }
                
                map[y][x] = map[y2][x2] = 0;
                return true;
            }
            
        }
        
    }
    
    // Zig-zag matching
    if (x != x2 && y != y2){
        if (abs(x - x2) <= 1 && abs(y - y2) <= 1)
            return false;
        
        if (x > x2){
            swap(x, x2);
            swap(y, y2);
        }
        
        for (int i = x + 1; i < x2; i++){
            if (!isClear(map, m, n, i, min(y, y2) - 1, i, max(y, y2) + 1))
                continue;
            
            if (!isClear(map, m, n, x, y, i, y))
                continue;
                
            if (!isClear(map, m, n, x2, y2, i, y2))
                continue;
                
            map[y][x] = map[y2][x2] = 0;
            
            // For debugging
            COORD origin = GetConsoleCaretPos();
            gotoxy(70, 16);
            cout << "Z   matching";
            if (!skip)
                Sleep(000);
            gotoxy(70, 16);
            cout << "            ";
            gotoxy(origin.X, origin.Y);
            
            return true;
        }
        
        if (y > y2){
            swap(x, x2);
            swap(y, y2);
        }
        
        for (int i = y + 1; i < y2; i++){
            if (!isClear(map, m, n, min(x, x2) - 1, i, max(x, x2) + 1, i))
                continue;
            
            if (!isClear(map, m, n, x, y, x, i))
                continue;
                
            if (!isClear(map, m, n, x2, y2, x2, i))
                continue;
                
            map[y][x] = map[y2][x2] = 0;
            
            // For debugging
            COORD origin = GetConsoleCaretPos();
            gotoxy(70, 16);
            cout << "N matching";
            if (!skip)
                Sleep(000);
            gotoxy(70, 16);
            cout << "            ";
            gotoxy(origin.X, origin.Y);
            
            return true;
        }
        
    }
    
    return false;
}

int** generateMap(int m, int n){
    int **map = new int*[m];
    srand(7);
    
    // Fill each block with 0s
    for (int i = 0; i < m; i++){
        map[i] = new int [n];
        
        for (int j = 0; j < n; j++)
            map[i][j] = 0;
    }
    
    // How many pairs of the same number should be in a map
    int count = 3;
        
    for (int i = 1; i <= m*n / (count * 2); i++){
            int x, y, x2, y2;
            
            for (int j = 0; j < count; j++) {
                // Randomly choose 2 points then fill the numbers in
                do {x = rand() % n; y = rand() % m;} while (map[y][x] != 0);
                map[y][x] = i;
                do {x2 = rand() % n; y2 = rand() % m;} while (map[y2][x2] != 0);
                map[y2][x2] = i;
                
                // cout << x << ":" << y << " & " << x2 << ":" << y2 << endl;
                
            }
            // while (!pathSearch(map, m, n, x, y, x2, y2, true));
            
            // For debugging purpose, should be commentted out
            // for (int a = 0; a < m; a++){
            //     for (int b = 0; b < n; b++)
            //         cout << "[" << dye(rainbow[map[a][b] % 15], to_string(map[a][b])) << "]";
            //     cout << endl;
            // }
            // cout << "----------------------------" << endl;
    }
    
    // exit(1);
    
    return map;
}

int selectBlock(){
    int input;
    if (_kbhit())
        input = _getch();
    else
        return 0;
    
    if (input == 224){
        switch (_getch()){
		case KEY_UP:				//lên
			cout << 1 << endl;
            return 1;
            // break;
		case KEY_LEFT:				//trái
			cout << 2 << endl;
            return 2;
            // break;
		case KEY_RIGHT:				//phải
			cout << 4 << endl;
            return 4;
            // break;
		case KEY_DOWN:				//xuống
			cout << 3 << endl;
            return 3;
            // break;
		default:				//nút khác
			cout << 0 << endl;
            return 0;
            // break;
		}
    }
    
    
    return 0;
}

int xSelect = 0, ySelect = 0;

// For refferencing purpose
void oldPlayScreen(int** map, int m, int n){
    // system("cls");
    // ShowConsoleCursor(false);
    pair<int, int> highlight(xSelect, ySelect);
    // boardPrint(map, m, n, highlight);
    // mapPrint(map, m, n);
    
    int move = selectBlock();
    if (move != 0){
        // Sleep(100);
        switch (move){
            case 1:
                ySelect--;
                if (ySelect < 0)
                    ySelect = 0;
                break;
                
            case 2:
                xSelect--;
                if (xSelect < 0)
                    xSelect = 0;
                    break;
                
            case 3:
                ySelect++;
                if (ySelect >= m)
                    ySelect = m - 1;
                    break;
                    
            case 4:
                xSelect++;
                if (xSelect >= n)
                    xSelect = n - 1;
                    break;
        }
    }
    else
        cout << "No Input" << endl;
        
    cout << "Looping" << endl;
    // switch ()
    // char temp;
    // int a, b, c, d;
    // cout << "Nhap toa do 1: ";
    // cin >> a >> b;
    // cout << "Nhap toa do 2: ";
    // cin >> c >> d;
    
    // if (!pathSearch(map, m, n, b, a, d, c)){
    //     cout << "Khong co duong" << endl;
    //     Sleep(800);
    //     // string temp;
    //     // cin >> temp;
    // }
    // else {
    //     cout << "UOOooh" << endl;
    //     Sleep(800);
    //     // string temp;
    //     // cin >> temp;
    // }
    
    cout << endl << endl << endl;
}


// Check if the board is empty
bool isEmpty(BoardLayout a){
    for (int i = 0; i < a.height; i++)
        for (int j = 0; j < a.width; j++)
            if (a.board[i][j] != 0)
                return false;
                
    return true;
}

// Check if the board is solvable
bool isSolvable(BoardLayout &a, bool showHint = false, bool autoHighlight = false){
    for (int i = 0; i < a.height; i++)
        for (int j = 0; j < a.width; j++){
            int value = a.board[i][j];
            
            if (value == 0)
                continue;
            
            for (int b = 0; b < a.height; b++)
                for (int c = 0; c < a.width; c++)
                
                    if (a.board[i][j] != a.board[b][c])
                        continue;
                        
                    else if (pathSearch(a.board, a.height, a.width, j, i, c, b, true)){
                        if (showHint){
                            a.hint1 = make_pair(j, i);
                            a.hint2 = make_pair(c, b);
                        }
                        
                        if (autoHighlight){
                            a.point1 = a.hint1;
                            a.point2 = a.hint2;
                        }
                        
                        a.board[i][j] = a.board[b][c] = value;
                        return true;
                    }
        }
                
    return false;
}

// Rearrange elements of the board based on player's skill
bool rearrange(User &player){
    bool change = false;
    
    if (player.skill == 1){
        for (int i = 0; i < player.getBoard.height; i++){
            int width = player.getBoard.width - 1;
            while (player.getBoard.board[i][width] == 0 && width > 0)
                width--;
                
            for (int j = 0; j < width; j++){
                
                if (player.getBoard.board[i][j] == 0){
                    change = true;
                    
                    for (int k = j; k < width; k++){
                        int temp = player.getBoard.board[i][k];
                        player.getBoard.board[i][k] = player.getBoard.board[i][k + 1];
                        player.getBoard.board[i][k + 1] = temp;
                    }
                    
                    j--;
                    width--;
                }
            }
            
            // for (int a = 0; a < player.getBoard.width; a++)
            //     cout << player.getBoard.board[i][a] << "\t";
                
            // cout << endl;
        }
    }
    
    else if (player.skill == 2){
        for (int i = 0; i < player.getBoard.height; i++){
            int width = 0;
            while (player.getBoard.board[i][width] == 0 && width < player.getBoard.width - 1)
                width++;
                
            for (int j = player.getBoard.width - 1; j > width; j--){
                
                if (player.getBoard.board[i][j] == 0){
                    change = true;
                    
                    for (int k = j; k > width; k--){
                        int temp = player.getBoard.board[i][k];
                        player.getBoard.board[i][k] = player.getBoard.board[i][k - 1];
                        player.getBoard.board[i][k - 1] = temp;
                    }
                    
                    j++;
                    width++;
                }
            }
            
            // for (int a = 0; a < player.getBoard.width; a++)
            //     cout << player.getBoard.board[i][a] << "\t";
                
            // cout << endl;
        }
    }
    
    else if (player.skill == 3){
        for (int i = 0; i < player.getBoard.width; i++){
            int height = player.getBoard.height - 1;
            
            while (player.getBoard.board[height][i] == 0 && height > 0)
                height--;
                
            for (int j = 0; j < height; j++){
                
                if (player.getBoard.board[j][i] == 0){
                    change = true;
                    
                    for (int k = j; k < height; k++){
                        int temp = player.getBoard.board[k][i];
                        player.getBoard.board[k][i] = player.getBoard.board[k + 1][i];
                        player.getBoard.board[k + 1][i] = temp;
                    }
                    
                    j--;
                    height--;
                }
            }
            
            // for (int a = 0; a < player.getBoard.width; a++)
            //     cout << player.getBoard.board[i][a] << "\t";
                
            // cout << endl;
        }
    }
    
    else if (player.skill == 4){
        for (int i = 0; i < player.getBoard.height; i++){
            int height = 0;
            
            while (player.getBoard.board[height][i] == 0 && height < player.getBoard.height - 1)
                height++;
                
            for (int j = player.getBoard.height - 1; j > height; j--){
                
                if (player.getBoard.board[j][i] == 0){
                    change = true;
                    
                    for (int k = j; k > height; k--){
                        int temp = player.getBoard.board[k][i];
                        player.getBoard.board[k][i] = player.getBoard.board[k - 1][i];
                        player.getBoard.board[k - 1][i] = temp;
                    }
                    
                    j++;
                    height++;
                }
            }
            
            // for (int a = 0; a < player.getBoard.width; a++)
            //     cout << player.getBoard.board[i][a] << "\t";
                
            // cout << endl;
        }
    }
    
    return change;
}

void banter(int skill){
    // Construct a new screen with dialog box
    if (skill <= 0 && false){
        gotoxy(50, 15);
        cout << "My oh my, a new kid on the block, trying to kill his useless time";
        gotoxy(0, 0);
    }
}
