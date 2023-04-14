#define NCURSES_MOUSE_VERSION
#define PI 3.14
// #include "include/curses.h"

#include <Windows.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

// #include "console/ui.hpp"
#include "console/color.hpp"
#include "engine/dataType.hpp"
#include "ansiart.hpp"
#include "console/ui.hpp"

using namespace std;

string decode(char text[999], char mask){
	string result;
	for (int i = 0; i < strlen(text); i++){
		result += text[i] ^ mask;
	}
	
	return result;
}

string decode(char text, char mask){
	string result;
	result += (char)(text ^ mask);
	return result;
}

int main(int argc, char *argv[]){
	SetConsoleOutputCP(65001);
	ifstream input("sample.bin", ios::binary);
	
	// Determine the file's size
	input.seekg(0, ios::end);
	cout << "Size of file: " << input.tellg() << endl;
	
	// cout << sizeof(savefile) << endl;
	
	input.seekg(0, ios::beg);
	
	savefile file;
	input.read((char *)&file, sizeof(savefile));
	
	cout << "Mask: " << file.mask << endl;
	
	cout << "Name: " << file.name << endl;
		
	cout << "Password: " << file.password << endl;
	
	
	cout << "--------------" << endl;
	for (int i = 0; i < 5; i++){
		cout << "Record #" << i + 1 << ": " << endl;
		cout << "Date: " << file.record[i].date.dd << "/" << file.record[i].date.dd << "/" << file.record[i].date.dd << endl;
		cout << "Point: " << file.record[i].points << endl;
	}
	
	cout << "--------------" << endl;
	for (int i = 0; i < 5; i++){
		cout << "State #" << i + 1 << ": " << endl;
		cout << "Size: " << file.state[i].p << "x" << file.state[i].q << endl;
		cout << "Pos: " << file.state[i].p_ << "x" << file.state[i].q_ << endl;
        int count = 0;
		for (int j = 0; j < file.state[i].p; j++){
			for (int b = 0; b < file.state[i].q; b++){
				cout << "[" << file.state[i].board[count] << "]";
                count++;
            }
            cout << endl;
        }
		cout << file.state[i].file_background << endl;
        cout << "Background URL: " << file.state[i].file_background << endl;
	}
	
	// ifstream in("sample.bin");
	
	// in.seekg(0, ios::end);
	// int fileSize = in.tellg();
	
	// cout << "Size of the bin file: " << fileSize << endl;
	// cout << "Size of \'savefile\' struct " << sizeof(savefile) << endl;
	
	// in.close();
	
	return 0;
}
