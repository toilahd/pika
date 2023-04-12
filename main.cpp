#pragma pack(1)

#include <iostream>
#include "engine/game.h"
#include "console/color.hpp"

using namespace std;

int main(){
    // For outputing UNICODE characters
    SetConsoleOutputCP(65001);
    // ShowConsoleCursor(false);
    
    system("cls");
    // cout << tintAll("142334");
    
    // skip option with value true will go straight to the game screen
    menuScreen();
    
    return 0;
}