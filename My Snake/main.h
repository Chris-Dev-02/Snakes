struct position{
    int x;
    int y;
};

enum direction {
    RIGHT,
    LEFT,
    UP,
    DOWN,
};

enum game_state{
    MAIN_MENU,
    GAME,
    GAME_OVER,
};

enum difficulty {
    EASY,
    MEDIUM,
    HARD,
};

void gotoxy(struct position pos);

void draw_frame();
void draw_main_menu();
void draw_game_over();
void draw_snake();
void draw_score();
void update_and_redraw_score();
void draw_apple();

void erase_snake();
void read_keyboard();
void move_snake();
void calculate_time();
void create_new_apple();

void check_collision_with_apple();
void check_collision_with_frame();
void check_collision_with_snake();

void change_game_state(enum game_state state);
void change_difficulty(enum difficulty dif);
void main_menu();
void game();
void game_over();

