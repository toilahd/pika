#include <iostream>
#include "engine/game.h"
#include "console/color.hpp"

using namespace std;

int main(){
    SetConsoleOutputCP(65001);
    // ShowConsoleCursor(false);
    
    system("cls");
    
    menuScreen(true);
    
    return 0;
}