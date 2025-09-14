#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <unistd.h>
#include "colors.h"

void result(int *, int *, int *, char []);
void set_opt(int, char *[], int *, int *, int *, char []);
void p_status(int *, int *, int *, int *, int *, int *, char []);


int main(int argc, char *argv[])
{
    int ch;
    int lines = 0;
    int words = 0;
    int bytes = 0;
    int inside_word = 0;

    int print_l = 0;
    int print_w = 0;
    int print_b = 0;

    set_opt(argc, argv, &print_l, &print_w, &print_b, argv[0]);

    if (optind >= argc) {
        fprintf(stderr, "%sFile don\'t selected.%s\n", RED, RESET);
        fprintf(stderr, "Usage: %s%s [-lwb] <filename>%s\n", YELLOW, argv[0], RESET);
        return -1;
    }

    FILE *txt_file = fopen(argv[optind], "r");
    if (txt_file == NULL) {
        perror("Error opening file");
        return -1;
    }

    while ((ch = fgetc(txt_file)) != EOF) {
        bytes++;
        if (ch == '\n') {
            lines++;
        }
        if (!isspace(ch) && !inside_word) {
            inside_word = 1;
            words++;
        }
        if (isspace(ch) && inside_word) {
            inside_word = 0;
        }
    }

    fclose(txt_file);
    p_status(&print_l, &print_w, &print_b, &lines, &words, &bytes, argv[optind]);

    return 0;
}

void result(int * l, int * w, int * b, char f_name[]) {
    printf("%slines%s = %d, %swords%s = %d, %sbytes%s = %d\t%s\n",
        YELLOW, RESET, *l, BLUE, RESET, *w, PURPLE, RESET, *b, f_name);
}

void set_opt(int arg_c, char *arg_v[], int *pr_l, int *pr_w, int *pr_b, char f_name[]) {
    int opt;
    while ((opt = getopt(arg_c, arg_v, "lwbh")) != -1) {
        switch (opt) {
            case 'l':
                *pr_l = 1;
                break;
            case 'w':
                *pr_w = 1;
                break;
            case 'b':
                *pr_b = 1;
                break;
            case 'h':
                printf("Usage: %s [-lwb] <filename>\n", f_name);
                printf("Options:\n");
                printf("\t-l\tPrint line count\n");
                printf("\t-w\tPrint word count\n");
                printf("\t-b\tPrint byte count\n");
                printf("\t-h\tShow help message\n");
                exit(0);
            case '?':
                fprintf(stderr, "Try \'%s -h\' for more info.\n", f_name);
                exit(1);
            default:
                fprintf(stderr, "Unknown option: %c\n", optopt);
                exit(1);
        }
    }
}

void p_status(int *pr_l, int *pr_w, int *pr_b, int *l, int *w, int *b, char f_name[]) {
    if (!(*pr_l) && !(*pr_w) && !(*pr_b)) {
        result(l, w, b, f_name);
    } else {
        int first = 1;
        if (*pr_l) {
            printf("%s%d%s", YELLOW, *l, RESET);
            first = 0;
        }
        if (*pr_w) {
            if (!first) printf(" ");
            printf("%s%d%s", BLUE, *w, RESET);
            first = 0;
        }
        if (*pr_b) {
            if (!first) printf(" ");
            printf("%s%d%s", PURPLE, *b, RESET);
        }
        printf(" %s\n", f_name);
    }
}