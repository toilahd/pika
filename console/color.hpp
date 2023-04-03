#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

const string rainbow[] = {"#FF0000", "#FFA500", "#FFFF00", "#5dc591", "#84ff01", "#077712", "#00FFFF", "#ADD8E6", "#0000FF", "#4B0082", "#FFC0CB", "#EE82EE", "#FF69B4", "#FF1493", "#800000"};

ostream& bold_on(ostream& cout){
    return cout << "\e[1m";
}

ostream& bold_off(ostream& cout){
return cout << "\e[0m";
}

string dye(string color, string text = "▞▞▞▞▞█▓▒░"){
    if (color.at(0) == '#'){
        color = color.substr(1, 6);
    }
    
    int r = stoi(color.substr(0, 2), nullptr, 16);
    int g = stoi(color.substr(2, 2), nullptr, 16);
    int b = stoi(color.substr(4, 2), nullptr, 16);
    
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + text + "\033[0m";
}

string fill(string color, string text = "hello"){
    if (color.at(0) == '#'){
        color = color.substr(1, 6);
    }
    
    int r = stoi(color.substr(0, 2), nullptr, 16);
    int g = stoi(color.substr(2, 2), nullptr, 16);
    int b = stoi(color.substr(4, 2), nullptr, 16);
    
    return "\033[48;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + text + "\033[0m";
}

void testingBold(){
    cout << "\e[1mHello\e[0mHello" << endl;
    cout << "\e[1m" << dye("ec8797", "Hello") << "\e[0m" << dye("ec8797", "Hello") << "" << endl;
    cout << "\x1b[1mHello\x1b[0mHello" << endl;
    cout << bold_on << "Hello" << bold_off << "Hello" << endl;
    cout << bold_on << dye("ec8797", "Hello") << bold_off << dye("ec8797", "Hello") << endl;
}

void testColor(){
    SetConsoleOutputCP(65001);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    
	cout << dye("#cba6f7", "Hex color code can be written with/without # ,like dye(\"#cba6f7\", textToDye)") << endl;
	cout << dye("cba6f7", "...or dye(\"cba6f7\", anotherTextToDye)") << endl;
    
    cout << "...and it automatically resets, even written inline like " << dye("ff0000","t") << dye("00ff00", "h") << dye("0000ff", "i") << dye("ffffff","s") << ", and " << fill("437213", "background") << " too." << endl;
    
    cout << dye("#ff0000") << endl;
    cout << dye("#ffa500") << endl;
    cout << dye("#ffff00") << endl;
    cout << dye("#008000") << endl;
    cout << dye("#0000ff") << endl;
    cout << dye("#4b0082") << endl;
    cout << dye("#ee82ee") << endl;
    
    cout << "And now, the classics..." << endl;
    
    cout << fill("#ff0000") << endl;
    cout << fill("#ffa500") << endl;
    cout << fill("#ffff00") << endl;
    cout << fill("#008000") << endl;
    cout << fill("#0000ff") << endl;
    cout << fill("#4b0082") << endl;
    cout << fill("#ee82ee") << endl;
}