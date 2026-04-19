#include <ncurses.h>
#include "../include/game.h"
#include "../include/ui.h"
#include "../include/save.h"
#include "../include/obstacle.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define GAME_OVER 0
#define RESTART 1
#define EXIT_GAME -1
#define SAVE_EXIT -2
#define GO_RESTART 0
#define GO_MENU 1
#define GO_QUIT 2
int main(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    srand(time(NULL));
    int h, w;
    getmaxyx(stdscr, h, w);
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4,COLOR_WHITE,COLOR_BLACK);
    init_pair(5,COLOR_CYAN,COLOR_BLACK);
    while(1) {
        int choice = startScreen(h,w);
        int mode;
        if(choice == 2) break;
        if(choice == 0) {
            difficulty = chooseDifficulty(h,w);
        }
        mode = choice;
        while (1) {
        int score = 0;
        int result;
        int old_score = 0;
        if(mode == 0) {
            result = runGame(h,w, &score);
        }
        else {
            int dx, dy, food_x, food_y;
            int slot = chooseSlotUI(h,w);
            Node* snake = loadGame(slot,&dx, &dy, &food_x, &food_y, &old_score,&obstacleCount,obstacles);
            if(!snake) {
                mvprintw(h-2,2,"No saved game found!");
                refresh();
                sleep(1);
                result = runGame(h, w,&score);
            } else {
                //remove("save.csv");
                result = runGameLoaded(h, w, snake, dx, dy, food_x, food_y, old_score,&score);
            }
        }
        
        if (result == EXIT_GAME) {
            endwin();
            return 0;
        }
        if (result == SAVE_EXIT) {
            break;
        }
        if (result == RESTART) {
            mode = 0;
            continue;
        }

        int go = gameOverScreen(h,w,score);

        if (go == GO_RESTART) {
            mode = 0;
            continue;
        }
        else if (go == GO_MENU) {
            break;
        }
        else if (go == GO_QUIT) {
            endwin();
            return 0;
        }
        }
    }
    
    endwin();
    return 0;
}