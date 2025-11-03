#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "file_utils.h"
using namespace std;

void showMenu() {
    cout << "1. Create new file\n";
    cout << "2. Open existing file\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}
void createFile(const string& filename) {   

    vector<string> lines;
    cout << "Start typing your text (type ':wq' on a new line to save & exit):\n";
    string line;
    while (true) {
        getline(cin, line);
        if (line == ":wq")
            break;
        lines.push_back(line);
    }

    if (!writeToFile(filename, lines)) {
        cerr << "Error creating file!\n";
        return;
    }
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
    int choice; 
    if (argc > 2){
        cout << "Invalid Arguments: Expected only one filename" << endl;
        cout << "Usage: ./termn <filename>" << endl;
        return 0;
    }
    if (argc ==2) {
        /* argc ==2 then first name is the application name and second name 
        is assumed to be the filename 
        */
        string filename = argv[1];
        int action = openFile(filename);
        if (action == 0) {
            cout << "File not found. Creating new file: " << filename << endl;
            createFile(filename);
            cout << "Good Bye ! " << endl;
            return 0;            
        }
    }    
    while(true){
        showMenu();
        cin >> choice;
        cin.ignore();
        switch(choice){
            case 1 : createFileAction();cout << "Good Bye ! " << endl;return 0; 
            case 2 : openFileAction();break;
            case 3 : cout << "GoodBye !!!" ;return 0;
            default: cout << "Invalid Choice \n";break; 
        }
    }
}