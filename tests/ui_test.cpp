#include "../include/ui.h"
#include <cassert>
#include <iostream>

int main() {
    initscr();
    int width, height;

    getmaxyx(stdscr, height, width);
    mvprintw(height - 1, 0, "Test footer line");

    WINDOW* win = newwin(1, width, 0, 0);

    drawTitle(win, "demo.txt");
    drawFooter(win);

    delwin(win);
    endwin();

    std::cout << "✅ ui_test executed without errors\n";
    return 0;
}
