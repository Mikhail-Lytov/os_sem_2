#include <ncurses.h>
#include <stdio.h>

 int main(int arqc, char* argv[]){
    
    
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);

    int x_left = COLS / 2 - 3, y_left = LINES/2;
    int x_left_1 = COLS / 2 - 3, y_left_1 = LINES/2;
    int x_left_2 = COLS / 2 - 3, y_left_2 = LINES/2;
    int x_left_3 = COLS / 2 - 3, y_left_3 = LINES/2;
    int x_left_4 = COLS / 2 - 3, y_left_4 = LINES/2;
    int x_left_5 = COLS / 2 - 3, y_left_5 = LINES/2;


    int x_right = COLS / 2 + 3, y_right = LINES/2;
    int x_right_1 = COLS / 2 + 3, y_right_1 = LINES/2;
    int x_right_2 = COLS / 2 + 3, y_right_2 = LINES/2;
    int x_right_3 = COLS / 2 + 3, y_right_3 = LINES/2;
    int x_right_4 = COLS / 2 + 3, y_right_4 = LINES/2;
    int x_right_5 = COLS / 2 + 3, y_right_5 = LINES/2;

    int x_up = COLS / 2, y_up = LINES/2 + 3;
    int x_up_1 = COLS / 2, y_up_1 = LINES/2 + 3;
    int x_up_2 = COLS / 2, y_up_2 = LINES/2 + 3;
    int x_up_3 = COLS / 2, y_up_3 = LINES/2 + 3;
    int x_up_4 = COLS / 2, y_up_4 = LINES/2 + 3;
    int x_up_5 = COLS / 2, y_up_5 = LINES/2 + 3;

    int x_down = COLS / 2, y_down = LINES/2 - 3;
    int x_down_1 = COLS / 2, y_down_1 = LINES/2 - 3;
    int x_down_2 = COLS / 2, y_down_2 = LINES/2 - 3;
    int x_down_3 = COLS / 2, y_down_3 = LINES/2 - 3;
    int x_down_4 = COLS / 2, y_down_4 = LINES/2 - 3;
    int x_down_5 = COLS / 2, y_down_5 = LINES/2 - 3;
    int ch = 0;

    int stop = 0;
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLUE);

    while(ch != 'q'){
        attron(COLOR_PAIR(1));
        mvaddch(y_left,x_left,'*');
        mvaddch(y_left_1,x_left_1,'*');
        mvaddch(y_left_2,x_left_2,'*');
        mvaddch(y_left_3,x_left_3,'*');
        mvaddch(y_left_4,x_left_4,'*'); 
        mvaddch(y_up,x_up ,'*');
        mvaddch(y_right,x_right,'*');
        mvaddch(y_down,x_down,'*');
        attroff(COLOR_PAIR(1)); 
        refresh();
        refresh();

        ch = getch();

        x_down_5 = x_down_4;
        x_down_4 = x_down_3;
        x_down_3 = x_down_2;
        x_down_2 = x_down_1;
        x_down_1 = x_down;
        y_down_5 = y_down_4;
        y_down_4 = y_down_3;
        y_down_3 = y_down_2;
        y_down_2 = y_down_1;
        y_down_1 = y_down;

        x_up_5 = x_up_4;
        x_up_4 = x_up_3;
        x_up_3 = x_up_2;
        x_up_2 = x_up_1;
        x_up_1 = x_up;
        y_up_5 = y_up_4;
        y_up_4 = y_up_3;
        y_up_3 = y_up_2;
        y_up_2 = y_up_1;
        y_up_1 = y_up;


        x_left_5 = x_left_4;
        x_left_4 = x_left_3;
        x_left_3 = x_left_2;
        x_left_2 = x_left_1;
        x_left_1 = x_left;
        y_left_5 = y_left_4;
        y_left_4 = y_left_3;
        y_left_3 = y_left_2;
        y_left_2 = y_left_1;
        y_left_1 = y_left;

        x_right_5 = x_right_4;
        x_right_4 = x_right_3;
        x_right_3 = x_right_2;
        x_right_2 = x_right_1;
        x_right_1 = x_right;
        y_right_5 = y_right_4;
        y_right_4 = y_right_3;
        y_right_3 = y_right_2;
        y_right_2 = y_right_1;
        y_right_1 = y_right;

        switch(ch){
            case KEY_LEFT:
                y_left = (y_left + LINES - 1) % LINES;
                y_right = (y_right+1) % LINES;
                x_up = (x_up + COLS - 1) % COLS;
                x_down = (x_down+1) % COLS;
                break;
            case KEY_RIGHT:
                y_left = (y_left+1) % LINES;
                y_right = (y_right + LINES - 1) % LINES;
                x_up = (x_up+1) % COLS;
                x_down = (x_down + COLS - 1) % COLS;
                break;
            case KEY_DOWN:
                x_left = (x_left + 1) % COLS;
                x_right = (x_right + COLS - 1)%COLS;
                y_up = (y_up + LINES - 1) % LINES;
                y_down = (y_down+1) % LINES;
                break;
            case KEY_UP:
                x_left = (x_left + COLS - 1)%COLS;
                x_right = (x_right + 1) % COLS;
                y_up = (y_up+1) % LINES;
                y_down = (y_down + LINES - 1) % LINES;

                break;
            default:
                break;
            }

        
        if (stop > 3){
        mvaddch(y_left,x_left,' ');
        mvaddch(y_left_1,x_left_1,' ');
        mvaddch(y_left_2,x_left_2,' ');
        mvaddch(y_left_3,x_left_3,' ');
        mvaddch(y_left_4,x_left_4,' '); 
        mvaddch(y_left_5,x_left_5,' ');
        mvaddch(y_right_5,x_right_5,' ');
        mvaddch(y_up_5,x_up_5,' ');
        mvaddch(y_down_5,x_down_5,' ');
        }
        stop += 1;


        }
        endwin();
        return 0;
}