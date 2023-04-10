#include "menu.h"

int main(){
    SetConsoleOutputCP(65001);
    system("cls");
    bool check = false;
    string name;
    string password;
    cout << "◊ 1. Login \n"
         << "│\n" <<
            "◊ 2. Register" << endl;
    int choice;
    cout << "│ ";
    cin >> choice;
    while(!check){
        if (choice == 1){
            check = true;
            cout << "│\n" 
                 << "◊ Enter your username: \n" << "│ ";
            cin >> name;
            cout << "│\n" 
                 << "◊ Enter your password: \n" << "│ ";
            cin >> password;
            cout << "◊ Loading...." << endl ;
            Sleep(1000); 
            cout << "│ " << endl;
            cout << "◊ Login successfully!";
            drawMenu();

        } 
    else if (choice == 2){
            check = true;
            cout << "│\n" 
                 << "◊ Enter username: \n" << "│ ";
            cin >> name;
            cout << "│\n" 
                 << "◊ Create a password: \n" << "│ ";
            cin >> password;
            cout << "│\n" 
                 << "◊ Confirm password: \n" << "│ ";
            cin >> password;
            Sleep(1000); 
            cout << "│ " << endl;
            cout << "◊ Register successfully!";
            drawMenu();

        }
    else{
            cout << "◊ Invalid choice";
            break;
        }
    }
    return 0;
}