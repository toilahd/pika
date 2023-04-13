#include <iostream>
#include <fstream>
#include <cstring>

#include "dataType.hpp"

using namespace std;

int main(){
    ifstream in;
    in.open("../data.bin", ios::binary);
	
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
    
    return 0;
}