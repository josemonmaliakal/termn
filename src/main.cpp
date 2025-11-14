#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>  // For system("clear")
#include "../include/file_utils.h"
#include "../include/ui.h"
using namespace std;


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
    initUI();   
    for (int i =1;i<argc;i++){
        runEditor(argv[i],i,argc);
    } 
}