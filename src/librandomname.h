// vim:et:sta:sts=4:sw=4:ts=8:tw=79:

#include <stdbool.h>

typedef enum {
    RANDOM_NONE = 0,
    RANDOM_ADJECTIVE,
    RANDOM_ANIMAL,
    RANDOM_COLOR,
    RANDOM_NOTABLE_PERSON,
    RANDOM_NOUN
} randomname_category_t;

char *randomname();
char *randomname_opts(randomname_category_t left_category,
                      randomname_category_t middle_category,
                      randomname_category_t right_category,
                      char first_char_left,
                      char middle_start,
                      char right_start,
                      char separator,
                      bool no_dashes);

char *randomname_by_category(randomname_category_t c);
char *randomname_by_category_opts(randomname_category_t c, char first_char, bool no_dashes);

char *randomname_docker();
char *randomname_ubuntu(char first_char);
