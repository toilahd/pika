#include <fstream>
#include <iostream>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>
#include <Windows.h>

#include "engine/tryingout.hpp"

// #include "./engine/tryingout.hpp"
#include "engine/dataType.hpp"


int main(int argc, char *argv[]){
	// User students[1];
	
	// strcpy(students[0].name, "phkahng");
	
	// int num = 1;
	// ofstream f("data.bin", ios::binary);
	
	// for (int i = 0; i < num; ++i) {
	// 	f.write((char*)&students[i], sizeof(User));
	// }
	
	// f.close();
	
	
	
	
	// ifstream in("data.bin", ios::binary);
	
	// // we can’t declare a student array here because we don’t know its size
	// // so now we compute the size before reading the file
	// in.seekg(0, ios::end);
	// num = in.tellg() / sizeof(User); // file size / struct size
	// cout << "file size: " << in.tellg() << ", struct size: " << sizeof(User) << endl;
	// in.seekg(0, ios::beg);
	
	// User* studentsPointers = new User[num]; // now we can declare an array
	// for (int i = 0; i < num; ++i) {
	// 	in.read((char*)&studentsPointers[i], sizeof(User));
	// cout << studentsPointers[i].name << endl;
	// }
	
	// delete[] studentsPointers;
	
	// PlaySound("C:\\Users\\phkhng\\Desktop\\Let The Rain Kiss You.wav", 0, SND_FILENAME | SND_ASYNC);
	mciSendString("play \"C:\\Users\\phkhng\\Desktop\\Let The Rain Kiss You.wav\"", NULL, 0, NULL);
	Sleep(2000);
	// PlaySound("C:\\Users\\phkhng\\Music\\Indoor Kei Nara Trackmaker_Stems_128bpm\\CHpercpluck.wav", 0, SND_FILENAME | SND_ASYNC);
	
	
	Sleep(15000);
	
	return 0;
}

void myFileTest(){
	User player[1];
	strcpy(player[0].name, "Player 1");
	player[0].skill = 3;
	
	ofstream out("data.bin", ios::binary);
	out.write((char *)&player[0], sizeof(User));
	
	out.close();

	ifstream in;
	
	in.open("data.bin", ios::binary);
	
	if (in.is_open()){
		in.seekg(0, ios::end);
                
		int amount = in.tellg() / sizeof(User);
		
        cout << "file size: " << in.tellg() << ", struct size: " << sizeof(User);
		cout << amount << endl;
		
		in.seekg(0, ios::beg);
		
		User *users = new User[amount + 1];
		
		for (int i = 0; i < amount; i++){
			in.read((char *)&users[i], sizeof(User));
		}
		
		for (int i = 0; i < amount; i++)
			cout << users[i].name << endl;
		
		// bool found = false;
		// for (int i = 0; i < amount; i++){
		// 	if (users[i].name == player.name/*  && users[i].pass == player.pass */){
		// 		users[i].skill = player.skill;
		// 		cout << users[i].skill << endl;
		// 		found = true;
		// 	}
		// }
		
		// if (found == false)
			// cout << "No result";
	}
	// else
	// 	cout << "File does not exist" << endl;
}