#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <random>
#include <iomanip>
#include <string>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int selected = 1;

void menuScreen(){
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

int** generateMap(int m, int n){
    int **map = new int*[m];
    srand(2);
    
    for (int i = 0; i < m; i++){
        map[i] = new int [n];
        
        for (int j = 0; j < n; j++)
            map[i][j] = rand() % 8;
    }
    
    return map;
}

void mapPrint(int **map, int m, int n, int mx = -1, int my = -1, int m2x = -1, int m2y = -1){
    system("cls");
    int txtw = 3;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
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

bool pathSearch(int **map, int m, int n, int x, int y, int x2, int y2){
    
    // cout << x << " : " << x2 << endl;
    if (*(*(map + y) + x) == 0 || *(*(map + y2) + x2) == 0 || (x == x2 && y == y2))
        return false;
        
    Sleep(1000);
    
    if (y == y2 && *(*(map + y) + x) == *(*(map + y) + x2)){
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
    
    if (x == x2 && *(*(map + y) + x) == *(*(map + y2) + x)){
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
    
    
    
    return false;
}

void playScreen(int** map, int m, int n){
    mapPrint(map, m, n);
    
    char temp;
    int a, b, c, d;
    cout << "Nhap toa do 1: ";
    cin >> a >> b;
    cout << "Nhap toa do 2: ";
    cin >> c >> d;
    
    if (!pathSearch(map, m, n, b, a, d, c)){
        cout << "Khong co duong" << endl;
        Sleep(800);
        // string temp;
        // cin >> temp;
    }
    else {
        cout << "UOOooh" << endl;
        Sleep(800);
        // string temp;
        // cin >> temp;
    }
}