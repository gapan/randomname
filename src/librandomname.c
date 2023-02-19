// vim:et:sta:sts=4:sw=4:ts=8:tw=79:

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "librandomname.h"
#include "adjectives.h"
#include "adjectives_docker.h"
#include "animals.h"
#include "colors.h"
#include "elements.h"
#include "notable_people.h"
#include "nouns.h"

static bool randomname_initialized = false;

// return random number between min and max (both inclusive)
static int random_number(int min, int max) {
    if (!randomname_initialized) return - 1;
    return rand() % (max + 1 - min) + min;
}

static bool includes_dash(char *s) {
    bool found_dash = false;
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if (s[i] == '-') {
            found_dash = true;
            break;
        }
    }
    return found_dash;
}

static char *random_item(char **list, int len) {
    return random_item_opts(list, len, 0, false);
}

static char *random_item_opts(char **list, int len, char first_char, bool no_dashes) {
    int start = 0;
    int end = len - 1;
    bool found_start = false;
    if (first_char && first_char >= 'a' && first_char <= 'z') {
        for (int i = 0; i < len; ++i) {
            if (!found_start && list[i][0] == first_char) {
                start = i;
                found_start = true;
            }
            if (found_start && list[i][0] != first_char) {
                end = i - 1;
                break;
            }
        }
    }
    int rand;
    do {
        rand = random_number(start, end);
    } while (no_dashes && no_dashes == true && includes_dash(list[rand]));
    return list[rand];
}

void randomname_init() {
    if (!randomname_initialized) {
        randomname_initialized = true;
        srand(time(NULL) * getpid()); // random seed. Should be random enough
    }
}

char *randomname() {
    return randomname_opts(RANDOM_ADJECTIVE, RANDOM_NONE, RANDOM_NOUN, 0, 0, 0, '-', false);
}

char *randomname_opts(randomname_category_t left_category,
                      randomname_category_t middle_category,
                      randomname_category_t right_category,
                      char first_char_left,
                      char first_char_middle,
                      char first_char_right,
                      char separator,
                      bool no_dashes) {
    char *left = randomname_by_category_opts(left_category, first_char_left, no_dashes);
    char *middle = randomname_by_category_opts(middle_category, first_char_middle, no_dashes);
    char *right = randomname_by_category_opts(right_category, first_char_right, no_dashes);
    char *name;
    if (left && middle && right) {
        name = malloc(strlen(left) + strlen(middle) + strlen(right) + 3);
        sprintf(name, "%s%c%s%c%s", left, separator, middle, separator, right);
    } else if (left && right) {
        name = malloc(strlen(left) + strlen(right) + 2);
        sprintf(name, "%s%c%s", left, separator, right);
    } else if (middle && right) {
        name = malloc(strlen(middle) + strlen(right) + 2);
        sprintf(name, "%s%c%s", middle, separator, right);
    } else if (left && middle) {
        name = malloc(strlen(left) + strlen(middle) + 2);
        sprintf(name, "%s%c%s", left, separator, middle);
    } else if (left) {
        return left;
    } else if (middle) {
        return middle;
    } else if (right) {
        return right;
    }
    return name;
}

char *randomname_by_category(randomname_category_t c) {
    return randomname_by_category_opts(c, 0, false);
}

char *randomname_by_category_opts(randomname_category_t c, char first_char, bool no_dashes) {
    int len;
    if (c == RANDOM_ADJECTIVE) {
        len = sizeof(adjectives) / sizeof(adjectives[0]);
        return random_item_opts(adjectives, len, first_char, no_dashes);
    } else if (c == RANDOM_ADJECTIVE_DOCKER) {
        len = sizeof(adjectives_docker) / sizeof(adjectives_docker[0]);
        return random_item_opts(adjectives_docker, len, first_char, no_dashes);
    } else if (c == RANDOM_ANIMAL) {
        len = sizeof(animals) / sizeof(animals[0]);
        return random_item_opts(animals, len, first_char, no_dashes);
    } else if (c == RANDOM_COLOR) {
        len = sizeof(colors) / sizeof(colors[0]);
        return random_item_opts(colors, len, first_char, no_dashes);
    } else if (c == RANDOM_ELEMENT) {
        len = sizeof(elements) / sizeof(elements[0]);
        return random_item_opts(elements, len, first_char, no_dashes);
    } else if (c == RANDOM_NOTABLE_PERSON) {
        len = sizeof(notable_people) / sizeof(notable_people[0]);
        return random_item_opts(notable_people, len, first_char, no_dashes);
    } else if (c == RANDOM_NOUN) {
        len = sizeof(nouns) / sizeof(nouns[0]);
        return random_item_opts(nouns, len, first_char, no_dashes);
    } else if (c == RANDOM_NUMBER) {
        printf("%");
        int r = random_number(1000, 9999);
        printf("%");
        char *s = malloc(5);
        printf("%");
        sprintf(s, "%d", r);
        printf("%");
        return s;
    }
    return NULL;
}

char *randomname_docker() {
    char *name;
    /* Steve Wozniak is not boring
     * just mirroring what docker does. See:
     * https://github.com/moby/moby/blob/master/pkg/namesgenerator/names-generator.go
     */
    do {
        char *left = randomname_by_category_opts(RANDOM_ADJECTIVE_DOCKER, 0, true);
        char *right = randomname_by_category_opts(RANDOM_NOTABLE_PERSON, 0, true);
        name = malloc(strlen(left) + strlen(right) + 2);
        sprintf(name, "%s_%s", left, right);
    } while (strcmp(name, "boring_wozniak") == 0);
    return name;
}

char *randomname_ubuntu(char first_char) {
    if (first_char < 'a' || first_char > 'z') {
        first_char = random_number('a', 'z');
    }
    char *left = randomname_by_category_opts(RANDOM_ADJECTIVE, first_char, true);
    char *right = randomname_by_category_opts(RANDOM_ANIMAL, first_char, true);
    char *name = malloc(strlen(left) + strlen(right) + 2);
    sprintf(name, "%s-%s", left, right);
    return name;
}

