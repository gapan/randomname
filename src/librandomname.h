// vim:et:sta:sts=4:sw=4:ts=8:tw=79:

enum random_left {
    LEFT_NONE = 0,
    LEFT_ADJECTIVE,
    LEFT_COLOR
};

enum random_middle {
    MIDDLE_NONE = 0,
    MIDDLE_ADJECTIVE,
    MIDDLE_COLOR 
};

enum random_right {
    RIGHT_NONE = 0,
    RIGHT_ANIMAL,
    RIGHT_NOUN,
    RIGHT_PERSON
};

enum random_preset {
    PRESET_NONE = 0,
    PRESET_DOCKER,
    PRESET_UBUNTU
};

// return random number between min and max (both inclusive)
int random_number(int min, int max);

char *randomname_adjective();
char *randomname_animal();
char *randomname_color();
char *randomname_notable_person();
char *randomname_noun();

