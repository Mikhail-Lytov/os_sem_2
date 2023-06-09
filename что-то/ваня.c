#include <ncurses.h>
#include <stdio.h>
int main(int argc, char argv[])
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    int exit = 0, lx = COLS/2,ly = LINES/2;
    int lyL = ly,lxX = lx, lyL1 = lyL, lxX1 = lxX, ly2 = lyL1, lx2 = lxX1;
    do {
    mvaddch(ly,lx,'*');
    lx2 = lxX1;
    lxX1 = lxX;
    lxX = lx;
    ly2 = lyL1;
    lyL1 = lyL;
    lyL = ly;
    //mvaddch(ly,lx,' ');

    switch(exit) {
    case KEY_UP:
        ly = (ly + COLS - 1) % COLS;
        break;
    case KEY_DOWN:
        ly = (ly + 1) % LINES;
        break;
    case KEY_LEFT:
        lx = (lx + LINES - 1) % LINES;
        break;
    case KEY_RIGHT:
        lx = (lx + 1) % COLS;
        break;
    default:
        break;
    }
    mvaddch(ly2,lx2,' ');
    refresh();
    }while('q' != (exit = getch()));
    endwin();
    return 0;
}