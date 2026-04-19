#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "snake.h"
typedef struct Obstacle{
    int x,y;
    int dx,dy;
    int moving;
} Obstacle;
#define UI_HEIGHT 3
#define MAX_OBS 50
extern Obstacle obstacles[MAX_OBS];
extern int obstacleCount;
void addOneObstacle(int w,int h, Node* snake);
int isObstacle(int x,int y);
void addVerticalWall(int w,int h);
void addMovingObstacle(int w,int h,Node* snake);
int collision(Node* snake);
#endif