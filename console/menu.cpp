#include "menu.h"

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
	cout << "=== LEADER BOARDS ===" << endl;
	// code for displaying the leader boards goes here
	system("pause");
	system("cls");
}

void credits() {
	system("cls");
	cout << "...";
	system("pause");
	system("cls");
}
void exit() {
	system("cls");
	gotoxy(50, 15);
	cout << "Thank you so much!\n";
	gotoxy(45, 16);
	system("pause");
	system("cls");
	return;
}

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
			cout << dye(rainbow[GetRandom(0,14)], img);
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
void drawMenu() {
	
	string menu[6] = {"=== MENU ===", "Play", "Game Mode", "LeaderBoards", "Credits", "Exit"};
	int counter = 1;
	char key;
	SetWindowSize(150, 42);
	SetScreenBufferSize(150, 42);
	SetConsoleOutputCP(65001);
	DisableResizeWindow();
	ShowScrollbar(false);
	system("cls");
	while(true){
		drawTitle(47, 3, "logo.txt");
		drawImages(15, 23, -1, "burger.txt");
		drawImages(100, 30, 0, "fish.txt");
		drawImages(110, 10, -1, "icescream.txt");
		drawImages(5, 3, 1, "cheese.txt");
		//gotoxy(68, 25);
		//cout << menu[0];
		drawBox(menu[1], 68, 27, 72);
		drawBox(menu[2], 68, 30, 70);
		drawBox(menu[3], 68, 33, 68);
		drawBox(menu[4], 68, 36, 71);
		drawBox(menu[5], 68, 39, 72);		
		if (counter == 1){
			gotoxy(72, 27);
			cout << dye(rainbow[3], menu[1]);
		}
		if (counter == 2){
			gotoxy(70, 30);
			cout << dye(rainbow[3], menu[2]);
		}
		if (counter == 3){
			gotoxy(68, 33);
			cout << dye(rainbow[3], menu[3]);
		}
		if (counter == 4){
			gotoxy(71, 36);
			cout << dye(rainbow[3], menu[4]);
		}
		if (counter == 5){
			gotoxy(72, 39);
			cout << dye(rainbow[3], menu[5]);
		}
		key = _getch();
		// 72 = up arrow key
		if (key == 72 && (counter >= 2 && counter <= 5)) {
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 4)) {
			counter++;
		}
		//carriage return = enter key
		if (key == '\r'){
			if (counter == 1){
				playGame();
			}
			if (counter == 2){
				gameMode();
			}
			if (counter == 3){
				leaderBoards();
			}
			if (counter == 4){
				credits();
			}
			if (counter == 5){
				exit();
			}
		}
	}
}
