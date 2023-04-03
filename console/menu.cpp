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
void drawMenu() {
	string menu[6] = {"=== MENU ===", "Play", "Game Mode", "LeaderBoards", "Credits", "Exit"};
	int counter = 1;
	char key;
	int y = 20;
	system("cls");
	SetConsoleOutputCP(65001);
	while(true){
		for (int i = 0; i < 6; i++) {
			gotoxy(50, y);
			cout << menu[i] << "\n";
			y++;
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
			dye(menu[1], rainbow[0]);
		}
		if (counter == 2) {
			dye(menu[2], rainbow[0]);
		}
		if (counter == 3) {
			dye(menu[3], rainbow[0]);
		}
		if (counter == 4) {
			dye(menu[4], rainbow[0]);
		}
		if (counter == 5) {
			dye(menu[5], rainbow[0]);
		}
	}
}
