#include <stdio.h>
#include <ncurses.h>
#include "../include/snake.h"
#include "../include/game.h"
#include "../include/obstacle.h"
void drawSnake(Node* snake){
    Node* curr=snake;
    while(curr){
        if(curr==snake){
            attron(COLOR_PAIR(1));
            mvaddch(curr->y,curr->x,'@');
            attroff(COLOR_PAIR(1));
        }   
        else{
            attron(COLOR_PAIR(1));
            mvaddch(curr->y,curr->x,'o');
            attroff(COLOR_PAIR(1));
        }       
        curr=curr->next;
    }
}
void drawFood(int food_x,int food_y){
    attron(COLOR_PAIR(2));
    mvaddch(food_y,food_x,'0');
    attroff(COLOR_PAIR(2));
}
void drawScore(int score){
    attron(COLOR_PAIR(3));
    char *diffStr[] = {"Slow", "Medium", "Fast","Hardcore"};
    mvprintw(1,2,"Score: %d",score*100);
    mvprintw(2,2,"Difficulty: %s", diffStr[difficulty]);
    attroff(COLOR_PAIR(3));
}
void drawObstacles(){
    if (obstacles==NULL | obstacleCount<=0) return;
    for(int i=0;i<obstacleCount;i++){
        if(obstacles[i].moving){
            attron(COLOR_PAIR(5));
            mvaddch(obstacles[i].y,obstacles[i].x,'X');
            attroff(COLOR_PAIR(5));
        }
        else
        {
        attron(COLOR_PAIR(4));
        mvaddch(obstacles[i].y, obstacles[i].x, '#');
        attroff(COLOR_PAIR(4));
        }
    }
}
