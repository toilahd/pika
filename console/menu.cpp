#include "menu.h"



int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void drawTitle(int x, int y, string filename){
	SetConsoleOutputCP(65001);
	int line = 0, col = 0;
	string img;
	ifstream in;
	in.open(filename);
	srand((unsigned int)time(NULL));
	while(!in.eof()){
		getline(in, img);
		gotoxy(x, y + line);
			cout << img;
		line++;
	}
	in.close();
}
void drawImages(int x, int y, int color, string filename){
	SetConsoleOutputCP(65001);
	int line = 0, col = 0;
	string img;
	ifstream in;
	in.open(filename);
	while(!in.eof()){
		getline(in, img);
		gotoxy(x, y + line);
		if (color > 0){
			cout << dye(rainbow[color], img);
		}
		else
			cout << img;
		line++;
	}
	in.close();
}
void drawBox(string menu, int x, int y, int z){
	gotoxy(x - 6, y - 1 );
	cout << "╭───────────────────────╮" << endl;
	gotoxy(x - 6, y);
    cout << "│      ";
	gotoxy(z, y);
	cout << menu;
	gotoxy(x + 13, y);
	cout << "     │" << endl;
	gotoxy(x - 6, y + 1);
    cout << "╰───────────────────────╯";
}
void playGame() {
	system("cls");
	system("pause");
	system("cls");
}


void leaderBoards() {
	system("cls");
	drawImages(15, 3, -1, "leader.txt");
	// code for displaying the leader boards goes here
	gotoxy(58, 40);
	system("pause");
	system("cls");
}

void credits() {
	system("cls");
	drawImages(15, 3, -1, "credits/logo.txt");
	drawImages(45, 15, -1, "credits/credits.txt");
	gotoxy(63, 33);
	system("pause");
	system("cls");
}
void cursor(int x, int y, int color){
	gotoxy(x, y);
	cout << dye(rainbow[color],"╭──               ──╮          ╭─   ─╮");
	gotoxy(x, y + 2);
	cout << dye(rainbow[color],"╰──               ──╯          ╰─   ─╯");
}
void redrawMenu(int counter){
	string menu[4] = {"PLAY           ──────     ◊"
					,"LEADERBOARDS      ──────     ◊"
					, "CREDITS         ──────     ◊"
					, "EXIT           ──────     ◊"};
	
		system("cls");
		drawTitle(78, 3, "menu/menugame.txt");
		gotoxy(94, 27);
		cout << menu[0];
		gotoxy(91, 30);
		cout << menu[1];
		gotoxy(93, 33);
		cout << menu[2];
		gotoxy(94, 36);
		cout << menu[3];	
		if (counter == 1){
			cursor(86, 26, 4);
			gotoxy(94, 27);	
			cout << dye(rainbow[4], menu[0]);
		}
		if (counter == 2){
			cursor(86, 29, 4);
			gotoxy(91, 30);
			cout << dye(rainbow[4], menu[1]);
		}
		if (counter == 3){
			cursor(86, 32, 4);
			gotoxy(93, 33);
			cout << dye(rainbow[4], menu[2]);
		}
		if (counter == 4){
			cursor(86, 35, 4);
			gotoxy(94, 36);
			cout << dye(rainbow[4], menu[3]);
		}
		

}
void drawMenu(){
	string menu[4] = {"PLAY           ──────     ◊"
					,"LEADERBOARDS      ──────     ◊"
					, "CREDITS         ──────     ◊"
					, "EXIT           ──────     ◊"};
	int counter = 1;
	char key;
	SetWindowSize(150, 42);
	SetScreenBufferSize(150, 42);
	SetConsoleOutputCP(65001);
	DisableResizeWindow();
	ShowScrollbar(false);
	ShowConsoleCursor(false);
	system("cls");
	while(true){
		drawTitle(78, 3, "menu/menugame.txt");
		//gotoxy(68, 25);
		//cout << menu[0];
		//drawBox(menu[1], 68, 27, 72);
		//drawBox(menu[2], 68, 30, 69);
		//drawBox(menu[3], 68, 33, 71);
		//drawBox(menu[4], 68, 36, 72);
		gotoxy(94, 27);
		cout << menu[0];
		gotoxy(91, 30);
		cout << menu[1];
		gotoxy(93, 33);
		cout << menu[2];
		gotoxy(94, 36);
		cout << menu[3];	
		if (counter == 1){
			cursor(86, 26, 4);
			gotoxy(94, 27);	
			cout << dye(rainbow[4], menu[0]);
		}
		if (counter == 2){
			cursor(86, 29, 4);
			gotoxy(91, 30);
			cout << dye(rainbow[4], menu[1]);
		}
		if (counter == 3){
			cursor(86, 32, 4);
			gotoxy(93, 33);
			cout << dye(rainbow[4], menu[2]);
		}
		if (counter == 4){
			cursor(86, 35, 4);
			gotoxy(94, 36);
			cout << dye(rainbow[4], menu[3]);
			}
		key = _getch();
		// 72 = up arrow key
		if (key == 72 && (counter >= 2 && counter <= 4)) {
			counter--;
			redrawMenu(counter);
			Sleep(100);
		}
		if (key == 80 && (counter >= 1 && counter <= 3)) {
			counter++;
			redrawMenu(counter);
			Sleep(100);
		}
		//carriage return = enter key
		if (key == '\r'){
			if (counter == 1){
				playGame();
			}
			if (counter == 2){
				leaderBoards();
			}
			if (counter == 3){
				credits();
			}
			if (counter == 4){
				return;
			}
		}
	}
}
