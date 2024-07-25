#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include "main.h"

struct position snake[101];
struct position snake_init_pos = {40, 10};
struct position upper_limit = {0, 0};
struct position lower_limit = {80, 20};
struct position apple = {10, 10};

enum direction direction = LEFT; 

int sleep_time = 80;
float seconds = 0.0;
int snake_lenght = 1;

bool is_game_over = false;  //LEGACY
enum game_state var_game_state = MAIN_MENU;
enum difficulty var_difficulty = EASY;
bool is_program_running = true;
bool first_frame = true;
bool redraw_frame = false;
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

void draw_main_menu(){
    struct position pos_1 = {(lower_limit.x / 2) - 5, (lower_limit.y / 2)};
    gotoxy(pos_1);
    printf("S N A K E");
    struct position pos_2 = {(lower_limit.x / 2) - 15, (lower_limit.y / 2) + 2};
    gotoxy(pos_2);
    printf("Press \"1\" to play in easy mode");
    struct position pos_3 = {(lower_limit.x / 2) - 16, (lower_limit.y / 2) + 3};
    gotoxy(pos_3);
    printf("Press \"2\" to play in medium mode");
    struct position pos_4 = {(lower_limit.x / 2) - 15, (lower_limit.y / 2) + 4};
    gotoxy(pos_4);
    printf("Press \"3\" to play in hard mode");
}

void draw_game_over(){
    struct position pos_1 = {(lower_limit.x) / 2 - 8, (lower_limit.y) / 2};
    gotoxy(pos_1);
    printf("G A M E   O V E R");
    struct position pos_2 = {(lower_limit.x / 2) - 12, (lower_limit.y / 2) + 2};
    gotoxy(pos_2);
    printf("Press \"space\" to restart");
}

void draw_snake(){
    for(int i = 0; i < snake_lenght; i++){
        gotoxy(snake[i]);
        if(i == 0){
            //is_game_over ? printf("X") : printf("@");
            var_game_state == GAME_OVER ? printf("X") : printf("@");
        }
        else{
            //is_game_over ? printf("+") : printf("*");
            var_game_state == GAME_OVER ? printf("+") : printf("*");
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

void draw_apple(){
    gotoxy(apple);
    printf("%c", 224);
}

// General
void erase_snake(){
    
    /*for(int i = 0; i < snake_lenght - 1; i++){
        gotoxy(snake[i]);
        printf(" ");
    }*/
    
    gotoxy(snake[snake_lenght - 1]);
    printf(" ");
}

void read_keyboard(){
    if (_kbhit()) {
        switch (_getch()){
            // Gameplay
            case 'w': direction = UP; break;
            case 'a': direction = LEFT; break;
            case 's': direction = DOWN; break;
            case 'd': direction = RIGHT; break;
            // Flow control
            case 32: 
                switch (var_game_state)
                {
                    case MAIN_MENU: change_game_state(GAME); break;
                    case GAME_OVER: change_game_state(MAIN_MENU); break;
                }
                change_difficulty(MEDIUM);
                break; // SPACE detection
            case 49: 
                switch (var_game_state)
                {
                    case MAIN_MENU: change_game_state(GAME); break;
                    case GAME_OVER: change_game_state(MAIN_MENU); break;
                }
                change_difficulty(EASY);
                break;
            case 50: 
                switch (var_game_state)
                {
                    case MAIN_MENU: change_game_state(GAME); break;
                    case GAME_OVER: change_game_state(MAIN_MENU); break;
                }
                change_difficulty(MEDIUM);
                break;
            case 51: 
                switch (var_game_state)
                {
                    case MAIN_MENU: change_game_state(GAME); break;
                    case GAME_OVER: change_game_state(MAIN_MENU); break;
                }
                change_difficulty(HARD);
                break;
            case 27: is_program_running = false; break; // ESC detection
        }  
    }  
}

void move_snake(){
    if(var_game_state == GAME){
    //if(!is_game_over){
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

void create_new_apple(){
    int N = lower_limit.x - 1;
    int M = upper_limit.x + 1;
    apple.x = rand() % (N - M + 1) + M;
    N = lower_limit.y - 1;
    M = upper_limit.y + 1;
    apple.y = rand() % (N - M + 1) + M;

    if(apple.x == upper_limit.x || apple.y == upper_limit.y || apple.x == lower_limit.x || apple.y == lower_limit.y){
        return create_new_apple();
    }
}

// Collision functions
void check_collision_with_apple(){
    if(snake[0].x == apple.x && snake[0].y == apple.y){
        snake[snake_lenght + 1] = snake[snake_lenght];
        create_new_apple();
        score += 1;
        snake_lenght++;
    }
}

void check_collision_with_frame(){

    if(var_difficulty == EASY){
        if (snake[0].x >= lower_limit.x){
            snake[0].x = upper_limit.x + 2;
            redraw_frame = true;
        }  
        else if(snake[0].x <= upper_limit.x + 1){
            snake[0].x = lower_limit.x - 1;
            redraw_frame = true;
        }
        if (snake[0].y >= lower_limit.y){
            snake[0].y = upper_limit.y + 2;
            redraw_frame = true;
        }
        else if (snake[0].y <= upper_limit.y + 1) {
            snake[0].y = lower_limit.y - 1;
            redraw_frame = true;
        }
    }
    else{
        if(snake[0].x == upper_limit.x + 1 || snake[0].x == lower_limit.x){
            //is_game_over = true;
            change_game_state(GAME_OVER);
        }
        if(snake[0].y == upper_limit.y + 1 || snake[0].y == lower_limit.y){
            //is_game_over = true;
            change_game_state(GAME_OVER);
        }
    }
}

void check_collision_with_snake(){
    for (int i = 1; i < snake_lenght; i++) {
        if (snake[i].x == snake[0].x && snake[i].y == snake[0].y)
            //is_game_over = true;
            //first_frame = true;
            //var_game_state = 2;
            change_game_state(GAME_OVER);
    }
}

// Game state handle functions
void change_game_state(enum game_state state){
    first_frame = true;
    var_game_state = state;
}

void change_difficulty(enum difficulty dif){
    var_difficulty = dif;
    switch (var_difficulty)
    {
    case EASY:
        sleep_time = 130;
        break;
    case MEDIUM:
        sleep_time = 100;
        break;
    case HARD:
        sleep_time = 70;
        break;
    }
}

void main_menu(){
    if(first_frame){
        system("cls");
        draw_frame();
        draw_main_menu();
        first_frame = false;
    }

    read_keyboard();
    Sleep(sleep_time);
}

void game(){
    
    if(first_frame){
        system("cls");
        snake[0] = snake_init_pos;
        snake_lenght = 1;
        seconds = 0.0;
        score = 0;
        draw_frame();
        draw_score();
        create_new_apple();
        first_frame = false;
    }

    if(redraw_frame){
        draw_frame();
        redraw_frame = false;
    }
    erase_snake();
    read_keyboard();
    check_collision_with_frame();
    check_collision_with_snake();
    check_collision_with_apple();
    move_snake();
    draw_snake();
    draw_apple();
    update_and_redraw_score();
    Sleep(sleep_time);
    calculate_time();
}

void game_over(){
    if(first_frame){
        //system("cls");
        //draw_frame();
        draw_game_over();
        first_frame = false;
    }

    read_keyboard();
    Sleep(sleep_time);
}


int main(){
    while(is_program_running){
        switch (var_game_state)
        {
        case MAIN_MENU:
            main_menu();
            break;
        case GAME:
            game();
            break;
        case GAME_OVER:
            game_over();
            break;
        }
    }

    return 0;
}

/*
int main()
{
    snake[0] = snake_init_pos;
    draw_frame();
    draw_score();
    create_new_apple();
    while(!is_game_over){
        erase_snake();
        read_keyboard();
        check_collision_with_frame();
        check_collision_with_snake();
        check_collision_with_apple();
        move_snake();
        draw_snake();
        draw_apple();
        update_and_redraw_score();
        Sleep(sleep_time);
        calculate_time();
    }

    return 0;
}*/



