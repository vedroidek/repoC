#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include "colors.h"
#define BUFFSIZE 256
#define LAST_N_LINES 10

/**
 * Your version 'tail'.
 */

volatile sig_atomic_t keep_runing = 1;
void handle_sig(int);

long file_size(FILE *);
void inf_out(FILE *);
FILE * open_file(const char *, const char *);
void con_out(FILE *);
void print_help();
void output_last_n_lines(FILE *, int);


int main(int argc, char * argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "You did not indicate arguments.\nSee \'%s -h\'.\n",
            argv[0]);
        exit(1);
    }

    const char VERSION[5] = "v0.1";
    FILE * fp;
    int opt;
    char * filename = NULL;

    while ((opt = getopt(argc, argv, "o:s:f:n:hv")) != -1) {
        switch (opt) {
            case 'o':
                filename = optarg; // Save argument's value
                fp = open_file(filename, "rb");
                puts("Press \'ctrl + c\' for exit.");
                con_out(fp);
                break;
            case 's':
                filename = optarg;
                fp = open_file(filename, "rb");
                printf("%ld", file_size(fp));
                break;
            case 'n':
                filename = optarg;
                fp = open_file(filename, "rb");
                output_last_n_lines(fp, LAST_N_LINES);  // output last 10 lines
                con_out(fp);
                break;
            case 'h':
                print_help();
            case 'v':
                puts(VERSION);
                exit(EXIT_SUCCESS);
            case '?':
                fprintf(stderr, "Error: unknown option \'-%s\'.\n", optarg);
                exit(EXIT_FAILURE);
            default:
                print_help();
        }
    }

    putchar('\n');
    fclose(fp);

    return 0;
}

FILE * open_file(const char * filename, const char * mode) {
    FILE * fp;
    fp = fopen(filename, mode);
    if (!fp) {
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

long file_size(FILE * fptr) {
    long end_pos;
    if (fseek(fptr, 0, SEEK_END) != -1) {
        end_pos = ftell(fptr);
    }

    return end_pos;
}

void con_out(FILE * fptr) {
    // Constant out
    long pos; // position
    long new_pos; // new position
    char buffer[BUFFSIZE];
    size_t bytes_read;

    signal(SIGINT, handle_sig);

    if (fseek(fptr, 0L, SEEK_END) != 0) {
        perror("Failed to move.");
        exit(EXIT_FAILURE);
    }
    pos = ftell(fptr);

    while (keep_runing) {
        if (fseek(fptr, 0L, SEEK_END) != 0){
        perror("Failed to move.");
        exit(EXIT_FAILURE);
    }

        new_pos = ftell(fptr);

        if (new_pos < pos) {
            perror("File was truncated. Resetting...\n");
            fseek(fptr, 0, SEEK_SET);
            new_pos = 0L;
        }

        if (new_pos > pos) {
            fseek(fptr, pos, SEEK_SET);
            size_t bytes_to_read = new_pos - pos;

            while (bytes_to_read > 0) {
                size_t chunk_size = (bytes_to_read < BUFFSIZE) ? bytes_to_read : BUFFSIZE;
                bytes_read = fread(buffer, 1, chunk_size, fptr);

                if (bytes_read > 0) {
                    fwrite(buffer, 1, bytes_read, stdout);
                    fflush(stdout);

                    bytes_to_read -= bytes_read;
                } else {
                    perror("Error reading file.\n");
                    break;
                }
            }

            pos = new_pos;
        }

        sleep(1);
    }
    puts(RED "\nExit." RESET);
}

void print_help() {
    printf("Help.\n\v");
    puts("-v      show current version;");
    puts("-s      size of file (byte);\n\t\tfile -s <filename>\n");
    puts("-o      constant output of new lines;\n\t\tfile -o <filename>\n");
    exit(EXIT_SUCCESS);
}

void handle_sig(int signal) {
    keep_runing = 0;
}

void output_last_n_lines(FILE * fptr, int n) {
    int counter;
    int new_line;
    long shift_back = 0L;
    int ch;

    for (counter = 0 ; counter <= n; shift_back--) {
        if (fseek(fptr, shift_back, SEEK_END) != 0) {
            perror("Failed to move.");
            exit(EXIT_FAILURE);
        }

        if ((new_line = getc(fptr)) == '\n')
            counter++;
    }

    while ((ch = getc(fptr)) != EOF) {
        putchar(ch);
    }
}