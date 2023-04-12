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


/*
BUTTON1_PRESSED          mouse button 1 down
BUTTON1_RELEASED         mouse button 1 up
BUTTON1_CLICKED          mouse button 1 clicked
BUTTON1_DOUBLE_CLICKED   mouse button 1 double clicked
BUTTON1_TRIPLE_CLICKED   mouse button 1 triple clicked
BUTTON2_PRESSED          mouse button 2 down
BUTTON2_RELEASED         mouse button 2 up
BUTTON2_CLICKED          mouse button 2 clicked
BUTTON2_DOUBLE_CLICKED   mouse button 2 double clicked
BUTTON2_TRIPLE_CLICKED   mouse button 2 triple clicked
BUTTON3_PRESSED          mouse button 3 down
BUTTON3_RELEASED         mouse button 3 up
BUTTON3_CLICKED          mouse button 3 clicked
BUTTON3_DOUBLE_CLICKED   mouse button 3 double clicked
BUTTON3_TRIPLE_CLICKED   mouse button 3 triple clicked
BUTTON4_PRESSED          mouse button 4 down
BUTTON4_RELEASED         mouse button 4 up
BUTTON4_CLICKED          mouse button 4 clicked
BUTTON4_DOUBLE_CLICKED   mouse button 4 double clicked
BUTTON4_TRIPLE_CLICKED   mouse button 4 triple clicked
BUTTON_SHIFT             shift was down during button state change
BUTTON_CTRL              control was down during button state change
BUTTON_ALT               alt was down during button state change
ALL_MOUSE_EVENTS         report all button state changes
REPORT_MOUSE_POSITION    report mouse movement
*/

/* void ncurses(){
	MEVENT event;

	int ch = 0;
	initscr();
	// raw();
	keypad(stdscr, TRUE);
	// noecho();
	mmask_t old;
	mousemask (ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);


	while(ch != 27)
	{
		ch = getch();
		if(ch == KEY_MOUSE) {
			if(getmouse(&event) == OK)
			{
				if(event.bstate & BUTTON1_PRESSED) {
					printw("Mouse down at ê ệ \033[38;2;255;192;203mHello\033[0m, x: %d y: %d\n", event.x, event.y);
					refresh();
				}
			}
		}
	}
	
	refresh();
	endwin();
} */

void oldColorTest(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for (int i = 0; i <= 500; i++){
        SetConsoleTextAttribute(hConsole, i);
        cout << i << " I want to be nice today!";
        SetConsoleTextAttribute(hConsole, 263);
		cout << endl;
    }
}

void layout(){
	cout << "        ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮\n\
           A      B      A      B      A      B      A      B\n\
	╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯\n\
        ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮\n\
        │  A      B      A      B      A      B      A      B\n\
        ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯\n\
        ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮\n\
           A      B      A      B      A      B      A      B\n\
        ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯\n\
        ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮\n\
           A      B      A      B      A      B      A      B\n\
        ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯\n";
}

void anotherLayout(){
	cout << "      ╭─ Player 1 ───────────────────────────────────────────────╮\n\
      │ ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮ │\n\
      │    A <==> B      A      B      A      B      A      B    │\n\
      │ ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯ │\n\
      │ ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮       ╭─   ─╮╭─   ─╮╭─   ─╮ │\n\
      │    A      B      A      B <====╗      B      A      B    │\n\
      │ ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯   ║   ╰─   ─╯╰─   ─╯╰─   ─╯ │\n\
      │ ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮   ║   ╭─   ─╮╭─   ─╮╭─   ─╮ │\n\
      │    A      B      A      B      ║      B      A      B    │\n\
      │ ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯   ║   ╰─   ─╯╰─   ─╯╰─   ─╯ │\n\
      │ ╭─   ─╮╭─   ─╮╭─   ─╮╭─   ─╮   ║          ╭─   ─╮╭─   ─╮ │\n\
      │    A      B      A      B      ╚===========> A      B    │\n\
      │ ╰─   ─╯╰─   ─╯╰─   ─╯╰─   ─╯              ╰─   ─╯╰─   ─╯ │\n\
      ╰──────────────────────────────────────────────────────────╯";
}

void testOnWin10(){
	SetConsoleOutputCP(65001);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
	
	time_t now = time(nullptr);
	
	// testColor();
	string pics = "	     ⠀⣀⣠⠤⠤⠤⠤⠤⠤⣀⡀⠀⠀⠀\n\
⠀⠀⠀⠀⠀⠀⠀⢀⣠⢤⡶⠞⠋⠉⠀⣀⣀⣀⣀⣀⣀⣀⠀⠉⠲⡀⠀\n\
⠀⠀⠀⠀⣀⠴⢊⡥⠚⠁⣀⠤⠖⠊⠉⠀⠀⠀⠀⠈⢧⡸⡀⠀⠀⢹⠀\n\
⠀⢀⡴⠊⣡⠖⠁⢀⠴⠊⣁⣀⡠⠔⠒⠊⠉⠉⠓⢦⠀⠀⢱⠀⠀⢀⡇\n\
⡴⠋⢀⠞⠁⢀⠔⠁⢀⡼⠤⠇⣀⡤⠤⠤⡀⠀⠀⢸⠀⠀⡸⠀⠀⡸⠀\n\
⠀⣰⠃⠀⡰⠃⠀⡴⠋⠀⡠⠊⠁⠀⠀⣠⠇⠀⢠⠎⠀⢠⠋⠀⣰⠃⠀\n\
⣰⠃⢠⡚⡗⠀⡜⠀⠀⢸⡀⠀⣀⣼⣹⠁⢀⠔⠁⢀⡴⠃⢀⡴⠁⠀⠀\n\
⡇⠀⠀⡏⠁⠀⣇⠀⠀⠀⠈⠉⠀⣀⠤⠚⠁⢀⡤⠋⠀⡠⠊⣠⠞⠀⠀\n\
⡇⠀⠀⢻⡀⠀⠈⠓⠲⠖⠒⠚⠉⠀⢰⡋⢙⠏⢀⡤⢊⡠⠚⠁⠀⠀⠀\n\
⢳⡀⠀⠀⠙⠲⠤⠄⠀⠠⠤⠤⠒⠊⠁⣉⣭⣚⡥⠒⠉⠀⠀⠀⠀⠀⠀\n\
⠀⠙⡞⠉⣆⠀⠀⠀⠀⢀⣀⡤⠤⠶⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠉⠚⠁⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
⠀⠀⠀⠀⠰⠤⠴⠤⠴⢶⠴⠤⠤⠆⠀⠂⠄⠀⠴⠤⠦⠴⠀⠀⠀⠀⠀	\n\
\n";

	cout << pics;
	
	cout << time(NULL) - now << endl;
	
	oldColorTest();
}

struct Student {
	unsigned short id; // 2 byte positive integer
	char name[30]; // 29 chars + '\0'
	double score; // 8 byte floating point number
};

void keyPressTest(){
	int key;
	while (1){
		if (_kbhit()){
			key = _getch();
			
			if (key == 27)
				cout << "ESC pressed" << endl;
		}
	}
}

// void pixelManipulatingTest(){
// 	//Get a console handle
//     HWND myconsole = GetConsoleWindow();
//     //Get a handle to device context
//     HDC mydc = GetDC(myconsole);

//     while(true){
//         SetPixel(mydc, 20, 20, RGB(255, 255, 255));
//         SetPixel(mydc, 20, 21, RGB(255, 255, 255));
//         SetPixel(mydc, 20, 22, RGB(255, 255, 255));
//         SetPixel(mydc, 20, 23, RGB(255, 255, 255));
//         SetPixel(mydc, 21, 20, RGB(255, 255, 255));
//         SetPixel(mydc, 21, 21, RGB(255, 255, 255));
//         SetPixel(mydc, 21, 22, RGB(255, 255, 255));
//         SetPixel(mydc, 21, 23, RGB(255, 255, 255));
//         SetPixel(mydc, 22, 20, RGB(255, 255, 255));
//         SetPixel(mydc, 22, 21, RGB(255, 255, 255));
//         SetPixel(mydc, 22, 22, RGB(255, 255, 255));
//         SetPixel(mydc, 22, 23, RGB(255, 255, 255));
//         SetPixel(mydc, 23, 20, RGB(255, 255, 255));
//         SetPixel(mydc, 23, 21, RGB(255, 255, 255));
//         SetPixel(mydc, 23, 22, RGB(255, 255, 255));
//         SetPixel(mydc, 23, 23, RGB(255, 255, 255));
//     }

//     ReleaseDC(myconsole, mydc);
//     cin.ignore();
// }


void ansiArtTest(){
	int count = 0;
	for (int i = 0; i < 12; i++){
		while (banVit[count] != '\n'){
			cout << banVit[count];
			count++;
		}
		cout << count << endl;
		count++;
	}
	
	cout << banVit;
}

void printImageBlock(int x = 0, int y = 0){
	
}

void findM(string str, int &i){
	i = str.find('m', i);
	
	if (str[i + 1] == '\033'){
		i++;
		findM(str, i);
	}
}

int printAt(int at, string str = abc){
	string result;
	
	int i = 0;
	for (int j = 0; j <= at; j++){
		// cout << "------" << endl;
		// cout << i << endl;
		
		if (i >= str.size())
			break;
		
		if (str[i] == '\033'){
			int mAt = i;
			findM(str, mAt);
			mAt++;
			// cout << abc.substr(i, mAt - i + 1);
			result = str.substr(i, mAt - i + 1);
			i += mAt - i + 1;
		}
		else{
			// cout << abc[i];
			result = str[i];
			i++;
		}
		
		// cout << endl;
	}
	
	// cout << result;
	
	return i;
}

void failedAttempt(){
	
	// cout << endl << COLOR_RESET;
	// cout << "-------------------------\n";
	// cout << endl;
	
	// for (int i = 0; i < 50; i){
	// 	cout << fall[i];
			
	// 	i++;
	// }
	
	// printAt(40, fall);
	// for (int i = 3)
	// 	cout << "]" << fallMono.substr(11, 3) << "[" << endl;
	
	int printHere = 40;
	
	// printAt(40, fall[0]);
	// printAt(41, fall[0]);
	// printAt(42, fall[0]);
	
	// return 0;
	for (int i = 0; i < 100; i++)
		if (i%10 == 0)
			cout << dye(rainbow[4], to_string(i%10));
		else
			cout << i%10;
		
	cout << endl;
	
	for (int j = 0; j < 3; j++){
		string str = fall[j];
		bool first = true;
		for (int i = 0; i < printAt(64, str);) {
			if (first){
				first = false;
				cout << printAt(64, str);
			}
			
			std::cout << str[i];
			
			
			if(str[i] & 0x80) {
				std::cout << str[i + 1];
				if(str[i] & 0x20) {
					std::cout << str[i + 2];
					if(str[i] & 0x10) {
						std::cout << str[i + 3];
						i += 4;
					} else {
						i += 3;
					}
				} else {
					i += 2;
				}
			}  else {
				i += 1;
			}
			
		}
		
		cout << endl;
	}
}

void fileTest(){
	ifstream file("sample.bin", ios::binary);
	ifstream in("savedFile.txt", ios::binary);
	
	User user;
	
	file.seekg(0, ios::end);
	in.read((char*)&user, sizeof(User));
	
	cout << user.name << endl;
	cout << user.skill << endl;
	cout << user.getBoard.highlight.first << " " << user.getBoard.highlight.second << endl;
	cout << user.getBoard.point1.first << " " << user.getBoard.point1.second << endl;
	cout << user.getBoard.point2.first << " " << user.getBoard.point2.second << endl;
	
	char a[100];
	cout << sizeof(savefile) << endl;
}

void readFileTest(){
	ifstream f("students.dat", ios::binary);
	// we can’t declare a student array here because we don’t know its size
	// so now we compute the size before reading the file
	f.seekg(0, ios::end);
	int num = f.tellg() / 40; // file size / struct size
	f.seekg(0, ios::beg);
	
	Student students; // now we can declare an array
	
	f.read((char*)&students, sizeof(Student));
	cout << students.id << "\t" << students.name << "\t" << students.score << endl;
	
	f.close();
}

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
	
	cout << "Name: " << decode(file.name, file.mask) << endl;
		
	cout << "Password: " << decode(file.password, file.mask) << endl;
	
	
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
				cout << "[" << decode(file.state[i].board[count], file.mask) << "]";
                count++;
            }
            cout << endl;
        }
		cout << decode(file.state[i].file_background, file.mask) << endl;
        cout << "Background URL: " << decode(file.state[i].file_background, file.mask) << endl;
	}
	
	
	
	return 0;
}
