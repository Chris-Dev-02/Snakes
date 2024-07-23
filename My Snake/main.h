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

void gotoxy(struct position pos);

void draw_frame();