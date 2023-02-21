// vim:et:sta:sts=4:sw=4:ts=8:tw=79:

#include <stdbool.h>

typedef enum {
    RANDOM_NONE = 0,
    RANDOM_ADJECTIVE,
    RANDOM_ADJECTIVE_DOCKER,
    RANDOM_ANIMAL,
    RANDOM_COLOR,
    RANDOM_ELEMENT,
    RANDOM_NOTABLE_PERSON,
    RANDOM_NOUN,
    RANDOM_NUMBER
} randomname_category_t;

/* Make sure you run randomname_init() before anything else! */
void randomname_init();

/* Returns a name in the form of adjective-noun. */
char *randomname();

/* Use this if you want to customize the random name more. */
char *randomname_opts(randomname_category_t left_category,
                      randomname_category_t middle_category,
                      randomname_category_t right_category,
                      char first_char_left,
                      char middle_start,
                      char right_start,
                      char separator,
                      bool no_dashes);

/* If the above are too restrictive for you, use the following to create names
 * with any number of parts you like. These return a random word from the
 * specified category.
 */
char *randomname_by_category(randomname_category_t c);
char *randomname_by_category_opts(randomname_category_t c, char first_char, bool no_dashes);

/* Just some more easy-to-use presets. */
char *randomname_docker();
char *randomname_heroku();
char *randomname_ubuntu(char first_char);

