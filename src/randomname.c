// vim:et:sta:sts=4:sw=4:ts=8:tw=79:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "librandomname.h"

void usage() {
    fprintf(stdout, "HELP\n");
}

int main(int argc, char** argv) {

    // flagged (value = 0) if the respective part is enabled
    int left_flag = 0;
    int middle_flag = 1;
    int right_flag = 0;

    // 0 means that names could start with any letter
    char first_char_left = 0;
    char first_char_middle = 0;
    char first_char_right = 0;

    // flagged (value = 0) if the respective option is enabled
    int ubuntu_flag = 1;
    int docker_flag = 1;
    int no_dashes_flag = 1;

    randomname_category_t left_category = RANDOM_ADJECTIVE;
    randomname_category_t middle_category = RANDOM_NONE;
    randomname_category_t right_category = RANDOM_NOUN;

    char separator = '-';

    int next_opt;
    /* String of short options */
    const char *short_options = "hl:m:r:s:";
    /* The array of long options */
    const struct option long_options[] = {
        { "help",         no_argument,       NULL,           'h' },
        { "left",         required_argument, NULL,           'l' },
        { "middle",       required_argument, NULL,           'm' },
        { "right",        required_argument, NULL,           'r' },
        { "left-start",   required_argument, NULL,            0  },
        { "middle-start", required_argument, NULL,            0  },
        { "right-start",  required_argument, NULL,            0  },
        { "docker",       no_argument,       &docker_flag,    0  },
        { "ubuntu",       optional_argument, &ubuntu_flag,    0  },
        { "no-dashes",    no_argument,       &no_dashes_flag, 0  },
        { "separator",    required_argument, NULL,           's' },
        { NULL,           0,                 NULL,            0  } 
    };

    do {
        next_opt = getopt_long(argc, argv, short_options, long_options, NULL);
        switch (next_opt) {
            case 0: // A long-only option
                // these first ones are handled by their respective short
                // options and flags anyway
                if (strcmp(argv[optind-1], "--help") == 0);
                else if (strcmp(argv[optind-1], "--left") == 0);
                else if (strcmp(argv[optind-1], "--middle") == 0);
                else if (strcmp(argv[optind-1], "--right") == 0);
                else if (strcmp(argv[optind-1], "--docker") == 0);
                else if (strcmp(argv[optind-1], "--no-dashes") == 0);
                else if (strcmp(argv[optind-1], "--separator") == 0);
                // handle optional argument for --ubuntu option
                else if (strcmp(argv[optind-1], "--ubuntu") == 0) {
                    if (argv[optind]) {
                        if (argv[optind][0] == '-'); // next arg is an option
                        else if (strlen(argv[optind]) == 1 && argv[optind][0] >= 'a' && argv[optind][0] <= 'z') {
                            first_char_left = argv[optind][0];
                            first_char_right = argv[optind][0];
                        } else {
                            // invalid argument
                            fprintf(stderr, "ERROR: Invalid argument (%s)\n\n", argv[optind]);
                            usage();
                            exit(EXIT_FAILURE);
                        }
                        
                    }
                } else if (strcmp(argv[optind-2], "--left-start") == 0) {
                    if (strlen(optarg) == 1 && optarg[0] >= 'a' && optarg[0] <= 'z') {
                        first_char_left = optarg[0];
                    } else {
                        // invalid argument
                        fprintf(stderr, "ERROR: Invalid argument (%s)\n\n", optarg);
                        usage();
                        exit(EXIT_FAILURE);
                    }
                } else if (strcmp(argv[optind-2], "--middle-start") == 0) {
                    if (strlen(optarg) == 1 && optarg[0] >= 'a' && optarg[0] <= 'z') {
                        first_char_middle = optarg[0];
                    } else {
                        // invalid argument
                        fprintf(stderr, "ERROR: Invalid argument (%s)\n\n", optarg);
                        usage();
                        exit(EXIT_FAILURE);
                    }
                } else if (strcmp(argv[optind-2], "--right-start") == 0) {
                    if (strlen(optarg) == 1 && optarg[0] >= 'a' && optarg[0] <= 'z') {
                        first_char_right = optarg[0];
                    } else {
                        // invalid argument
                        fprintf(stderr, "ERROR: Invalid argument (%s)\n\n", optarg);
                        usage();
                        exit(EXIT_FAILURE);
                    }
                } else {
                    // no valid long-only options found
                    fprintf(stderr, "ERROR: Invalid option (%s)\n\n", argv[optind-1]);
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h': // User requested help
                usage();
                return 0;
            case 'l':
                if (strcmp(optarg, "none") == 0) left_category = RANDOM_NONE;
                else if (strcmp(optarg, "adjective") == 0) left_category = RANDOM_ADJECTIVE;
                else if (strcmp(optarg, "color") == 0) left_category = RANDOM_COLOR;
                else {
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;
            case 'm':
                if (strcmp(optarg, "none") == 0) middle_category = RANDOM_NONE;
                else if (strcmp(optarg, "adjective") == 0) middle_category = RANDOM_ADJECTIVE;
                else if (strcmp(optarg, "color") == 0) middle_category = RANDOM_COLOR;
                else {
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;
            case 'r':
                if (strcmp(optarg, "none") == 0) right_category = RANDOM_NONE;
                else if (strcmp(optarg, "animal") == 0) right_category = RANDOM_ANIMAL;
                else if (strcmp(optarg, "noun") == 0) right_category = RANDOM_NOUN;
                else if (strcmp(optarg, "person") == 0) right_category = RANDOM_NOTABLE_PERSON;
                else {
                    usage();
                    exit(EXIT_FAILURE);
                }
                break;
            case 's':
                /* The separator to use */
                separator = optarg[0];
                break;
            case '?':
                /* The user specified an invalid option */
                fprintf(stderr, "ERROR: Invalid option specified.\n\n");
                usage();
                exit(EXIT_FAILURE);
            case -1:
                /* Done with options */
                break;
            default:
                /* Unexpected... */
                fprintf(stderr, "ERROR: Something weird happened.\n\n");
                usage();
                exit(EXIT_FAILURE);
        }
    } while (next_opt != -1);

    randomname_init();

    if (docker_flag == 0) {
        fprintf(stdout, "%s\n", randomname_docker());
        return 0;
    }
    if (ubuntu_flag == 0) {
        fprintf(stdout, "%s\n", randomname_ubuntu(first_char_left));
        return 0;
    }

    char *name = randomname_opts(left_category, middle_category, right_category,
            first_char_left, first_char_middle, first_char_right,
            separator, !no_dashes_flag);
    fprintf(stdout, "%s\n", name);

    return 0;
}
