#include <iostream>
#include <Windows.h>
using namespace std;

#define RED RGB(0, 255, 0)

void color(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for (int i = 0; i <= 15; i++){
        SetConsoleTextAttribute(hConsole, i);
        cout << i << " I want to be nice today!" << endl;
    }
}

int main(){
    string buffer = "";
    
    buffer += "hello";
    buffer += "world, programmed to work but not to feel." ;
    
    cout << buffer;
    
    return 0;
}
