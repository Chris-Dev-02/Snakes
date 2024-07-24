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
void draw_snake();
void draw_score();
void update_and_redraw_score();
void draw_new_apple();

void erase_snake();
void read_keyboard();
void move_snake();
void calculate_time();

void check_collision_with_apple();
void check_collision_with_frame();
void check_collision_with_snake();
