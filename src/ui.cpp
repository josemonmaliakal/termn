#include "../include/ui.h"
#include <fstream>
#include <vector>
#include <iostream>

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

void runEditor(const string& initialFilename) {
    int height, width;
    string filename = initialFilename;
    string saveMsg = "File Cancelled!";

    getmaxyx(stdscr, height, width);

    WINDOW* titlebar = newwin(1, width, 0, 0);
    WINDOW* textwin  = newwin(height - 2, width, 1, 0);
    WINDOW* footer   = newwin(1, width, height - 1, 0);

    scrollok(textwin, TRUE);

    drawTitle(titlebar, filename.empty() ? "[New File]" : filename);
    drawFooter(footer);

    vector<string> buffer;
    string currentLine;
    int ch;

    while ((ch = wgetch(textwin)) != 24) { // Ctrl+X
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

