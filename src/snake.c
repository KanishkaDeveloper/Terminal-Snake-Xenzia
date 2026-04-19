#include "../include/snake.h"
#include "../include/obstacle.h"
#include <stdlib.h>
void addHead(Node** head,int x,int y){
    Node* new=(Node*)malloc(sizeof(Node));
    new->x=x;
    new->y=y;
    new->prev=NULL;
    new->next=NULL;
    Node* curr=*head;
    if(curr==NULL)
        *head=new;
    else
    {
        new->next=curr;
        curr->prev=new;
        *head=new;
    }
}
void removeBack(Node** head){
    if (*head == NULL) return;
    Node* curr=*head;

    if (curr->next == NULL) {
        free(curr);
        *head = NULL;
        return;
    }
    while(curr->next)
    {
        curr=curr->next;
    }

    (curr->prev)->next=NULL;
    free(curr);
}
void addBack(Node** head, int x, int y){
    Node* new=(Node*)malloc(sizeof(Node));
    new->x=x;
    new->y=y;
    new->prev=NULL;
    new->next=NULL;
    
    if(*head==NULL) {
        *head=new;
        return;
    }

    Node* curr=*head;
    while(curr->next){
        curr=curr->next;
    }
    curr->next=new;
    new->prev=curr;
}
int inSnake(int x,int y, Node*head){
    Node* curr=head;
    while(curr)
    {
        if(curr->x==x && curr->y==y)
        {
            return 1;
        }
        curr=curr->next;
    }
    return 0;
}
int checkCollision(int x, int y, Node* head){
    return inSnake(x,y,head->next);
}
int snakeLength(Node* snake){
    int len = 0;
    while(snake){
        len++;
        snake=snake->next;
    }
    return len;
}
int checkObstacleCollision(int x,int y){
    for(int i=0;i<obstacleCount;i++){
        if(x == obstacles[i].x && y == obstacles[i].y)
            return 1;
    }
    return 0;
}

