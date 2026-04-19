#ifndef RENDER_H
#define RENDER_H

#include "snake.h"

void drawSnake(Node* snake);
void drawFood(int food_x,int food_y);
void drawScore(int score);
void drawObstacles();
#endif