#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <random>
#include <iomanip>
#include <string>

#include "../console/ui.hpp"
#include "../console/console.h"
#include "dataType.hpp"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int selected = 1;

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
    
    if ((*(*(map + y) + x) == 0 || *(*(map + y2) + x2) == 0) && skip == false)
        return false;
    
    if ((x == x2 && y == y2) || *(*(map + y) + x) != *(*(map + y2) + x2))
        return false;
        
    // Horizontal matching
    if (y == y2){
        bool obstacle = false;
        for (int i = min(x, x2) + 1; i < max(x, x2); i++)
            if (map[y][i] != 0)
                obstacle = true;
                
        if (!obstacle){
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
                Sleep(400);
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
                Sleep(400);
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
                Sleep(400);
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
                        Sleep(400);
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
                Sleep(400);
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
                    map[y][x] = map[y2][x2] = 0;
                    
                    // For debugging
                    COORD origin = GetConsoleCaretPos();
                    gotoxy(70, 16);
                    cout << "⊃   matching";
                    if (!skip)
                        Sleep(400);
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
                
                // For debugging
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 16);
                cout << "⊃matching@" << i;
                if (!skip)
                    Sleep(400);
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
                        Sleep(400);
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
                    Sleep(400);
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
                        Sleep(400);
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
                    Sleep(400);
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
                        Sleep(400);
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
                    Sleep(400);
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
                Sleep(400);
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
                Sleep(400);
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
    srand(4);
    
    for (int i = 0; i < m; i++){
        map[i] = new int [n];
        
        for (int j = 0; j < n; j++)
            map[i][j] = 0;
    }
    
    int count = 1;
    while (m*(double)n / (2*count) > 25 && m*n % (2*count) == 0)
        count++;
        
    for (int i = 0; i < m*(double)n / (2*count); i++)
        for (int j = 0; j < count; j++){
            int x, y, x2, y2;
            
            // do {
                do {x = rand() % n; y = rand() % m;} while (map[y][x] != 0);
                do {x2 = rand() % n; y2 = rand() % m;} while (map[y2][x2] != 0);
            // }
            // while (!pathSearch(map, m, n, x, y, x2, y2, true));
            
            map[y][x] = i;
            map[y2][x2] = i;
            
            for (int a = 0; a < m; a++){
                for (int b = 0; b < n; b++)
                    cout << "[" << map[a][b] << "]";
                cout << endl;
            }
            cout << "----------------------------" << endl;
        }  
    
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


bool isEmpty(BoardLayout a){
    for (int i = 0; i < a.height; i++)
        for (int j = 0; j < a.width; j++)
            if (a.board[i][j] != 0)
                return false;
                
    return true;
}

bool isSolveable(BoardLayout a){
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
                        a.board[i][j] = a.board[b][c] = value;
                        return true;
                    }
        }
                
    return false;
}

void banter(int skill){
    // Construct a new screen with dialog box
    if (skill <= 0 && false){
        gotoxy(50, 15);
        cout << "My oh my, a new kid on the block, trying to kill his useless time";
        gotoxy(0, 0);
    }
}
void playScreen(User player = User{"", "", 0}){
    ShowConsoleCursor(false);
    int timeLength = 300;
    
    
    if (player.isLogged == false){
        string stockName = "Player 1";
        strcpy(player.name, stockName.c_str());
        player.getBoard.board = generateMap(8, 8);
        player.getBoard.height = 8;
        player.getBoard.width = 8;
    }
    
    bool solveState = isSolveable(player.getBoard);
    
    bool isWon = false;
    while (1){
        if (isWon){
            player.skill++;
            isWon = false;
        }
        
        banter(player.skill);
        
        time_t startTime = time(NULL);
        
        boardPrint(player.getBoard, "Level: " + to_string(player.skill));
        
        while (1){
            int key = -1;
            
            // A non blocking input
            if (_kbhit()){
                key = _getch();
                // cout << "Key: " << key << endl;
            }
            
            // if ESC -> pauseScreen
            if (key == 27){
                time_t pauseTime = time(NULL);
                while (1){
                    cout << "Break time!" << endl;
                    // Some reserved space for code to navigate Pause screen items but repressing the ESC key will break out the pause loop
                    
                    // A blocking input
                    key = _getch();
                    
                    if (key == 27){
                        startTime += time(NULL) - pauseTime;
                        cout << "Continuing the game..." << endl;
                        break;
                    }
                }
            
            }
            //  Check for Space key input
            else if (key == 32){
                // Fill up point1 and point2
                if (player.getBoard.point1 == make_pair(-1, -1)){
                    player.getBoard.point1 = player.getBoard.highlight;
                }
                else if (player.getBoard.point2 == make_pair(-1, -1)){
                    player.getBoard.point2 = player.getBoard.highlight;
                }
                
                // Path search when 2 points were filled
                if (player.getBoard.point1 != make_pair(-1, -1) && player.getBoard.point2 != make_pair(-1, -1)){
                    cout << "Search for path" << endl;
                    if (pathSearch(player.getBoard.board, player.getBoard.height, player.getBoard.width, player.getBoard.point1.first, player.getBoard.point1.second, player.getBoard.point2.first, player.getBoard.point2.second)){
                        boardPrint(player.getBoard);
                        Sleep(400);
                        // Reset 2 highlighted points
                        player.getBoard.point1 = player.getBoard.point2 = make_pair(-1, -1);
                        boardPrint(player.getBoard);
                    }
                    else {
                        cout << "No path found";
                        Sleep(400);
                        player.getBoard.point1 = player.getBoard.point2 = make_pair(-1, -1);
                        boardPrint(player.getBoard);
                    }
                    
                }
                
            }
            
            // if move, refresh the actual map
            else if (key == 0 || key == 224){
                key = _getch();
                
                // Arrow keys for navigating the board
                switch (key) {
                    case 72: 
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
                
                boardPrint(player.getBoard);
                solveState = isSolveable(player.getBoard);
            }
                
            // if did not move, do not refresh the map but only refresh the time, stats element...
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
            }
                
        }
    }
}


void menuScreen(bool skip = false){
    if (skip){
        playScreen();
        return;
    }
    
    system("cls");
    
    cout << (selected != 1 ? "\t" : ">\t") << "Play Game" << endl;
    cout << (selected != 2 ? "\t" : ">\t") << "Continue previous game" << endl;
    cout << (selected != 3 ? "\t" : ">\t") << "About" << endl;
    
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
        
        default:
            // cout << endl << "null" << endl;  // not arrow
            break;
        }
}
