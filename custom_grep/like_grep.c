#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <colors.h>
#include "kmp.h"

// length of the array to store the number of occurrences of the substring in the string
#define ELEMENTS_COUNT 8
#define COLOR GREEN


void *open_file(char *);

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Missing required arguments.\n%s <filename> <pattern>\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];
    char *pattern = argv[2];

    char buff[100];
    
    void *file = open_file(filename);

    while (fgets(buff, 100, file) != NULL) {
        char *res_arr[ELEMENTS_COUNT];
        int found_count = kmp_search(buff, pattern, res_arr, ELEMENTS_COUNT);

        int idx = 0;
        while (buff[idx]) {
            int highlighted = 0;
            for (int i = 0; i < found_count; i++) {
                if (&buff[idx] >= res_arr[i] && &buff[idx] < res_arr[i] + strlen(pattern)) {
                    printf(COLOR "%c" RESET, buff[idx]);
                    highlighted = 1;
                    break;
                }
            }
            if (!highlighted) {
                putchar(buff[idx]);
            }
            idx++;
    }

    }

    return 0;
}

void *open_file(char *filename) {
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filename);
        return NULL;
    } else 
        return fptr;
}