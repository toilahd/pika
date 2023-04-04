#define NCURSES_MOUSE_VERSION
#define PI 3.14
// #include "include/curses.h"
#include <Windows.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cmath>

// #include "console/ui.hpp"
#include "console/color.hpp"
#include "engine/dataType.hpp"

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
void gotoxy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
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
	char name[30]; // 29 chars + ’\0’
	double score; // 8 byte floating point number
};

void fileTest(){
	ifstream file("sample.bin", ios::binary);
	
	file.seekg(0, ios:: end);
	cout << file.tellg() << endl;
	
	char a[100];
	cout << sizeof(a) << endl;
}

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

void pixelManipulatingTest(){
	//Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    while(true){
        SetPixel(mydc, 20, 20, RGB(255, 255, 255));
        SetPixel(mydc, 20, 21, RGB(255, 255, 255));
        SetPixel(mydc, 20, 22, RGB(255, 255, 255));
        SetPixel(mydc, 20, 23, RGB(255, 255, 255));
        SetPixel(mydc, 21, 20, RGB(255, 255, 255));
        SetPixel(mydc, 21, 21, RGB(255, 255, 255));
        SetPixel(mydc, 21, 22, RGB(255, 255, 255));
        SetPixel(mydc, 21, 23, RGB(255, 255, 255));
        SetPixel(mydc, 22, 20, RGB(255, 255, 255));
        SetPixel(mydc, 22, 21, RGB(255, 255, 255));
        SetPixel(mydc, 22, 22, RGB(255, 255, 255));
        SetPixel(mydc, 22, 23, RGB(255, 255, 255));
        SetPixel(mydc, 23, 20, RGB(255, 255, 255));
        SetPixel(mydc, 23, 21, RGB(255, 255, 255));
        SetPixel(mydc, 23, 22, RGB(255, 255, 255));
        SetPixel(mydc, 23, 23, RGB(255, 255, 255));
    }

    ReleaseDC(myconsole, mydc);
    cin.ignore();
}


int main(int argc, char *argv[]){
	while (1)
		pixelManipulatingTest();

	return 0;
}
