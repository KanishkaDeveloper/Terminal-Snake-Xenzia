#ifndef SNAKE_H
#define SNAKE_H

typedef struct Node {
    int x,y;
    struct Node* prev;
    struct Node* next;
} Node;
void addHead(Node** head,int x,int y);
void removeBack(Node** head);
void addBack(Node** head, int x, int y);
int inSnake(int x,int y, Node*head);
int checkCollision(int x, int y, Node* head);
int snakeLength(Node* snake);
#endif