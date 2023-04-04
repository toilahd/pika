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
void drawImages(int x, int y, string filename){
	int line = 0, col = 0;
	string img;
	ifstream in;
	in.open(filename);
	while(!in.eof()){
		getline(in, img);
		gotoxy(x, y + line);
		cout << img;
		line++;
	}
	in.close();
}
void drawBox(string menu, int x, float y, int z){
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
		drawImages(30, 3, "logo.txt");
		drawImages(0, 15, "logo1.txt");
		gotoxy(55, 25);
		cout << menu[0];
		drawBox(menu[1], 55, 27, 59);
		drawBox(menu[2], 55, 30, 57);
		drawBox(menu[3], 55, 33, 55);
		drawBox(menu[4], 55, 36, 58);
		drawBox(menu[5], 55, 39, 59);		
		key = _getch();
		// 72 = up arrow key
		if (key == 72 && (counter >= 2 && counter <= 5)) {
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 4)) {
			counter++;
		}
		//carriage return = enter key
		if (counter == 1){
			gotoxy(54, 21);
			cout << dye(rainbow[3], menu[1]);
		}
		if (counter == 2){
			gotoxy(50, 24);
			cout << dye(rainbow[3], menu[2]);
		}
		if (counter == 3){
			gotoxy(50, 27);
			cout << dye(rainbow[3], menu[3]);
		}
		if (counter == 4){
			gotoxy(53, 24);
			cout << dye(rainbow[3], menu[4]);
		}
		if (counter == 5){
			gotoxy(54, 33);
			cout << dye(rainbow[3], menu[5]);
		}
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
