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

int** generateMap(int m, int n){
    int **map = new int*[m];
    srand(4);
    
    for (int i = 0; i < m; i++){
        map[i] = new int [n];
        
        for (int j = 0; j < n; j++)
            map[i][j] = rand() % 8;
    }
    
    return map;
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

bool pathSearch(int **map, int m, int n, int x, int y, int x2, int y2){
    
    // cout << x << " : " << x2 << endl;
    if (*(*(map + y) + x) == 0 || *(*(map + y2) + x2) == 0 || (x == x2 && y == y2) || *(*(map + y) + x) != *(*(map + y2) + x2))
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
            
            // cout << endl;
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
            
            // cout << endl;
            return true;
        }
    }
    
    // Right angle matching
    if (x != x2 && y != y2){
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
            map[y][x] = map[y2][x2] = 0;
            return true;
        }
        
        obstacle = false;
        if (y < y2){
            swap(y, y2);
            swap(x, x2);
        }
        
        for (int i = y - 1; i >= y2; i--)
            if (map[i][x] != 0){
                cout << i << ":" << x << map[i][x] << endl;
                obstacle = true;
                break;
            }
            
        if (!obstacle){
            int direction = 1;
            if (x2 < x)
                direction = -1;
                
            for (int i = x + direction; i != x2; i+=direction)
                if (map[y2][i] != 0){
                    cout << y2 << ":" << i << map[y2][i] << endl;
                    obstacle = true;
                    break;
            }
        }
        
        if (!obstacle){
            map[y][x] = map[y2][x2] = 0;
            return true;
        }
    }
    
    if (x != x2 || y  != y2){
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
                    return true;
                }
            }
            
            while (map[y][i] == 0 && map[y2][i] == 0){
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
                
                map[y][x] = map[y2][x2] = 0;
                return true;
            }
            
        }
        
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
                    return true;
                }
            }
            
            while (map[i][x] == 0 && map[i][x2] == 0){
                bool obstacle = false;
                
                if (!isClear(map, m, n, min(x, x2), i, max(x, x2), i))
                    obstacle = true;
                
                if (obstacle && i < m - 1){
                    i++;
                    continue;
                }
                
                map[y][x] = map[y2][x2] = 0;
                return true;
            }
            
        }
        
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
                    return true;
                }
            }
            
            while (map[y][i] == 0 && map[y2][i] == 0){
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
                return true;
            }
            
        }
        
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
                    return true;
                }
            }
            
            while (map[i][x] == 0 && map[i][x2] == 0){
                bool obstacle = false;
                
                if (!isClear(map, m, n, min(x, x2), i, max(x, x2), i))
                    obstacle = true;
                
                if (obstacle && i > 0){
                    i--;
                    continue;
                }
                
                map[y][x] = map[y2][x2] = 0;
                return true;
            }
            
        }
        
    }
    
    if (x != x2 && y  != y2){
        if (x > x2){
            swap(x, x2);
            swap(y, y2);
        }
        
        for (int i = x + 1; i < x2; i++){
            if (!isClear(map, m, n, i, y, i, y2))
                continue;
            
            if (!isClear(map, m, n, x, y, i, y))
                continue;
                
            if (!isClear(map, m, n, x2, y2, i, y2))
                continue;
                
            map[y][x] = map[y2][x2] = 0;
            return true;
        }
        
        
        
        if (y > y2){
            swap(x, x2);
            swap(y, y2);
        }
        
        for (int i = y + 1; i < y2; i++){
            if (!isClear(map, m, n, x - 1, i, x2 + 1, i))
                continue;
            
            if (!isClear(map, m, n, x, y, x, i))
                continue;
                
            if (!isClear(map, m, n, x2, y2, x2, i))
                continue;
                
            map[y][x] = map[y2][x2] = 0;
            return true;
        }
        
    }
    
    return false;
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
    boardPrint(map, m, n, highlight);
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


void banter(int skill){
    if (skill <= 0){
        // Construct a new screen with dialog box
        gotoxy(50, 15);
        cout << "My oh my, a new kid on the block, trying to kill his useless time";
        gotoxy(0, 0);
    }
}
void playScreen(User player = User{"", "", 0}){
    
    if (player.isLogged == false){
        player.getBoard.board = generateMap(5, 5);
        player.getBoard.height = 5;
        player.getBoard.width = 5;
    }
    
    bool isWon = false;
    while (1){
        if (isWon){
            player.skill++;
        }
        
        banter(player.skill);
        
        time_t startTime = time(NULL);
        
        boardPrint(player.getBoard.board, player.getBoard.height, player.getBoard.width, player.getBoard.highlight);
        
        while (1){
            int key = -1;
            
            // Non blocking input
            if (_kbhit()){
                key = _getch();
                cout << "Key: " << key << endl;
            }
            
            // if ESC -> pauseScreen
            if (key == 27)
                while (1){
                    cout << "Break time!" << endl;
                    // Some reserved space for code to navigate Pause screen items but repressing the ESC key will break out the pause loop
                    
                    // A blocking input
                    key = _getch();
                    
                    if (key == 27){
                        cout << "Continuing the game..." << endl;
                        break;
                    }
                }
            
            // if move, refresh the actual map
            else if (key == 0 || key == 224){
                key = _getch();
                
                switch (key) {
                    case 72: 
                        player.getBoard.highlight.second--;
                        if (player.getBoard.highlight.second < 0)
                            player.getBoard.highlight.second = 0;
                        cout << "Up arrow" << endl;
                        break;
                    case 80:
                        player.getBoard.highlight.second++;
                        if (player.getBoard.highlight.second >= player.getBoard.height)
                            player.getBoard.highlight.second = player.getBoard.height - 1;
                        cout << "Down arrow" << endl; 
                        break;
                    case 75: 
                        player.getBoard.highlight.first--;
                        if (player.getBoard.highlight.first < 0)
                            player.getBoard.highlight.first = 0;
                        cout << "Left arrow" << endl; 
                        break;
                    case 77: 
                        player.getBoard.highlight.first++;
                        if (player.getBoard.highlight.first >= player.getBoard.width)
                            player.getBoard.highlight.first = player.getBoard.width - 1;
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
                
                boardPrint(player.getBoard.board, player.getBoard.height, player.getBoard.width, player.getBoard.highlight);
            }
                
            // if did not move, do not refresh the map but only refresh the time, stats element...
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
