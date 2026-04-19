#ifndef GAME_H
#define GAME_H
#define SLOW 0
#define MEDIUM 1
#define FAST 2
#define HARDCORE 3
#include "snake.h"

extern int difficulty;
int runGame(int h, int w, int* score);
int runGameLoaded(int h, int w, Node* snake, int dx, int dy, int food_x, int food_y, int old_score, int* new_score);
int getlevel(int len);
#endif