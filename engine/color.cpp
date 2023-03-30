#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

string dye(string color, string text = "▞▞▞▞▞█▓▒░"){
    if (color.at(0) == '#'){
        color = color.substr(1, 6);
    }
    
    int r = stoi(color.substr(0, 2), nullptr, 16);
    int g = stoi(color.substr(2, 2), nullptr, 16);
    int b = stoi(color.substr(4, 2), nullptr, 16);
    
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + text + "\033[0m";
}

int main(){
    SetConsoleOutputCP(65001);
    
	cout << dye("#cba6f7", "Hex color code can be written with/without # ,like dye(\"#cba6f7\", textToDye)") << endl;
	cout << dye("cba6f7", "...or dye(\"cba6f7\", anotherTextToDye)") << endl;
    
    cout << "...and it automatically resets, even written inline like " << dye("ff0000","t") << dye("00ff00", "h") << dye("0000ff", "i") << dye("ffffff","s") << "!!" << endl;
    
    cout << dye("#ff0000") << endl;
    cout << dye("#ffa500") << endl;
    cout << dye("#ffff00") << endl;
    cout << dye("#008000") << endl;
    cout << dye("#0000ff") << endl;
    cout << dye("#4b0082") << endl;
    cout << dye("#ee82ee") << endl;

	return 0;
}