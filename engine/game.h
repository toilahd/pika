#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <random>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "../console/ui.hpp"
#include "../console/console.h"
#include "dataType.hpp"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


// Need more work
void infoScreen(){
    
}

void pauseScreen(time_t &startTime, User &player) {
    time_t pauseTime = time(NULL);
    
    COORD origin = GetConsoleCaretPos();
    int pauseBoxWidth = 100;
    int pauseBoxHeight = 25;
    
    string blankLine(pauseBoxWidth, ' ');
    string upperEdge;
    for (int i = 0; i < pauseBoxWidth - 2; i++)
        upperEdge += "─";
        
    for (int i = 0; i < pauseBoxHeight; i++){
        gotoxy((120 - pauseBoxWidth)/2, (30 - pauseBoxHeight)/2 + i);
        cout << blankLine;
    }
    
    gotoxy((120 - pauseBoxWidth)/2, (30 - pauseBoxHeight)/2);
    cout << "╭";
    
    cout << upperEdge;
        
    cout << "╮";
    
    for (int i = 0; i < pauseBoxHeight - 2; i++){
        gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y + 1);
        cout << "│";
    }
    
    
    gotoxy((120 - pauseBoxWidth)/2, (30 - pauseBoxHeight)/2 + pauseBoxHeight - 2);
    cout << "╰";
    cout << upperEdge;
    cout << "╯";
    
    // Sleep(5000);
    
    gotoxy((120 - pauseBoxWidth)/2 + 1, (30 - pauseBoxHeight)/2);
    for (int i = 0; i < pauseBoxHeight - 3; i++){
        gotoxy(GetConsoleCaretPos().X - 1, GetConsoleCaretPos().Y + 1);
        cout << "│";
    }
    // Sleep(3000);
    
    while (1){
        gotoxy((120 - pauseBoxWidth)/2 + 1, (30 - pauseBoxHeight)/2);
        cout << " Break time! ";
        // Some reserved space for code to navigate Pause screen items but repressing the ESC key will break out the pause loop
        
        gotoxy((120 - pauseBoxWidth)/2 + 3, (30 - pauseBoxHeight)/2 + 2);
        cout << "ESC for Continuing the game";
        gotoxy((120 - pauseBoxWidth)/2 + 3, (30 - pauseBoxHeight)/2 + 3);
        cout << "Q to Quit the current game";
        
        // A blocking input
        int key = _getch();
        COORD origin = GetConsoleCaretPos();
        gotoxy(70, 2);
        cout << key;
        gotoxy(origin.X, origin.Y);
        
        // If ESC -> Continue the game
        if (key == 27){
            startTime += time(NULL) - pauseTime;
            gotoxy((120 - pauseBoxWidth)/2 + 1, (30 - pauseBoxHeight)/2);
            cout << "Continuing the game...";
            
            boxErase(pauseBoxHeight, pauseBoxWidth);
            // Sleep(4000);
            boardPrint(player.getBoard, "Level: " + to_string(player.skill));
            break;
        }
        // If Q key -> Save player info and exit the game
        else if (key == 113){
            string name = "";
            {
                gotoxy(70, 4);
                if (name != "")
                    cout << "Retry: your name must not be longer than 49 charactes";
                gotoxy(70, 5);
                cout << "Your name: ";
                cin >> name;
            } while (name.size() > 49);
            
            string pass = "";
            {
                gotoxy(70, 6);
                if (pass != "")
                    cout << "Retry: your password must not be longer than 49 charactes";
                else
                    cout << "                                                         ";
                gotoxy(70, 7);
                cout << "Your password: ";
                cin >> pass;
            } while (pass.size() > 49);
            
            strcpy(player.name, name.c_str());
            strcpy(player.pass, pass.c_str());
            
            // Open file
            ifstream in("data.bin", ios::binary);
            
            if (in.is_open()){
                // we can’t declare a student array here because we don’t know its size
                // so now we compute the size before reading the file
                in.seekg(0, ios::end);
                int num = in.tellg() / sizeof(User); // file size / struct size
                cout << "file size: " << in.tellg() << ", struct size: " << sizeof(User) << endl;
                in.seekg(0, ios::beg);
                
                User* studentsPointers = new User[num + 1]; // now we can declare an array
                for (int i = 0; i < num; ++i) {
                    in.read((char*)&studentsPointers[i], sizeof(User));
                    cout << studentsPointers[i].name << ": " << studentsPointers[i].skill << endl;
                }
            
                in.close();
                
                // Write to file
                
                strcpy(studentsPointers[num].name, player.name);
                strcpy(studentsPointers[num].pass, player.pass);
                studentsPointers[num].skill = player.skill;
                
                ofstream f("data.bin", ios::binary);
                
                for (int i = 0; i < num + 1; ++i) {
                    f.write((char*)&studentsPointers[i], sizeof(User));
                }
                
                f.close();
            
                delete[] studentsPointers;
            }
            
            Sleep(5000);
            
            // ofstream out("savedFile.bin", ios::binary);
            
            // out.write((char*)info, sizeof(savefile));
            // out.close();
            
            COORD origin = GetConsoleCaretPos();
            gotoxy(70, 2);
            cout << "Exiting the game...";
            gotoxy(origin.X, origin.Y);
            
            exit(1);
        }
    }
            
}

void playScreen(User player = User{"", "", 0}){
    // Initialize new user / load user info from saved file
    system("cls");
    
    ShowConsoleCursor(false);
    int timeLength = 300;
    
    
    // If isLogged is false -> new user -> create map and default username
    if (player.isLogged == false){
        string stockName = "Player 1";
        strcpy(player.name, stockName.c_str());
        player.getBoard.board = generateMap(9, 9);
        player.getBoard.height = 9;
        player.getBoard.width = 9;
    }
    else {
        cout << "Load info from file" << endl;
        Sleep(100);
        
        ifstream in;
        in.open("data.bin", ios::binary);
	
        // we can’t declare a student array here because we don’t know its size
        // so now we compute the size before reading the file
        if (in.is_open()){
            in.seekg(0, ios::end);
            int num = in.tellg() / sizeof(User); // file size / struct size
            cout << "file size: " << in.tellg() << ", struct size: " << sizeof(User) << endl;
            in.seekg(0, ios::beg);
            
            User* studentsPointers = new User[num]; // now we can declare an array
            for (int i = 0; i < num; ++i) {
                in.read((char*)&studentsPointers[i], sizeof(User));
            cout << studentsPointers[i].name << endl;
            }
            
            delete[] studentsPointers;
            
        }
        else
            cout << "Cannot open file" << endl;
        
        Sleep(4000);
    }
    
    bool isWon = false;
    while (1){
        // Game starting point. All levels only goes through these lines once
        
        // If the player has won in the previous game -> make new map + increase skill (level)
        if (isWon){
            player.skill++;
            isWon = false;
            player.getBoard.board = generateMap(9, 9);
            player.getBoard.height = 9;
            player.getBoard.width = 9;
        }
        
        // Check for player's skill level, then rearrange board accordingly
        rearrange(player);
        
        
        // Check if the board is solvable then load the result to solveState
        bool solveState = isSolvable(player.getBoard);
        
        // Small talk to the player (Coming soon)
        banter(player.skill);
        
        // Time the level started
        time_t startTime = time(NULL);
        
        // Draw background then overwrite it with the board
        drawBackground(MARGIN - 2, MARGIN - 3, BLOCK_HEIGHT*player.getBoard.height + 4, BLOCK_WIDTH*player.getBoard.width + 4);
        boardPrint(player.getBoard, "Level: " + to_string(player.skill));
        
        boxDrawing(20, 45, 71, 1);
        
        
        while (1){
            // Check to see if the board need to be arrange based on skill or the board is already arraged
            if (rearrange(player))
                boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                
            int key = -1;
            
            // A non blocking input (If there is no input -> skip and go to next line)
            if (_kbhit()){
                key = _getch();
                // cout << "Key: " << key << endl;
            }
            
            // If ESC -> pauseScreen
            if (key == 27){
                pauseScreen(startTime, player);
            }
            
            // If Space key -> select the points
            else if (key == 32){
                // Fill up point1 and point2
                if (player.getBoard.point1 == make_pair(-1, -1)){
                    player.getBoard.point1 = player.getBoard.highlight;
                }
                else if (player.getBoard.point2 == make_pair(-1, -1)){
                    player.getBoard.point2 = player.getBoard.highlight;
                }
                
                // pathSearch() activated when 2 points were filled
                if (player.getBoard.point1 != make_pair(-1, -1) && player.getBoard.point2 != make_pair(-1, -1)){
                    cout << "Search for path" << endl;
                    if (pathSearch(player.getBoard.board, player.getBoard.height, player.getBoard.width, player.getBoard.point1.first, player.getBoard.point1.second, player.getBoard.point2.first, player.getBoard.point2.second)){
                        boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                        // Sleep(200);
                        // Reset 2 highlighted points
                        player.getBoard.point1 = player.getBoard.point2 = make_pair(-1, -1);
                        player.getBoard.hint1 = player.getBoard.hint2 = make_pair(-1, -1);
                        
                        drawBackground(MARGIN - 2, MARGIN - 3, BLOCK_HEIGHT*player.getBoard.height + 4, BLOCK_WIDTH*player.getBoard.width + 4);
                        
                        boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                    }
                    else {
                        cout << "No path found";
                        // Sleep(200);
                        player.getBoard.point1 = player.getBoard.point2 = make_pair(-1, -1);
                        player.getBoard.hint1 = player.getBoard.hint2 = make_pair(-1, -1);
                        boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                    }
                    
                }
                
                solveState = isSolvable(player.getBoard);
                
            }
            
            // If H -> Hint
            else if (key == 'h'){
                isSolvable(player.getBoard, true, true);
                boardPrint(player.getBoard, "Level: " + to_string(player.skill));
            }
            
            // If move -> refresh the actual map
            else if (key == 0 || key == 224){
                key = _getch();
                
                // Arrow keys for navigating the board
                switch (key) {
                    case 72: 
                        // if ()
                        //     drawBackground(MARGIN - 2, MARGIN - 3, BLOCK_HEIGHT*player.getBoard.height + 4, BLOCK_WIDTH*player.getBoard.width + 4);
                        
                        player.getBoard.highlight.second--;
                        if (player.getBoard.highlight.second < 0){
                            player.getBoard.highlight.second = 0;
                            break;
                        }
                        cout << "Up arrow" << endl;
                        break;
                    case 80:
                        player.getBoard.highlight.second++;
                        if (player.getBoard.highlight.second >= player.getBoard.height){
                            player.getBoard.highlight.second = player.getBoard.height - 1;
                            break;
                        }
                        cout << "Down arrow" << endl; 
                        break;
                    case 75: 
                        player.getBoard.highlight.first--;
                        if (player.getBoard.highlight.first < 0){
                            player.getBoard.highlight.first = 0;
                            break;
                        }
                        cout << "Left arrow" << endl; 
                        break;
                    case 77: 
                        player.getBoard.highlight.first++;
                        if (player.getBoard.highlight.first >= player.getBoard.width){
                            player.getBoard.highlight.first = player.getBoard.width - 1;
                            break;
                        }
                        cout << "Right arrow" << endl; 
                        break;
                    case 71: cout << "Home" << endl; break;
                    case 79: cout << "End" << endl; break;
                    case 73: cout << "Page up" << endl; break;
                    case 81: cout << "Page down" << endl; break;
                    case 82: cout << "Insert" << endl; break;
                    case 83: cout << "Delete" << endl; break;
                    default: cout << "Unknown extended key" << endl; break;
                }
                
                drawBackground(MARGIN - 2, MARGIN - 3, BLOCK_HEIGHT*player.getBoard.height + 4, BLOCK_WIDTH*player.getBoard.width + 4);
                boardPrint(player.getBoard, "Level: " + to_string(player.skill));
                solveState = isSolvable(player.getBoard);
            }
                
            // If did not move, do not refresh the map but only refresh the time, stats element (need more work),...
            COORD origin = GetConsoleCaretPos();
            gotoxy(73, 2);
            cout << "Time left: ";
            cout << setw(3) << setfill(' ') << timeLength - (time(NULL) - startTime) << "s";
            gotoxy(73, 3);
            cout << "Player: " << player.name;
            gotoxy(origin.X, origin.Y);
            
            // If board empty, time out or unsolvable -> go to endscreen
            if (time(NULL) - startTime >= timeLength || isEmpty(player.getBoard) || !solveState){
                while (1) {
                    if (isWon || (time(NULL) - startTime < timeLength && (isEmpty(player.getBoard) || !solveState))) {
                        isWon = true;
                        COORD origin = GetConsoleCaretPos();
                        gotoxy(70, 2);
                        cout << "You won";
                        gotoxy(70, 3);
                        cout << "Press Space for next level";
                        gotoxy(origin.X, origin.Y);
                        
                        int key = _getch();
                        
                        origin = GetConsoleCaretPos();
                        gotoxy(70, 4);
                        cout << key;
                        gotoxy(origin.X, origin.Y);
                        
                        if (key == 32)
                            break;
                    }
                    else {
                        COORD origin = GetConsoleCaretPos();
                        gotoxy(70, 2);
                        cout << "Lmao, look at him, he can't count";
                        gotoxy(origin.X, origin.Y);
                    }
                    
                }
                
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 4);
                cout << "Out of while loop";
                gotoxy(origin.X, origin.Y);
            }
                
            // If won -> break out while loop to go to next level
            if (isWon){
                COORD origin = GetConsoleCaretPos();
                gotoxy(70, 5);
                cout << "Break out of while loop";
                Sleep(300);
                gotoxy(origin.X, origin.Y);
                system("cls");
                break;
            }
        }
    }
}

int userInput(string &str, int size = 30){
    
    int key = -1;
    
    if (_kbhit()){
        
        key = _getch();
        
        if (('a' <= key && key <= 'z') || ('A' <= key && key <= 'Z') || ('0' <= key && key <= '9') || key == ' '){
            if (str.size() == size)
                return 0;
            
            str += (char)key;
            
            return 1;
        }
        
        if (key == 13){
            if (str.size() == size)
                return 0;
                
            return 2;
        }
        
        if (key == 8){
            str = str.substr(0, str.size() - 1);
            return -1;
        }
        
    }
    
    return 0;
}

void signInSreen(User player){
    system("cls");
    ShowConsoleCursor(true);
    
    gotoxy(4, 1);
    cout << "Login page";
    
    string name = "";
    string pass = "";
    string blankLine(50, ' ');
    
    gotoxy(4, 2);
    
    while (1){
        
        int status = userInput(name, 49);
        
        if (status == 2)
            break;
        
        
        if (status != 0){
            ShowConsoleCursor(false);
            gotoxy(4, 2);
            cout << blankLine;
            
            gotoxy(4, 2);
            ShowConsoleCursor(true);
            cout << name;
        }
        
    }
    
    gotoxy(4, 3);
    
    while (1){
        int status = userInput(pass, 49);
        
        if (status == 2)
            break;
        
        
        if (status != 0){
            ShowConsoleCursor(false);
            gotoxy(4, 3);
            cout << blankLine;
            
            gotoxy(4, 3);
            ShowConsoleCursor(true);
            cout << pass;
        }
    }
    
    strcpy(player.name, name.substr(0, 49).c_str());
    player.getBoard.board = generateMap(9, 9);
    player.getBoard.height = 9;
    player.getBoard.width = 9;
    player.isLogged = 1;
    
    playScreen(player);
}

void logInScreen(User player){
    
}

void aboutScreen(){
    
}

void leaderboardScreen(){
    system("cls");
    ifstream in("data.bin", ios::binary);
            
    if (in.is_open()){
        // we can’t declare a student array here because we don’t know its size
        // so now we compute the size before reading the file
        in.seekg(0, ios::end);
        int num = in.tellg() / sizeof(User); // file size / struct size
        // cout << "file size: " << in.tellg() << ", struct size: " << sizeof(User) << endl;
        cout << "Players: " << endl;
        in.seekg(0, ios::beg);
        
        
        User* studentsPointers = new User[num + 1]; // now we can declare an array
        for (int i = 0; i < num; ++i) {
            in.read((char*)&studentsPointers[i], sizeof(User));
            cout << studentsPointers[i].name << "\t\t " << studentsPointers[i].skill << endl;
        }
    
        in.close();
        while (1){
            
        }
        // delete[] studentsPointers;
    }
    else{
        cout << "No data found:<" << endl << "So be our first guest!";
        Sleep(8000);
    }
}

void menuScreen(User player, bool skip = false){
    ShowConsoleCursor(false);
    // Skip to play screen
    if (skip){
        playScreen();
        return;
    }
    
    // cout << tintAll("142334") << dyeAll("3a96dd");
    string intro = "A journey made by Quang Huy & Phuc Khang";
    
    int count = 0;
    while (count <= 9){
        gotoxy(0, 0);
        cout << intro.substr(0, count);
        count++;
        Sleep(25);
    }
    
    Sleep(600);
    
    while (count <= intro.size()){
        gotoxy(0, 0);
        cout << intro.substr(0, count);
        count++;
        Sleep(20);
    }
    
    Sleep(1000);
    
    system("cls");
    int selected = 2;
    int screen = 0;
    int borderWidth = 99;
    string spaces(borderWidth, ' ');
    
    gotoxy((120 - borderWidth)/2 + 1, 1);
    COORD startLine = GetConsoleCaretPos();
    for (int i = 0; i < 27; i++){
        cout << tint("142334", spaces);
        gotoxy(startLine.X, startLine.Y + i + 1);
        Sleep(5);
    }
    
    gotoxy((120 - 92)/2, 2);
    startLine = GetConsoleCaretPos();
    for (int i = 0; i < 25; i++){
        cout << fall[i];
        gotoxy(startLine.X, startLine.Y + i + 1);
        Sleep(5);
    }
    
    while (1){
        // cout << tintAll("142334");
        
        gotoxy(20, 15);
        cout << tintAll("3a96dd") << dyeAll("142334") << (selected != 1 ? " \t" : ">\t") << "Start!" << COLOR_RESET << endl;
        gotoxy(20, 16);
        cout << tintAll("3a96dd") << dyeAll("142334") << (selected != 2 ? " \t" : ">\t") << "Login" << COLOR_RESET << endl;
        gotoxy(20, 17);
        cout << tintAll("3a96dd") << dyeAll("142334") << (selected != 3 ? " \t" : ">\t") << "About" << COLOR_RESET << endl;
        gotoxy(20, 18);
        cout << tintAll("3a96dd") << dyeAll("142334") << (selected != 4 ? " \t" : ">\t") << "Leaderboard" << COLOR_RESET << endl;
        
        int c = 0;
        switch((c=getch())) {
            case KEY_DOWN:
                // cout << endl << "Up" << endl;//key up
                if (selected == 4)
                    selected = 1;
                else
                    selected += 1;
                break;
                
            case KEY_UP:
                // cout << endl << "Down" << endl;   // key down
                if (selected == 1)
                    selected = 4;
                else
                    selected -= 1;
                break;
                
            case ' ':
                screen = selected;
                break;
            
            default:
                // cout << endl << "null" << endl;  // not arrow
                break;
        }
        
        switch (screen){
            case 1:
                screen = 0;
                playScreen();
                break;
            case 2:
                screen = 0;
                signInSreen(player);
                break;
            case 3:
                screen = 0;
                aboutScreen();
                break;
            case 4:
                screen = 0;
                leaderboardScreen();
                break;
        }
    }
}
