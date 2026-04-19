#include <ncurses.h>
#include "../include/ui.h"
#include "../include/save.h"
#include "../include/game.h"
#include <unistd.h>
#define GO_RESTART 0
#define GO_MENU 1
#define GO_QUIT 2
int startScreen(int h, int w) {
    int menuIndex=0;
    char *options[] = {"New Game", "Resume Game","Quit"};

    nodelay(stdscr, FALSE);

    while(1) {
        clear();
        box(stdscr,0,0);

        mvprintw(h/2 - 2, w/2 - 5, "WELCOME TO SNAKE XENZIA");

        for (int i = 0; i < 3; i++) {
            if (i == menuIndex) {
                attron(A_REVERSE);
                mvprintw(h/2 + i, w/2 - 8, "%s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(h/2 + i, w/2 - 8, "%s", options[i]);
            }
        }
        refresh();

        int ch = getch();

        if (ch == KEY_UP)
            menuIndex = (menuIndex + 2) % 3;
        else if (ch == KEY_DOWN)
            menuIndex = (menuIndex + 1) % 3;
        else if (ch == '\n' || ch == KEY_ENTER)
            return menuIndex;
    }
}
int chooseDifficulty(int h, int w){
    int idx = 1;
    char* options[] = {"Slow", "Medium", "Fast","Hardcore"};
    while(1){
        clear();
        box(stdscr,0,0);
        mvprintw(h/2 - 2, w/2 - 6,"Select Difficulty");
        for(int i=0;i<4;i++){
            if(i==idx){
                attron(A_REVERSE);
                mvprintw(h/2 + i, w/2 - 4,"%s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(h/2 + i, w/2 - 4, "%s", options[i]);
            }
        }
        refresh();
        int ch = getch();
        if(ch == KEY_UP) idx = (idx + 3)%4;
        else if(ch == KEY_DOWN) idx = (idx + 1)%4;
        else if(ch == '\n') return idx;
    }
}
int gameOverScreen(int h, int w, int score) {
    int highscore = loadHighScore();
    char *options[] = {"Restart", "Main Menu","Quit"};
    char *diffStr[] = {"Slow", "Medium", "Fast","Hardcore"};
    int menuIndex = 0;
    nodelay(stdscr, FALSE);
while(1) {
    clear();
    box(stdscr,0,0);
    mvprintw(h/2 - 4,w/2 - 3, "GAME OVER");
    mvprintw(h/2 - 3, w/2 - 7, "Final Score: %d",100*score);
    mvprintw(h/2-2,w/2 - 7,"Highest Score: %d",100*highscore);
    mvprintw(h/2-1,w/2 - 7,"Difficulty: %s",diffStr[difficulty]);
    for (int i = 0; i < 3; i++) {
        if (i == menuIndex) {
            attron(A_REVERSE);
            mvprintw(h/2 + i + 1, w/2 - 6, "%s", options[i]);
            attroff(A_REVERSE);
        } else {
            mvprintw(h/2 + i + 1, w/2 - 6, "%s", options[i]);
        }
    }

    refresh();

    int ch = getch();

    if (ch == KEY_UP){
        menuIndex = (menuIndex + 3)%4;
    }
    else if (ch == KEY_DOWN){
        menuIndex = (menuIndex + 1)%4;
    }
    else if(ch=='\n') {
        return menuIndex;
    }
    }
}
int chooseSlotUI(int h, int w){
    int menuIndex = 0;
    
    while(1){
        clear();
        box(stdscr,0,0);
        attron(A_BOLD);
        mvprintw(h/2,w/2 - 6, "Choose slot");
        attroff(A_BOLD);  
        char *options[] = {"Slot 1", "Slot 2", "Slot 3"};
               
        for (int i = 0; i < 3; i++){
            if (i == menuIndex){
                attron(A_REVERSE);
                mvprintw(h/2 + i+1, w/2 - 6, "%s", options[i]);
                attroff(A_REVERSE);
            }
                else 
                mvprintw(h/2 + i+1, w/2 - 6, "%s", options[i]);
        }

        refresh();

        int ch = getch();
        if (ch==KEY_UP) {
            menuIndex=(menuIndex + 2)%3;
        }
        else if (ch==KEY_DOWN) {
            menuIndex=(menuIndex + 1)%3;
        }
        else if (ch=='\n' || ch==KEY_ENTER){
            return menuIndex+1;
        }
        usleep(80000);
    }
}
 
