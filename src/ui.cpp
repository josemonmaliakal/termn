#include "../include/ui.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

void initUI() {
    system("stty -ixon"); 
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
}

void shutdownUI() {
    endwin();
}

void drawTitle(WINDOW* win, const string& filename) {
    wattron(win, A_REVERSE);
    werase(win);
    mvwprintw(win, 0, 0, " termn - Editing: %s ", filename.c_str());
    wattroff(win, A_REVERSE);
    wrefresh(win);
}

void drawFooter(WINDOW* win) {
    wattron(win, A_REVERSE);
    werase(win);
    mvwprintw(win, 0, 2, "^S Save");
    mvwprintw(win, 0, 15, "^X Exit");
    wattroff(win, A_REVERSE);
    wrefresh(win);
}

void runEditor(const string& initialFilename, const int& filec, const int&filet) {
    int height, width;
    string filename = initialFilename;
    string saveMsg = "File Cancelled!";

    getmaxyx(stdscr, height, width);

    WINDOW* titlebar = newwin(1, width, 0, 0);
    WINDOW* textwin  = newwin(height - 2, width, 1, 0);
    WINDOW* footer   = newwin(1, width, height - 1, 0);

    scrollok(textwin, TRUE);
    // Enable keypad mode once 
    // To support arrow-key cursor movement inside  ncurses
    keypad(textwin, TRUE);

    std::ostringstream tstring;
    tstring << "[FILES " << filec << "/" << (filet - 1) << "] "\
          << (filename.empty() ? "[New File]" : filename);
    std::string title = tstring.str();
    drawTitle(titlebar,title);
    drawFooter(footer);


    vector<string> buffer;
    string currentLine;

    // Load file if it exists

    if (!filename.empty()){
        ifstream infile(filename);
        string line;
        while (getline(infile, line )){
            buffer.push_back(line);
            wprintw(textwin, "%s\n", line.c_str());

        }
        infile.close();
    }

    int ch;

    while ((ch = wgetch(textwin)) != 24) { // Ctrl+X
        
        int y, x;
        // getting y,x position 
        getyx(textwin, y, x);
        // variable to track movement to avoid refresh after every keystroke 
        bool moved = false;
        switch (ch){
            // Handling Arrow keys 
            case KEY_LEFT:
                if (x > 0){x--;moved = true;}
                break;
            case KEY_RIGHT:
                x++; 
                moved = true;
                break;
            case KEY_UP:
                if (y > 0){y--;moved = true;}
                break;
            case KEY_DOWN:
                y++; 
                moved = true;
                break;
        }
        if (moved){
            wmove(textwin, y, x);   // cheap
            wrefresh(textwin);      // expensive — do only when necessary
            continue;
        }

        if (ch == 19) { // Ctrl+S
            // Ask for filename if none
            if (filename.empty()) {
                echo();
                mvwprintw(footer, 0, 0, "Save as: ");
                wrefresh(footer);
                char fname[256];
                wgetnstr(footer, fname, 255);
                filename = fname;
                noecho();
                // Clear footer after input
                werase(footer);
                drawFooter(footer);
            
            }
            if (!currentLine.empty()) {
                // If not pressed enter pushes current line content to file
                buffer.push_back(currentLine);
                currentLine.clear();

            }
            if (!filename.empty()){
                ofstream out(filename);
                for (auto& line : buffer)
                    out << line << "\n";
                out.close();
                saveMsg = "File saved!";
            }
            mvwprintw(footer, 0, width - 20, "%s", saveMsg.c_str());  
            wrefresh(footer);
            continue;
        }

        if (ch == '\n') {
            buffer.push_back(currentLine);
            currentLine.clear();
            waddch(textwin, '\n');
        } else if (ch == KEY_BACKSPACE || ch == 127) {
            if (!currentLine.empty()) {
                currentLine.pop_back();
                int y, x;
                getyx(textwin, y, x);
                if (x > 0) mvwdelch(textwin, y, x - 1);
            }
        } else {
            currentLine.push_back((char)ch);
            waddch(textwin, ch);
        }
        wrefresh(textwin);
    }

    if (!currentLine.empty()) buffer.push_back(currentLine);

    ofstream out(filename);
    for (auto& line : buffer)
        out << line << "\n";
    out.close();

    shutdownUI();
}

