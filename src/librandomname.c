// vim:et:sta:sts=4:sw=4:ts=8:tw=79:

#include <stdlib.h>
#include "adjectives.h"
#include "animals.h"
#include "colors.h"
#include "notable_people.h"
#include "nouns.h"

// return random number between min and max (both inclusive)
static int random_number(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

char *randomname_adjective() {
    int len_adjectives = sizeof(adjectives) / sizeof(adjectives[0]);
    int rand = random_number(0, len_adjectives - 1);
    return adjectives[rand];
}

char *randomname_animal() {
    int len_animals = sizeof(animals) / sizeof(animals[0]);
    int rand = random_number(0, len_animals - 1);
    return animals[rand];
}

char *randomname_color() {
    int len_colors = sizeof(colors) / sizeof(colors[0]);
    int rand = random_number(0, len_colors - 1);
    return colors[rand];
}

char *randomname_notable_person() {
    int len_notable_people = sizeof(notable_people) / sizeof(notable_people[0]);
    int rand = random_number(0, len_notable_people - 1);
    return notable_people[rand];
}

char *randomname_noun() {
    int len_nouns = sizeof(nouns) / sizeof(nouns[0]);
    int rand = random_number(0, len_nouns - 1);
    return nouns[rand];
}
