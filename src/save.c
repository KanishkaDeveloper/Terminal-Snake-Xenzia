#include <stdio.h>
#include "../include/save.h"
#include "../include/snake.h"
#include "../include/game.h"
#include "../include/obstacle.h"
void saveGame(int slot,Node* snake, int dx, int dy, int food_x, int food_y, int score,int obstacleCount,Obstacle obstacles[]){
    char filename[20];
    sprintf(filename,"save%d.csv",slot);

    FILE *f = fopen(filename,"w");
    if (!f) {
        perror("Save failed");
        return;
    }
    fprintf(f, "%d,%d,%d,%d\n",score,dx,dy,difficulty);
    fprintf(f,"%d,%d\n",food_x,food_y);

    Node* curr = snake;
    int count = 0;
    while(curr) {
        count++;
        curr=curr->next;
    }
    fprintf(f,"%d\n",count);
    curr=snake;
    while(curr) {
        fprintf(f,"%d,%d\n",curr->x,curr->y);
        curr=curr->next;
    }
    fprintf(f,"%d\n",obstacleCount);
    for(int i=0;i<obstacleCount;i++)
    {
        fprintf(f,"%d,%d,%d,%d,%d\n",obstacles[i].x,obstacles[i].y,obstacles[i].dx,obstacles[i].dy,obstacles[i].moving);
    }
    fclose(f);
}
Node* loadGame(int slot,int *dx, int *dy, int *food_x, int *food_y, int *score,int *obstacleCount,Obstacle obstacles[MAX_OBS]){
    char filename[20];
    sprintf(filename,"save%d.csv",slot);

    FILE* f=fopen(filename,"r");
    if (!f){
        perror("Load failed");
        return NULL;
    }
    int s,x,y,d;
    if (fscanf(f,"%d,%d,%d,%d",&s,&x,&y,&d) != 4) {
        fclose(f);
        return NULL;
    }
    *score=s; 
    *dx=x; 
    *dy=y;
    difficulty = d;
    int fx,fy;
    if (fscanf(f,"%d,%d",&fx,&fy) !=2) {
        fclose(f);
        return NULL;
    }
    *food_x=fx;
    *food_y=fy;
    int n;
    if (fscanf(f,"%d",&n) != 1 || n<=0) {
        fclose(f);
        return NULL;
    }

    Node* snake = NULL;

    for(int i=0;i<n;i++){
        int x,y;
        if (fscanf(f," %d , %d",&x,&y) !=2) {
            printf("FAILED at node %d\n",i);
            fclose(f);
            return NULL;
        }
        //printf("Adding node: %d %d\n",x,y);
        addBack(&snake,x,y);
    }
    /*Node* temp=snake;
    int cnt=0;
    while(temp){
        printf("Node %d: %d %d\n",cnt,temp->x,temp->y);
        temp=temp->next;
        cnt++;
        if(cnt>1000){
            printf("Loop detected or corruption\n");
            break;
        }
    }*/
    int cnt;
    fscanf(f,"%d",&cnt);
    *obstacleCount=cnt;
    for(int i=0;i<cnt;i++){
        int x,y,dx,dy,moving;
        fscanf(f,"%d,%d,%d,%d,%d",&x,&y,&dx,&dy,&moving);
        Obstacle item;
        item.x=x;
        item.y=y;
        item.dx=dx;
        item.dy=dy;
        item.moving=moving;
        obstacles[i]=item;
    }
    fclose(f);
    return snake;
}
void saveHighScore(int score){
    FILE* f=fopen("highscore.txt","r");
    int high = 0;
    if(f){
        fscanf(f,"%d",&high);
        fclose(f);
    }

    if(score>high){
        f=fopen("highscore.txt","w");
        if(f){
            fprintf(f,"%d",score);
            fclose(f);
        }
    }
}
int loadHighScore(){
    FILE* f=fopen("highscore.txt","r");
    int high = 0;

    if(f){
        fscanf(f,"%d",&high);
        fclose(f);
    }
    return high;
}