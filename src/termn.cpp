#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void showMenu() {
    cout << "1. Create new file\n";
    cout << "2. Open existing file\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}
void createFile(const string& filename) {   

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
void createFileAction(){
    string filename;
    cout << "Enter filename (with .txt): ";
    cin >> filename;
    createFile(filename);
}
int openFile(const string& filename){    
    ifstream file(filename);
    if(!file){
            cerr << "File Not Found";
            return 0;
        }    
    string line;
    vector <string> lines ;
    while(getline(file,line)){
        lines.push_back(line);
        cout << line << "\n";

    }
    file.close();
    return 1;
}
void openFileAction(){
    string filename;
    cout << "Enter filename to open : ";
    cin >> filename;
    cin.ignore();
    openFile(filename);    
}
int main(int argc , char* argv[]){
    int action=0;
    if (argc > 2){
        cout << "Invalid Arguments: Expected only one filename" << endl;
        cout << "Usage: ./termn <filename>" << endl;
        return 1;
    }
    if (argc ==2) {
        string filename = argv[1];
        int action = openFile(filename);
        if (action == 0) {
            cout << "File not found. Creating new file: " << filename << endl;
            createFile(filename);
        }
        
    }    
    int choice; 

    while(true){
        showMenu();
        cin >> choice;
        cin.ignore();

        switch(choice){
            case 1 : createFileAction();cout << "Good Bye ! ";return 0; 
            case 2 : openFileAction();break;
            case 3 : cout << "GoodBye !!!" ;return 0;
            default: cout << "Invalid Choice \n";break; 
        }
    }
}