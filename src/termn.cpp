#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void showMenu() {
    cout << "\n===== Simple Notepad =====\n";
    cout << "1. Create new file\n";
    cout << "2. Open existing file\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}
void createFile() {
    string filename;
    cout << "Enter filename (with .txt): ";
    cin >> filename;

    ofstream file(filename);
    if (!file) {
        cerr << "Error creating file!\n";
        return;
    }

    cout << "Start typing your text (type ':wq' on a new line to save & exit):\n";
    string line;
    while (true) {
        getline(cin, line);
        if (line == ":wq")
            break;
        file << line << "\n";
    }

    file.close();
    cout << "File saved successfully!\n";
}
void openFile(){
    string filename;
    cout << "Enter filename to open : ";
    cin >> filename;
    cin.ignore();
    ifstream file(filename);
    if(!file){
            cerr << "File Not Found";
            return;
        }    
    cout << "\n----- File Content -----\n";
    string line;
    vector <string> lines ;
    while(getline(file,line)){
        lines.push_back(line);
        cout << line << "\n";

    }
    file.close();
}
int main(){
    int choice;
    while(true){
        showMenu();
        cin >> choice;
        cin.ignore();

        switch(choice){
            case 1 :createFile();break; 
            case 2 : openFile(); break;
            case 3 :cout << "GoodBye !" ;return 0;
            default:cout << "Invalid Choice \n"; 
        }
    }
}