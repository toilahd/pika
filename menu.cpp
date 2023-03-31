#include <conio.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "console.h"


using namespace std;

string dye(string color, string text = "▞▞▞▞▞█▓▒░"){
    if (color.at(0) == '#'){
        color = color.substr(1, 6);
    }
    
    int r = stoi(color.substr(0, 2), nullptr, 16);
    int g = stoi(color.substr(2, 2), nullptr, 16);
    int b = stoi(color.substr(4, 2), nullptr, 16);
    
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + text + "\033[0m";
}

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
	int Set[] = { 7 ,7 ,7 ,7 ,7 ,7 };
	int counter = 1;
	char key;
	setConsoleFontSize(20);
	SetWindowSize(110, 30);
	SetScreenBufferSize(110, 30);
	ShowScrollbar(false);
	DisableResizeWindow();
	DisableCtrButton(0, 0, 1);

	system("cls");
	while (true) {
		string pics = R"(
		⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⠤⠤⠤⠤⠤⠤⣀⡀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢀⣠⢤⡶⠞⠋⠉⠀⣀⣀⣀⣀⣀⣀⣀⠀⠉⠲⡀⠀
⠀⠀⠀⠀⣀⠴⢊⡥⠚⠁⣀⠤⠖⠊⠉⠀⠀⠀⠀⠈⢧⡸⡀⠀⠀⢹⠀
⠀⢀⡴⠊⣡⠖⠁⢀⠴⠊⣁⣀⡠⠔⠒⠊⠉⠉⠓⢦⠀⠀⢱⠀⠀⢀⡇
⡴⠋⢀⠞⠁⢀⠔⠁⢀⡼⠤⠇⣀⡤⠤⠤⡀⠀⠀⢸⠀⠀⡸⠀⠀⡸⠀
⠀⣰⠃⠀⡰⠃⠀⡴⠋⠀⡠⠊⠁⠀⠀⣠⠇⠀⢠⠎⠀⢠⠋⠀⣰⠃⠀
⣰⠃⢠⡚⡗⠀⡜⠀⠀⢸⡀⠀⣀⣼⣹⠁⢀⠔⠁⢀⡴⠃⢀⡴⠁⠀⠀
⡇⠀⠀⡏⠁⠀⣇⠀⠀⠀⠈⠉⠀⣀⠤⠚⠁⢀⡤⠋⠀⡠⠊⣠⠞⠀⠀
⡇⠀⠀⢻⡀⠀⠈⠓⠲⠖⠒⠚⠉⠀⢰⡋⢙⠏⢀⡤⢊⡠⠚⠁⠀⠀⠀
⢳⡀⠀⠀⠙⠲⠤⠄⠀⠠⠤⠤⠒⠊⠁⣉⣭⣚⡥⠒⠉⠀⠀⠀⠀⠀⠀
⠀⠙⡞⠉⣆⠀⠀⠀⠀⢀⣀⡤⠤⠶⠛⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠉⠚⠁⠉⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

⠀⠀⠀⠀⠰⠤⠴⠤⠴⢶⠴⠤⠤⠆⠀⠂⠄⠀⠴⠤⠦⠴⠀⠀⠀⠀⠀	

		)";
		gotoxy(50, 0);
		cout << pics;
		gotoxy(50, 20);
		color(Set[0]);
		cout << "=== MENU ===";

		gotoxy(50, 21);
		color(Set[1]);
		cout << "Play";


		gotoxy(50, 22);
		color(Set[2]);
		cout << "Game Mode";

		gotoxy(50, 23);
		color(Set[3]);
		cout << "LeaderBoards";

		gotoxy(50, 24);
		color(Set[4]);
		cout << "Credits";

		gotoxy(50, 25);
		color(Set[5]);
		cout << "Exit";

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
		Set[0] = 8;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;
		Set[4] = 7;
		Set[5] = 7;
		if (counter == 1) {
			Set[1] = 12;
		}
		if (counter == 2) {
			Set[2] = 12;
		}
		if (counter == 3) {
			Set[3] = 12;
		}
		if (counter == 4) {
			Set[4] = 12;
		}
		if (counter == 5) {
			Set[5] = 12;
		}
	}

}
