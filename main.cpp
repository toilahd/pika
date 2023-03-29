#include <iostream>
#include "engine/game.h"

using namespace std;

int main(){
    bool gameRun = true;
    int screen = 2;
    
    int** map = generateMap(10, 10);
    system("cls");
    
    
    while (gameRun){
        
        switch (screen){
            case 1:
                menuScreen();
                break;
                
            case 2:
                playScreen(map, 10, 10);
                break;
            
            default:
                screen = 1;
                menuScreen();
                break;
        }
    }
    
    return 0;
}