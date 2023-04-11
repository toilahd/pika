#include <iostream>
#include <fstream>

using namespace std;

struct Data {
    char name[30] = "Khang";
    int numbers[81] = {0};
    char id[10] = "8472567";
};

int main(){
    Data info;
    
    int count = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++){
            info.numbers[i + j] = count;
            count ++;
        }
            
    ofstream out("binData.bin", ios::binary);
    out.write((char *)&info, sizeof(Data));
    out.close();
    
    Data infoFromFile;
    ifstream in("binData.bin", ios::binary);
    in.read((char *)&infoFromFile, sizeof(Data));
    
    cout << "Name: " << infoFromFile.name << endl;
    cout << "ID: " << infoFromFile.id << endl;
    
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
            cout << "[" << infoFromFile.numbers[i + j] << "]";
        cout << endl;
    }
    
    return 0;
}