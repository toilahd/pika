#include "menu.h"

void playGame() {
	system("cls");
	cout << "=== PLAY GAME ===" << endl;
	// code for playing the game goes here
	system("pause");
}

void gameMode() {
	system("cls");
	gotoxy(50, 10);
	cout << "=== GAME MODE ===" << endl;
	// code for choosing the game mode goes here
	system("pause");
}

void leaderBoards() {
	system("cls");
	cout << "=== LEADER BOARDS ===" << endl;
	// code for displaying the leader boards goes here
	system("pause");
}

void credits() {
	system("cls");
	cout << "...";
	system("pause");
}
void exit() {
	system("cls");
	gotoxy(50, 15);
	cout << "Thank you so much!\n";
	gotoxy(45, 16);
	system("pause");
	return;
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
	SetConsoleOutputCP(65001);
	system("cls");
	while(true){
		gotoxy(50, 19);
		cout << menu[0];
		drawBox(menu[1], 50, 21, 54);
		drawBox(menu[2], 50, 24, 52);
		drawBox(menu[3], 50, 27, 50);
		drawBox(menu[4], 50, 30, 53);
		drawBox(menu[5], 50, 33, 54);		
		key = _getch();
		// 72 = up arrow key
		if (key == 72 && (counter >= 2 && counter <= 5)) {
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 4)) {
			counter++;
		}
		//carriage return = enter key
		if (key == '\r') {
			if (counter == 1) {
				playGame();
			}
			if (counter == 2) {
				gameMode();
			}
			if (counter == 3) {
				leaderBoards();
			}
			if (counter == 4) {
				credits();
			}
			if (counter == 5) {
				exit();
			}
		}
		if (counter == 1) {
			gotoxy(50, 21);
			cout << dye(rainbow[3], menu[1]);
		}
		if (counter == 2) {
			gotoxy(50, 22);
			cout << dye(rainbow[3], menu[2]);
		}
		if (counter == 3) {
			gotoxy(50, 23);
			cout << dye(rainbow[3], menu[3]);
		}
		if (counter == 4) {
			gotoxy(50, 24);
			cout << dye(rainbow[3], menu[4]);
		}
		if (counter == 5) {
			gotoxy(50, 25);
			cout << dye(rainbow[3], menu[5]);
		}
	}
}
