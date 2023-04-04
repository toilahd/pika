#include "menu.h"


int main(){
	SetWindowSize(140, 30);
	SetScreenBufferSize(140, 30);
	ShowScrollbar(false);
	DisableResizeWindow();
	drawMenu();
	return 0;
}