#pragma once

#include <iostream>

using namespace std;

#define PADDING 500  // bytes
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100

struct Board {                      // Representing a board state
    int p = 0, q = 0;                       // Size of the board game
    int p_, q_;                     // Current cursor position
    char board[BOARDSIZE];          // Current board state
    char file_background[URLSIZE];  // Link to background file. This variable’s
                                    // value is NULL if there is no current
                                    // background
    // 500 byte NULL
    char filler[500];
};

struct Date {
    int dd, mm, yy;
};

struct Record {
    Date date;     // Date of completed record
    int points;  // points achieved
    
    // 500 byte NULL
    char filler[500];
};

struct savefile {
    char mask;  // You are required to transfer all char-type variables by
                // performing xor each with the mask - variable, bit - by - bit.
    char name[NAMESIZE];  // username
    char password[PASSSIZE]; // password
    
    // 500 byte NULL
    // char filler[500];
    
    Record record[5];  // List of sorted best records
    Board state[5];    // List of save state
};

// Before saving-file structures

struct BoardLayout {
    int **board = NULL;
    int width = 0;
    int height = 0;
    char background[URLSIZE] = "";
    pair<int, int> highlight = make_pair(0, 0);
    pair<int, int> point1 = make_pair(-1, -1);
    pair<int, int> point2 = make_pair(-1, -1);
    pair<int, int> hint1 = make_pair(-1, -1);
    pair<int, int> hint2 = make_pair(-1, -1);
};

struct User {
    char name[30] = "";
    char pass[20] = "";
    int isLogged = 0;
    int skill = 0;
    char ass[8] = "";
    char id[10] = "";
    BoardLayout getBoard;
};