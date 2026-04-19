#include <ncurses.h>
#include <stdlib.h>
#include "../include/snake.h"
#include "../include/obstacle.h"
Obstacle obstacles[MAX_OBS];
int obstacleCount = 0;
int isObstacle(int x,int y){
    for(int i=0;i<obstacleCount;i++){
        if(obstacles[i].x==x && obstacles[i].y==y) return 1;
    }
    return 0;
}
int collision(Node* snake){
    Node* curr=snake;
    while(curr)
    {
        if(isObstacle(curr->x,curr->y))
        {
            return 1;
        }
        curr=curr->next;
    }
    return 0;
}
void addOneObstacle(int w,int h, Node* snake) {
    if (obstacleCount >= MAX_OBS) return;

    int x,y;
    x = rand()%(w-2) + 1;
    y = rand()%(h-UI_HEIGHT-1) + UI_HEIGHT;
    while(isObstacle(x,y) || inSnake(x,y,snake)) {
        x = rand()%(w-2) + 1;
        y = rand()%(h-UI_HEIGHT-1) + UI_HEIGHT;
    }
    obstacles[obstacleCount].x =x;
    obstacles[obstacleCount].y =y;
    obstacleCount++;
}
void addVerticalWall(int w,int h){
    int x=rand()%(w-4)+2;
    for(int y= UI_HEIGHT+2;y<h-2;y++) {
        if(obstacleCount >=MAX_OBS) return;
        obstacles[obstacleCount++] = (Obstacle) {x,y,0,0,0};
    }
}
void addMovingObstacle(int w,int h,Node* snake){
    if(obstacleCount >= MAX_OBS) return;

    int x = rand()%(w-2) +1;
    int y = rand()%(h-UI_HEIGHT-1) + UI_HEIGHT;
    while(!isObstacle(x,y)) {
        x = rand()%(w-2) + 1;
        y = rand()%(h-UI_HEIGHT-1) + UI_HEIGHT;
        break;
    }
    int dx = (rand()%3) - 1;
    int dy = (rand()%3) - 1;
    if(dx == 0 && dy == 0) dx=1;

    obstacles[obstacleCount++] = (Obstacle) {x,y,dx,dy,1};
}