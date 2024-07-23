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
int sleep_time = 100;
float seconds = 0.0;
int snake_lenght = 1;
bool game_over = false;
int score = 0;

void gotoxy(struct position pos)
{
    printf( "\033[%d;%df", pos.y, pos.x);

}

// Drawings functions
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
            game_over ? printf("X") : printf("@");
        }
        else{
            game_over ? printf("+") : printf("*");
        }
    }
}

void draw_score(){
    struct position score_pos = {0, lower_limit.y + 1};
    gotoxy(score_pos);
    printf("SCORE: ");
    struct position time_position = {0, lower_limit.y + 2};
    gotoxy(time_position);
    printf("TIME: ");
}

void update_and_redraw_score(){
    struct position score_pos = {8, lower_limit.y + 1};
    gotoxy(score_pos);
    printf("%i", score);
    struct position time_position = {8, lower_limit.y + 2};
    gotoxy(time_position);
    printf("%.f", seconds);
}

// General
void draw_new_apple(){
    apple.x = rand() % (lower_limit.x - upper_limit.x + 1) + upper_limit.x;
    apple.y = rand() % (lower_limit.y - upper_limit.y + 1) + upper_limit.y;

    if(apple.x == 0 || apple.y == 0 || apple.x == lower_limit.x || apple.y == lower_limit.y){
        return draw_new_apple();
    }

    gotoxy(apple);
    printf("%c", 224);
}

void erase_snake(){
    /*
        for(int i = 0; i < snake_lenght; i++){
        gotoxy(snake[i]);
        printf(" ");
    }*/
    
    gotoxy(snake[snake_lenght - 1]);
    printf(" ");
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
    if(!game_over){
        struct position aux_1, aux_2;
        for(int i = snake_lenght - 1; i > 0; i--){
            snake[i] = snake[i - 1];
        }
            
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
    }
}

void calculate_time(){
    seconds = seconds + (sleep_time / 1000.0);
}

// Collision functions
void check_collision_with_apple(){
    if(snake[0].x == apple.x && snake[0].y == apple.y){
        snake[snake_lenght + 1] = snake[snake_lenght];
        draw_new_apple();
        score += 1;
        snake_lenght++;
    }
}

void check_collision_with_frame(){
    if(snake[0].x == upper_limit.x || snake[0].x == lower_limit.x){
        game_over = true;
    }
    if(snake[0].y == upper_limit.y || snake[0].y == lower_limit.y){
        game_over = true;
    }
}

void check_collision_with_snake(){
    for (int i = 1; i < snake_lenght; i++) {
        if (snake[i].x == snake[0].x && snake[i].y == snake[0].y)
            game_over = true;
    }
}

int main()
{
    snake[0] = snake_init_pos;
    draw_frame();
    draw_score();
    draw_new_apple();
    while(!game_over){
        erase_snake();
        read_keyboard();
        check_collision_with_frame();
        check_collision_with_snake();
        check_collision_with_apple();
        move_snake();
        draw_snake();
        update_and_redraw_score();
        Sleep(sleep_time);
        calculate_time();
    }

    return 0;
}


