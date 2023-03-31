#define NCURSES_MOUSE_VERSION
// #include "include/curses.h"
#include <Windows.h>
#include <iostream>

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


int main(int argc, char *argv[])
{
	SetConsoleOutputCP(65001);
	
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

	return 0;
}
