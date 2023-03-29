#include <iostream>
#include <Windows.h>
using namespace std;

void color(){
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for (int i = 240; i <= 255; i++){
        SetConsoleTextAttribute(hConsole, i);
        cout << i << " I want to be nice today!" << endl;
    }
}

int main(){
    color();
    return 0;
}
