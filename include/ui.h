#ifndef UI_H
#define UI_H
#include <string>
#include <ncurses.h>

void initUI();
void shutdownUI();
void drawTitle(WINDOW* win, const std::string& filename);
void drawFooter(WINDOW* win);
void runEditor(const std::string& filename);
void showMenu();

#endif
