#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../include/snake.h"
#include "../include/render.h"
#include "../include/game.h"
#include "../include/save.h"
#include "../include/obstacle.h"
#include "../include/ui.h"
#define UI_HEIGHT 3
#define GAME_OVER 0
#define RESTART 1
#define EXIT_GAME -1
#define SAVE_EXIT -2
int difficulty = MEDIUM;
int getlevel(int len){
    return len/3;
}
int runGame(int h, int w,int* score1){
    Node* snake=NULL;
    obstacleCount = 0;
    int lastObstacleLevel;
    lastObstacleLevel = 0;
    int x = w/2;
    int y = h/2;
    addHead(&snake,x,y);
    
    int dx = 1, dy = 0;
    
    int food_x, food_y;
    
    food_x=rand() % (w-2) + 1;
    food_y=rand() % (h - UI_HEIGHT-1) + UI_HEIGHT;
    
    while(inSnake(food_x,food_y,snake))
    {
        food_x=rand()% (w-2) + 1;
        food_y=rand()% (h - UI_HEIGHT-1) + UI_HEIGHT;
    }
    int score = 0;
    int paused = 0;
    int menuIndex = 0;
    int len = snakeLength(snake);
    int level = getlevel(len);
    nodelay(stdscr, TRUE);
    while(1) {
        clear();  
        box(stdscr,0,0);
        drawSnake(snake);
        drawFood(food_x,food_y);
        drawScore(score);
        drawObstacles();

        refresh();
        int baseSpeed;

        if(difficulty == SLOW) baseSpeed=120000;
        else if(difficulty == MEDIUM) baseSpeed=90000;
        else if(difficulty == FAST) baseSpeed = 60000;
        else baseSpeed=110000;
        int speed = baseSpeed - score*1500;
        if (speed < 30000) speed = 30000;
        int ch = getch();

        if(ch == 'q') {
            *score1 = score;
            saveHighScore(*score1);
            return EXIT_GAME;
        }
        if (ch == 'p') {
            paused = !paused;
            menuIndex = 0;
        }
        int moved = 0;
        if (!paused) {        
        if ((ch == 'w' || ch == KEY_UP) && dy!=1) {
            dx = 0; dy = -1; moved = 1;
        }
        else if ((ch == 'a' || ch == KEY_LEFT) && dx!=1) {
            dx = -1; dy = 0; moved = 1;
        }
        else if ((ch == 's' || ch == KEY_DOWN) && dy!=-1) {
            dx = 0; dy = 1; moved = 1;
        }
        else if ((ch == 'd' || ch == KEY_RIGHT) && dx!=-1) {
            dx = 1; dy = 0; moved = 1;
        }
        }

        if (paused) {
            while (paused) {
                clear();
                box(stdscr,0,0);
                drawSnake(snake);
                drawFood(food_x,food_y);
                drawScore(score);
                drawObstacles();
                mvprintw(h/2,w/2 - 6, "==== PAUSED ====");

                char *options[] = {"Resume", "Restart", "Save & Exit","Quit"};

                for (int i = 0; i < 4; i++){
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
                    menuIndex=(menuIndex + 3)%4;
                }
                else if (ch==KEY_DOWN) {
                    menuIndex=(menuIndex + 1)%4;
                }
                else if (ch=='\n' || ch==KEY_ENTER){
                    if (menuIndex==0){
                        paused=0;
                    }
                    else if(menuIndex==1){
                        *score1=score;
                        saveHighScore(*score1);
                        return RESTART;
                    }
                    else if(menuIndex==2) {
                        int slot = chooseSlotUI(h,w);
                        saveGame(slot,snake,dx,dy,food_x,food_y,score,obstacleCount,obstacles);
                        *score1=score;
                        saveHighScore(*score1);
                        return SAVE_EXIT;
                    }
                    else if(menuIndex==3) {
                        *score1=score;
                        saveHighScore(*score1);
                        return EXIT_GAME;
                    }
                }
                else if (ch == 'p'){
                    paused=0;
                }
                else if(ch == 'q') {
                    *score1=score;
                    return EXIT_GAME;
                }
                usleep(80000);
            }
            continue;
        }
        if (difficulty ==  HARDCORE) {
            len = snakeLength(snake);
            level = getlevel(len);
            
            if(level > lastObstacleLevel) {
                if(level==1 || level==2) addVerticalWall(w,h);
                else addMovingObstacle(w,h,snake);

                lastObstacleLevel=level;
            }
        
        }
        
        int new_x = snake->x + dx;
        int new_y = snake->y + dy;
        if(new_x<=0) new_x = w - 2;
        if(new_x>=w-1) new_x = 1;
        if(new_y<UI_HEIGHT) new_y = h - 2;
        if(new_y>=h-1) new_y = UI_HEIGHT;
        
        for(int i=0;i<obstacleCount;i++){
            if(obstacles[i].moving){
                obstacles[i].x += obstacles[i].dx;
                obstacles[i].y += obstacles[i].dy;
                if (obstacles[i].x <=1) {
                    obstacles[i].x = 1;
                    obstacles[i].dx *= -1;
                }
                if(obstacles[i].x >= w-2) {
                    obstacles[i].x = w-2;
                    obstacles[i].dx *= -1;
                }
                if(obstacles[i].y <=UI_HEIGHT){
                    obstacles[i].y =UI_HEIGHT;
                    obstacles[i].dy *=-1;
                }
                if(obstacles[i].y>= h-2){
                    obstacles[i].y = h-2;
                    obstacles[i].dy *= -1;
                }
            }
        }
        if(checkCollision(new_x,new_y, snake) || collision(snake))
        {
            *score1=score;
            saveHighScore(*score1);
            return GAME_OVER;
        }
        addHead(&snake, new_x, new_y);
        int ate = (new_x == food_x && new_y == food_y);
        if(ate)
        {
            score++;
            food_x=rand()%(w-2)+1;
            food_y=rand()%(h-UI_HEIGHT-1) + UI_HEIGHT;
            while(inSnake(food_x,food_y,snake)|| isObstacle(food_x,food_y))
            {
                food_x=rand()%(w-2)+1;
                food_y=rand()%(h - UI_HEIGHT-1) + UI_HEIGHT;
            }
        }
        else
        {
            removeBack(&snake);
        } 
        usleep(speed);
    }
    *score1=score;
    saveHighScore(*score1);
    return GAME_OVER;
}
int runGameLoaded(int h1, int w1, Node* snake1, int dx1, int dy1, int food_x1, int food_y1, int old_score, int* score1){
    Node* snake=snake1;
    int h=h1;
    int w=w1;
    int x = w/2;
    int y = h/2;
    
    int dx = dx1, dy = dy1;
    
    int food_x, food_y;
    
    food_x=food_x1;
    food_y=food_y1;
    
    int score=old_score;
    int paused = 0;
    int menuIndex = 0;
    int len=snakeLength(snake);
    int level = getlevel(len);
    int lastObstacleLevel =level;
    nodelay(stdscr, TRUE);
    flushinp();
    while(1) {
        clear();  
        refresh();
        box(stdscr,0,0);
        drawSnake(snake);
        drawFood(food_x,food_y);
        drawScore(score);
        drawObstacles();
        refresh();

        int baseSpeed;

        if(difficulty == SLOW) baseSpeed=120000;
        else if(difficulty == MEDIUM) baseSpeed=90000;
        else if(difficulty == FAST) baseSpeed = 60000;
        else baseSpeed=110000;
        int speed = baseSpeed - score*1500;
        if (speed < 30000) speed = 30000;
        int ch = getch();

        if(ch == 'q') {
            *score1 = score;
            saveHighScore(*score1);
            return EXIT_GAME;
        }
        if (ch == 'p') {
            paused = !paused;
            menuIndex = 0;
        }
        if (!paused) {
        if ((ch == 'w' || ch == KEY_UP) && dy!=1) {
            dx = 0; dy = -1;
        }
        else if ((ch == 'a' || ch == KEY_LEFT) && dx!=1) {
            dx = -1; dy = 0;
        }
        else if ((ch == 's' || ch == KEY_DOWN) && dy!=-1) {
            dx = 0; dy = 1;
        }
        else if ((ch == 'd' || ch == KEY_RIGHT) && dx!=-1) {
            dx = 1; dy = 0;
        }
        }
        if (paused) {
            while (paused) {
                clear();
                box(stdscr,0,0);
                drawSnake(snake);
                drawFood(food_x,food_y);
                drawScore(score);
                drawObstacles();
                attron(A_BOLD);
                mvprintw(h/2,w/2 - 6, "==== PAUSED ====");
                attroff(A_BOLD);  
                char *options[] = {"Resume", "Restart", "Save & Exit","Quit"};

                for (int i = 0; i < 4; i++){
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
                    menuIndex=(menuIndex + 3)%4;
                }
                else if (ch==KEY_DOWN) {
                    menuIndex=(menuIndex + 1)%4;
                }
                else if (ch=='\n' || ch==KEY_ENTER){
                    if (menuIndex==0){
                        paused=0;
                    }
                    else if(menuIndex==1){
                        *score1=score;
                        saveHighScore(*score1);
                        return RESTART;
                    }
                    else if(menuIndex==2) {
                        int slot = chooseSlotUI(h,w);
                        saveGame(slot,snake,dx,dy,food_x,food_y,score,obstacleCount,obstacles);
                        *score1=score;
                        saveHighScore(*score1);
                        return SAVE_EXIT;
                    }
                    else if(menuIndex==3) {
                        *score1=score;
                        saveHighScore(*score1);
                        return EXIT_GAME;
                    }
                }
                else if (ch == 'p'){
                    paused=0;
                }
                else if(ch == 'q') {
                    *score1=score;
                    saveHighScore(*score1);
                    return EXIT_GAME;
                }
                usleep(80000);
            }
            continue;
        }
        if (difficulty ==  HARDCORE) {
            len = snakeLength(snake);
            level = getlevel(len);
            
            if(level > lastObstacleLevel) {
                if(level==1 || level==2) addVerticalWall(w,h);
                else addMovingObstacle(w,h,snake);

                lastObstacleLevel=level;
            }
        
        }
        int new_x = snake->x + dx;
        int new_y = snake->y + dy;
        if(new_x<=0) new_x = w - 2;
        if(new_x>=w-1) new_x = 1;
        if(new_y<UI_HEIGHT) new_y = h - 2;
        if(new_y>=h-1) new_y = UI_HEIGHT;
        
        for(int i=0;i<obstacleCount;i++){
            if(obstacles[i].moving){
                obstacles[i].x += obstacles[i].dx;
                obstacles[i].y += obstacles[i].dy;
                if (obstacles[i].x <=1) {
                    obstacles[i].x = 1;
                    obstacles[i].dx *= -1;
                }
                if(obstacles[i].x >= w-2) {
                    obstacles[i].x = w-2;
                    obstacles[i].dx *= -1;
                }
                if(obstacles[i].y <=UI_HEIGHT){
                    obstacles[i].y =UI_HEIGHT;
                    obstacles[i].dy *=-1;
                }
                if(obstacles[i].y>= h-2){
                    obstacles[i].y = h-2;
                    obstacles[i].dy *= -1;
                }
            }
        }
        if(checkCollision(new_x,new_y, snake) || collision(snake))
        {
            *score1=score;
            saveHighScore(*score1);
            return GAME_OVER;
        }
        addHead(&snake, new_x, new_y);
        int ate = (new_x == food_x && new_y == food_y);
        if(ate)
        {
            score++;
            food_x=rand()%(w-2)+1;
            food_y=rand()%(h-UI_HEIGHT-1) + UI_HEIGHT;
            while(inSnake(food_x,food_y,snake)|| isObstacle(food_x,food_y))
            {
                food_x=rand()%(w-2)+1;
                food_y=rand()%(h - UI_HEIGHT-1) + UI_HEIGHT;
            }
        }
        else
        {
            removeBack(&snake);
        } 
        usleep(speed);
    }
    *score1=score;
    saveHighScore(*score1);
    return GAME_OVER;
}