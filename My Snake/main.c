#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include "main.h"

//╚╝╔╗╣╠║═
struct position snake[101];
struct position snake_init_pos = {40, 10};
struct position upper_limit = {0, 0};
struct position lower_limit = {80, 20};
struct position apple = {10, 10};
enum direction direction = LEFT; 
int prev_snake_lenght = 1;
int snake_lenght = 1;
bool game_over = false;
int score = 0;

void gotoxy(struct position pos)
{
    printf( "\033[%d;%df", pos.y, pos.x);

}

void draw_frame(){
    for(int i = upper_limit.x; i < lower_limit.x; i++){
        struct position pos_1 = {i, upper_limit.y};
        gotoxy(pos_1);
        printf("%c", 205);
        struct position pos_2 = {i, lower_limit.y};
        gotoxy(pos_2);
        printf("%c", 205);
    }
        for(int i = upper_limit.y; i < lower_limit.y; i++){
        struct position pos_1 = {upper_limit.x, i};
        gotoxy(pos_1);
        printf("%c", 186);
        struct position pos_2 = {lower_limit.x, i};
        gotoxy(pos_2);
        printf("%c", 186);
    }

    struct position pos_1 = {upper_limit.x, lower_limit.y};
    gotoxy(pos_1);
    printf("%c", 200);
    struct position pos_2 = {lower_limit.x, upper_limit.y};
    gotoxy(pos_2);
    printf("%c", 187);
    gotoxy(upper_limit);
    printf("%c", 201);
    gotoxy(lower_limit);
    printf("%c", 188);
}

void draw_snake(){
    for(int i = 0; i < snake_lenght; i++){
        gotoxy(snake[i]);
        if(i == 0){
            printf("@");
        }
        else{
            printf("*");
        }
    }
}

void erase_snake(){
    for(int i = 0; i < snake_lenght; i++){
        gotoxy(snake[0]);
        printf(" ");
    }
}

void read_keyboard(){
    if (_kbhit()) {
        switch (_getch()){
            case 'w': direction = UP; break;
            case 'a': direction = LEFT; break;
            case 's': direction = DOWN; break;
            case 'd': direction = RIGHT; break;
        }  
    }  
}

void move_snake(){
    switch (direction)
    {
    case RIGHT:
        snake[0].x++;
        break;
    case UP: 
        snake[0].y--;
        break;
    case LEFT:
        snake[0].x--;
        break;
    case DOWN:
        snake[0].y++;
        break;
    default:
        break;
    }

    for(int i = 0; i < snake_lenght; i++){

    }
}


int main()
{
    snake[0] = snake_init_pos;
    draw_frame();
    while(1){
        erase_snake();
        read_keyboard();
        move_snake();
        draw_snake();
        Sleep(100);
    }

    return 0;
}


