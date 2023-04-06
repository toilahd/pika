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
	cout << "=== PLAY GAME ===" << endl;
	// code for playing the game goes here
	system("pause");
	system("cls");
}

void gameMode() {
	system("cls");
	gotoxy(50, 10);
	cout << "=== GAME MODE ===" << endl;
	// code for choosing the game mode goes here
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
void drawMenu() {
	
	string menu[6] = {"=== MENU ===", "Play", "LeaderBoards", "Credits", "Exit"};
	int counter = 1;
	char key;
	SetWindowSize(150, 42);
	SetScreenBufferSize(150, 42);
	SetConsoleOutputCP(65001);
	DisableResizeWindow();
	ShowScrollbar(false);
	system("cls");
	while(true){
		drawTitle(35, 3, "menu/logo.txt");
		//gotoxy(68, 25);
		//cout << menu[0];
		drawBox(menu[1], 68, 27, 72);
		drawBox(menu[2], 68, 30, 69);
		drawBox(menu[3], 68, 33, 71);
		drawBox(menu[4], 68, 36, 72);		
		if (counter == 1){
			gotoxy(72, 27);
			cout << dye(rainbow[3], menu[1]);
		}
		if (counter == 2){
			gotoxy(69, 30);
			cout << dye(rainbow[3], menu[2]);
		}
		if (counter == 3){
			gotoxy(71, 33);
			cout << dye(rainbow[3], menu[3]);
		}
		if (counter == 4){
			gotoxy(72, 36);
			cout << dye(rainbow[3], menu[4]);
		}
		key = _getch();
		// 72 = up arrow key
		if (key == 72 && (counter >= 2 && counter <= 4)) {
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 3)) {
			counter++;
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
