#include <iostream>
#include "engine/game.h"
#include "engine/color.hpp"

using namespace std;

int main(){
    SetConsoleOutputCP(65001);
    
    bool gameRun = true;
    int screen = 2;
    
    int** map = generateMap(10, 10);
    system("cls");
    
    while (gameRun){
        
        string tmp;
        switch (screen){
            case 1:
                menuScreen();
                break;
                
            case 2:
                playScreen(map, 10, 10);
                // cout << EXAMPLE_LAYOUT << endl;
                cin >> tmp;
                break;
            
            default:
                screen = 1;
                menuScreen();
                break;
        }
    }
    
    return 0;
}