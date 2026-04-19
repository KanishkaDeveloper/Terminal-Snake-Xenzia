#ifndef SAVE_H
#define SAVE_H

#include "snake.h"
#include "obstacle.h"

void saveGame(int slot,Node* snake, int dx, int dy, int food_x, int food_y, int score,int obstacleCount,Obstacle obstacles[]);
Node* loadGame(int slot,int *dx, int *dy, int *food_x, int *food_y, int *score,int *obstacleCount,Obstacle obstacles[MAX_OBS]);
void saveHighScore(int score);
int loadHighScore();
#endif