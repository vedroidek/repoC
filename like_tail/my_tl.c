#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>

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

    while ((opt = getopt(argc, argv, "o:s:f:hv")) != -1) {
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
            case 'h':
                print_help();
            case 'v':
                puts(VERSION);
                exit(EXIT_SUCCESS);
            case '?':
                fprintf(stderr, "Error: unknown option \'-%s\'.\n", optarg);
                exit(EXIT_FAILURE);
            default:
                printf("Help.\n\v");
                puts("-v      show current version;");
                puts("-f      set output file;");
                exit(EXIT_SUCCESS);    
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
        fprintf(stderr, "Error opening file");
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
    long pos;
    long new_pos;
    int ch;

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

        if (new_pos > pos) {
            fseek(fptr, pos, SEEK_SET);
            while ((ch = getc(fptr)) != EOF) {
                    putchar(ch);
                }
            fflush(stdout);
            pos = new_pos;
        }

        sleep(1);
    }
    puts("\nExit.");
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