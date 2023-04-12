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

string EXAMPLE_LAYOUT = "         ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮\n \
           A <==> B      \x1b[1mA\x1b[0mAA      B      \033[1mA\033[0m      B      \033[1mA\033[0m      B\n \
        ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯\n \
        ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮       ╭─   ─╮╭─   ─╮╭─   ─╮\n \
           A      B      A      B <====╗      B      A      B\n \
        ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯   ║   ╰─   ─╯╰─   ─╯╰─   ─╯\n \
        ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮   ║   ╭─   ─╮╭─   ─╮╭─   ─╮\n \
           A      B      A      B      ║      B      A      B\n \
        ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯   ║   ╰─   ─╯╰─   ─╯╰─   ─╯\n \
        ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮   ║          ╭─   ─╮╭─   ─╮\n \
           A      B      A      B      ╚===========> A      B\n \
        ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯              ╰─   ─╯╰─   ─╯\n <=";
// ━━━ ╾── ╰─ ── ╰- ---- 
string testingLigature = " \
 <----╮      B     \n \
 ─╯   │   ╰─   ─╯╰─\n \
 ─╮   │   ╭─   ─╮╭─\n \
      │      B     \n \
 ─╯   │   ╰─   ─╯╰─\n \
 ─╮   │          ╭─\n \
      ╰----------> \n \
";

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
            int direction = 1;
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
            if (!skip)
                Sleep(000);
            gotoxy(70, 16);
            cout << "            ";
            gotoxy(origin.X, origin.Y);
            
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
            int direction = 1;
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
            if (!skip)
                Sleep(000);
            gotoxy(70, 16);
            cout << "            ";
            gotoxy(origin.X, origin.Y);
            
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
                
                if (!skip)
                    drawUrightMatch(x, y, x2, y2, i, map[y][x]);
                
                // For debugging
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 16);
                cout << "⊃matching@" << i;
                if (!skip)
                    Sleep(000);
                gotoxy(70, 16);
                cout << "            ";
                gotoxy(origin.X, origin.Y);
                
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
                    map[y][x] = map[y2][x2] = 0;
                    
                    // For debugging
                    COORD origin = GetConsoleCaretPos();
                    gotoxy(70, 16);
                    cout << "⋃   matching";
                    if (!skip)
                        Sleep(000);
                    gotoxy(70, 16);
                    cout << "            ";
                    gotoxy(origin.X, origin.Y);
                    
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
                
                // For debugging
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 16);
                cout << "⋃no matching";
                if (!skip)
                    Sleep(000);
                gotoxy(70, 16);
                cout << "            ";
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
                    cout << "⊂   matching";
                    if (!skip)
                        Sleep(000);
                    gotoxy(70, 16);
                    cout << "            ";
                    gotoxy(origin.X, origin.Y);
                    
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
                
                map[y][x] = map[y2][x2] = 0;
                
                // For debugging
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 16);
                cout << "⊂   matching";
                if (!skip)
                    Sleep(000);
                gotoxy(70, 16);
                cout << "            ";
                gotoxy(origin.X, origin.Y);
                
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
                    map[y][x] = map[y2][x2] = 0;
                    
                    // For debugging
                    COORD origin = GetConsoleCaretPos();
                    gotoxy(70, 16);
                    cout << "⋂   matching";
                    if (!skip)
                        Sleep(000);
                    gotoxy(70, 16);
                    cout << "            ";
                    gotoxy(origin.X, origin.Y);
                    
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
                
                map[y][x] = map[y2][x2] = 0;
                
                // For debugging
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 16);
                cout << "⋂   matching";
                if (!skip)
                    Sleep(000);
                gotoxy(70, 16);
                cout << "            ";
                gotoxy(origin.X, origin.Y);
                
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
                
                cout << x << ":" << y << " & " << x2 << ":" << y2 << endl;
                
            }
            // while (!pathSearch(map, m, n, x, y, x2, y2, true));
            
            // For debugging purpose, should be commentted out
            for (int a = 0; a < m; a++){
                for (int b = 0; b < n; b++)
                    cout << "[" << dye(rainbow[map[a][b] % 15], to_string(map[a][b])) << "]";
                cout << endl;
            }
            cout << "----------------------------" << endl;
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

void boxDrawing(int boxHeight, int boxWidth){
    gotoxy((120 - boxWidth)/2, (30 - boxHeight)/2);
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
    for (int i = 0; i < boxWidth; i++){
        gotoxy(GetConsoleCaretPos().X - 2, GetConsoleCaretPos().Y);
        cout << "─";
    }
    
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

void boxErase(int boxHeight, int boxWidth){
    string blankLine(boxWidth, ' ');
    for (int i = 0; i < boxHeight; i++){
        gotoxy((120 - boxWidth)/2, (30 - boxHeight)/2 + i);
        cout << blankLine;
    }
}

// Need more work
void infoScreen(){
    
}

void pauseScreen(time_t &startTime, User &player) {
    time_t pauseTime = time(NULL);
    
    COORD origin = GetConsoleCaretPos();
    int pauseBoxWidth = 100;
    int pauseBoxHeight = 25;
    
    string blankLine(pauseBoxWidth, ' ');
    string upperEdge;
    for (int i = 0; i < pauseBoxWidth - 2; i++)
        upperEdge += "─";
        
    for (int i = 0; i < pauseBoxHeight; i++){
        gotoxy((120 - pauseBoxWidth)/2, (30 - pauseBoxHeight)/2 + i);
        cout << blankLine;
    }
    
    gotoxy((120 - pauseBoxWidth)/2, (30 - pauseBoxHeight)/2);
    cout << "╭";
    
    cout << upperEdge;
        
    cout << "╮";
    
    for (int i = 0; i < pauseBoxHeight - 2; i++){
        gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y + 1);
        cout << "│";
    }
    
    
    gotoxy((120 - pauseBoxWidth)/2, (30 - pauseBoxHeight)/2 + pauseBoxHeight - 2);
    cout << "╰";
    cout << upperEdge;
    cout << "╯";
    
    // Sleep(5000);
    
    gotoxy((120 - pauseBoxWidth)/2 + 1, (30 - pauseBoxHeight)/2);
    for (int i = 0; i < pauseBoxHeight - 3; i++){
        gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y + 1);
        cout << "│";
    }
    // Sleep(3000);
    
    while (1){
        gotoxy((120 - pauseBoxWidth)/2 + 1, (30 - pauseBoxHeight)/2);
        cout << " Break time! ";
        // Some reserved space for code to navigate Pause screen items but repressing the ESC key will break out the pause loop
        
        gotoxy((120 - pauseBoxWidth)/2 + 3, (30 - pauseBoxHeight)/2 + 2);
        cout << "ESC for Continuing the game";
        gotoxy((120 - pauseBoxWidth)/2 + 3, (30 - pauseBoxHeight)/2 + 3);
        cout << "Q to Quit the current game";
        
        // A blocking input
        int key = _getch();
        COORD origin = GetConsoleCaretPos();
        gotoxy(70, 2);
        cout << key;
        gotoxy(origin.X, origin.Y);
        
        // If ESC -> Continue the game
        if (key == 27){
            startTime += time(NULL) - pauseTime;
            gotoxy((120 - pauseBoxWidth)/2 + 1, (30 - pauseBoxHeight)/2);
            cout << "Continuing the game...";
            
            boxErase(pauseBoxHeight, pauseBoxWidth);
            // Sleep(4000);
            boardPrint(player.getBoard, "Level: " + to_string(player.skill));
            break;
        }
        // If Q key -> Save player info and exit the game
        else if (key == 113){
            string name = "";
            {
                gotoxy(70, 4);
                if (name != "")
                    cout << "Retry: your name must not be longer than 49 charactes";
                gotoxy(70, 5);
                cout << "Your name: ";
                cin >> name;
            } while (name.size() > 49);
            
            string pass = "";
            {
                gotoxy(70, 6);
                if (pass != "")
                    cout << "Retry: your password must not be longer than 49 charactes";
                else
                    cout << "                                                         ";
                gotoxy(70, 7);
                cout << "Your password: ";
                cin >> pass;
            } while (pass.size() > 49);
            
            savefile *info = new savefile;
            (*info).mask = 'Q';
            strcpy((*info).name, name.c_str());
            strcpy((*info).password, pass.c_str());
            
            for (int i = 0; i < 5; i++){
                if ((*info).state[i].p == 0 && (*info).state[i].q == 0){
                    (*info).state[i].p = player.getBoard.height;
                    (*info).state[i].q = player.getBoard.width;
                    
                    (*info).state[i].p_ = player.getBoard.highlight.second;
                    (*info).state[i].q_ = player.getBoard.highlight.first;
                    
                    int count = 0;
                    for (int a = 0; a < player.getBoard.height; a++){
                        gotoxy(70, 7 + a);
                        for (int b = 0; b < player.getBoard.width; b++){
                            (*info).state[i].board[count] = (char)(player.getBoard.board[a][b] + 63);
                            cout << (*info).state[i].board[count] << " ";
                            count++;
                        }
                    }
                    
                    break;
                }
            }
            
            ofstream out("savedFile.bin", ios::binary);
            
            out.write((char*)info, sizeof(savefile));
            out.close();
            
            COORD origin = GetConsoleCaretPos();
            gotoxy(70, 2);
            cout << "Exiting the game...";
            gotoxy(origin.X, origin.Y);
            
            exit(1);
        }
    }
            
}

void playScreen(User player = User{"", "", 0}){
    // Initialize new user / load user info from saved file
    system("cls");
    ShowConsoleCursor(false);
    int timeLength = 300;
    
    
    // If isLogged is false -> new user -> create map and default username
    if (player.isLogged == false){
        string stockName = "Player 1";
        strcpy(player.name, stockName.c_str());
        player.getBoard.board = generateMap(9, 9);
        player.getBoard.height = 9;
        player.getBoard.width = 9;
    }
    
    
    bool isWon = false;
    while (1){
        // Game starting point. All levels only goes through these lines once
        
        // If the player has won in the previous game -> make new map + increase skill (level)
        if (isWon){
            player.skill++;
            isWon = false;
            player.getBoard.board = generateMap(9, 9);
            player.getBoard.height = 9;
            player.getBoard.width = 9;
        }
        
        // Check for player's skill level, then rearrange board accordingly
        rearrange(player);
        
        
        // Check if the board is solvable then load the result to solveState
        bool solveState = isSolvable(player.getBoard);
        
        // Small talk to the player (Coming soon)
        banter(player.skill);
        
        // Time the level started
        time_t startTime = time(NULL);
        
        // Draw background then overwrite it with the board
        drawBackground(MARGIN - 2, MARGIN - 3, BLOCK_HEIGHT*player.getBoard.height + 4, BLOCK_WIDTH*player.getBoard.width + 4);
        boardPrint(player.getBoard, "Level: " + to_string(player.skill));
        
        
        while (1){
            // Check to see if the board need to be arrange based on skill or the board is already arraged
            if (rearrange(player))
                boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                
            int key = -1;
            
            // A non blocking input (If there is no input -> skip and go to next line)
            if (_kbhit()){
                key = _getch();
                // cout << "Key: " << key << endl;
            }
            
            // If ESC -> pauseScreen
            if (key == 27){
                pauseScreen(startTime, player);
            }
            
            // If Space key -> select the points
            else if (key == 32){
                // Fill up point1 and point2
                if (player.getBoard.point1 == make_pair(-1, -1)){
                    player.getBoard.point1 = player.getBoard.highlight;
                }
                else if (player.getBoard.point2 == make_pair(-1, -1)){
                    player.getBoard.point2 = player.getBoard.highlight;
                }
                
                // pathSearch() activated when 2 points were filled
                if (player.getBoard.point1 != make_pair(-1, -1) && player.getBoard.point2 != make_pair(-1, -1)){
                    cout << "Search for path" << endl;
                    if (pathSearch(player.getBoard.board, player.getBoard.height, player.getBoard.width, player.getBoard.point1.first, player.getBoard.point1.second, player.getBoard.point2.first, player.getBoard.point2.second)){
                        boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                        // Sleep(200);
                        // Reset 2 highlighted points
                        player.getBoard.point1 = player.getBoard.point2 = make_pair(-1, -1);
                        player.getBoard.hint1 = player.getBoard.hint2 = make_pair(-1, -1);
                        
                        drawBackground(MARGIN - 2, MARGIN - 3, BLOCK_HEIGHT*player.getBoard.height + 4, BLOCK_WIDTH*player.getBoard.width + 4);
                        
                        boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                    }
                    else {
                        cout << "No path found";
                        // Sleep(200);
                        player.getBoard.point1 = player.getBoard.point2 = make_pair(-1, -1);
                        player.getBoard.hint1 = player.getBoard.hint2 = make_pair(-1, -1);
                        boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                    }
                    
                }
                
                solveState = isSolvable(player.getBoard);
                
            }
            
            // If H -> Hint
            else if (key == 'h'){
                isSolvable(player.getBoard, true, true);
                boardPrint(player.getBoard, "Level: " + to_string(player.skill));
            }
            
            // If move -> refresh the actual map
            else if (key == 0 || key == 224){
                key = _getch();
                
                // Arrow keys for navigating the board
                switch (key) {
                    case 72: 
                        // if ()
                        //     drawBackground(MARGIN - 2, MARGIN - 3, BLOCK_HEIGHT*player.getBoard.height + 4, BLOCK_WIDTH*player.getBoard.width + 4);
                        
                        player.getBoard.highlight.second--;
                        if (player.getBoard.highlight.second < 0){
                            player.getBoard.highlight.second = 0;
                            break;
                        }
                        cout << "Up arrow" << endl;
                        break;
                    case 80:
                        player.getBoard.highlight.second++;
                        if (player.getBoard.highlight.second >= player.getBoard.height){
                            player.getBoard.highlight.second = player.getBoard.height - 1;
                            break;
                        }
                        cout << "Down arrow" << endl; 
                        break;
                    case 75: 
                        player.getBoard.highlight.first--;
                        if (player.getBoard.highlight.first < 0){
                            player.getBoard.highlight.first = 0;
                            break;
                        }
                        cout << "Left arrow" << endl; 
                        break;
                    case 77: 
                        player.getBoard.highlight.first++;
                        if (player.getBoard.highlight.first >= player.getBoard.width){
                            player.getBoard.highlight.first = player.getBoard.width - 1;
                            break;
                        }
                        cout << "Right arrow" << endl; 
                        break;
                    case 71: cout << "Home" << endl; break;
                    case 79: cout << "End" << endl; break;
                    case 73: cout << "Page up" << endl; break;
                    case 81: cout << "Page down" << endl; break;
                    case 82: cout << "Insert" << endl; break;
                    case 83: cout << "Delete" << endl; break;
                    default: cout << "Unknown extended key" << endl; break;
                }
                
                drawBackground(MARGIN - 2, MARGIN - 3, BLOCK_HEIGHT*player.getBoard.height + 4, BLOCK_WIDTH*player.getBoard.width + 4);
                boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                solveState = isSolvable(player.getBoard);
            }
                
            // If did not move, do not refresh the map but only refresh the time, stats element (need more work),...
            COORD origin = GetConsoleCaretPos();
            gotoxy(70, 2);
            cout << setw(3) << setfill(' ') << timeLength - (time(NULL) - startTime);
            gotoxy(origin.X, origin.Y);
            
            // If board empty, time out or unsolvable -> go to endscreen
            if (time(NULL) - startTime >= timeLength || isEmpty(player.getBoard) || !solveState){
                while (1) {
                    if (isWon || (time(NULL) - startTime < timeLength && (isEmpty(player.getBoard) || !solveState))) {
                        isWon = true;
                        COORD origin = GetConsoleCaretPos();
                        gotoxy(70, 2);
                        cout << "You won";
                        gotoxy(70, 3);
                        cout << "Press Space for next level";
                        gotoxy(origin.X, origin.Y);
                        
                        int key = _getch();
                        
                        origin = GetConsoleCaretPos();
                        gotoxy(70, 4);
                        cout << key;
                        gotoxy(origin.X, origin.Y);
                        
                        if (key == 32)
                            break;
                    }
                    else {
                        COORD origin = GetConsoleCaretPos();
                        gotoxy(70, 2);
                        cout << "Lmao, look at him, he can't count";
                        gotoxy(origin.X, origin.Y);
                    }
                    
                }
                
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 4);
                cout << "Out of while loop";
                gotoxy(origin.X, origin.Y);
            }
                
            // If won -> break out while loop to go to next level
            if (isWon){
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 5);
                cout << "Break out of while loop";
                Sleep(300);
                gotoxy(origin.X, origin.Y);
                system("cls");
                break;
            }
        }
    }
}

int userInput(string &str, int size = 30){
    
    int key = -1;
    
    if (_kbhit()){
        
        key = _getch();
        
        if (('a' <= key && key <= 'z') || ('A' <= key && key <= 'Z') || key == ' '){
            if (str.size() == size)
                return 0;
            
            str += (char)key;
            
            return 1;
        }
        
        if (key == 13){
            if (str.size() == size)
                return 0;
                
            return 2;
        }
        
        if (key == 8){
            str = str.substr(0, str.size() - 1);
            return -1;
        }
        
    }
    
    return 0;
}

void loginScreen(){
    system("cls");
    ShowConsoleCursor(true);
    
    gotoxy(4, 1);
    cout << "Login page";
    
    string name = "";
    string pass = "";
    string blankLine(50, ' ');
    
    gotoxy(4, 2);
    
    while (1){
        
        int status = userInput(name);
        
        if (status == 2)
            break;
        
        
        if (status != 0){
            ShowConsoleCursor(false);
            gotoxy(4, 2);
            cout << blankLine;
            
            gotoxy(4, 2);
            ShowConsoleCursor(true);
            cout << name;
        }
        
    }
    
    gotoxy(4, 3);
    
    while (1){
        int status = userInput(pass);
        
        if (status == 2)
            break;
        
        
        if (status != 0){
            ShowConsoleCursor(false);
            gotoxy(4, 3);
            cout << blankLine;
            
            gotoxy(4, 3);
            ShowConsoleCursor(true);
            cout << pass;
        }
    }
    
    
}

void aboutScreen(){
    
}

void menuScreen(bool skip = false){
    ShowConsoleCursor(false);
    // Skip to play screen
    if (skip){
        playScreen();
        return;
    }
    
    system("cls");
    int selected = 2;
    int screen = 0;
    
    string spaces(120, ' ');
    for (int i = 0; i < 30; i++)
        cout << spaces << endl;
    
    gotoxy(0, 0);
	// dyeAll("142334");
    
    // gotoxy((120 - 75)/2, 2);
    // COORD startLine = GetConsoleCaretPos();
    // for (int i = 0; i < 25; i++){
    //     cout << fall[i];
    //     gotoxy(startLine.X, startLine.Y + i + 1);
    // }
    
    while (1){
        // cout << tintAll("142334");
        
        gotoxy(0, 0);
        cout << (selected != 1 ? " \t" : ">\t") << "Start!" << endl;
        cout << (selected != 2 ? " \t" : ">\t") << "Login" << endl;
        cout << (selected != 3 ? " \t" : ">\t") << "About" << endl;
        
        int c = 0;
        switch((c=getch())) {
            case KEY_DOWN:
                // cout << endl << "Up" << endl;//key up
                if (selected == 3)
                    selected = 1;
                else
                    selected += 1;
                break;
                
            case KEY_UP:
                // cout << endl << "Down" << endl;   // key down
                if (selected == 1)
                    selected = 3;
                else
                    selected -= 1;
                break;
                
            case ' ':
                screen = selected;
                break;
            
            default:
                // cout << endl << "null" << endl;  // not arrow
                break;
        }
        
        switch (screen){
            case 1:
                playScreen();
                break;
            case 2:
                loginScreen();
                break;
            case 3:
                aboutScreen();
                break;
        }
    }
}
