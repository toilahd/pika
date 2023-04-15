// Game's core components: generating levels, tracking time, proggress of players,...
#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <random>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "../console/ui.hpp"
#include "../console/console.h"
#include "dataType.hpp"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


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

