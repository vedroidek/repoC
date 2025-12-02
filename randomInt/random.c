#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>


unsigned int random_int(unsigned int *, unsigned int *);
int is_number(const char *);
void print_help();


int main(int argc, char *argv[]) {

	int opt;
	char *values;
	unsigned int min = 1, max = 10;

	while ((opt = getopt(argc, argv, "r:h")) != -1) {
        switch (opt) {
            case 'h':
                print_help();
				return 0;
			case 'r':
				values = optarg;  // macros from getopt
				char *first, *last;

				// делим аргументы на части по символу ','
				first = strtok(values, ","); 
				last = strtok(NULL, ",");

				if (is_number(first) && is_number(last)) {
					min = atoi(first);
        			max = atoi(last);
				}

					if (min >= max) {
						perror("min >= max");
						return 1;
					}
                	break;
            case '?':
                return 1;
			default:
					printf("%u\n", random_int(&min, &max));
        }
    }

	printf("%u\n", random_int(&min, &max));

    return 0;
}

unsigned int random_int(unsigned int *min, unsigned int *max) {
    static unsigned long seed = 1;
    if (seed == 1) {
        seed = (unsigned long) time(NULL);
    }
    seed = (seed * 1103515245 + 12345) & __INT_MAX__;  // из-за одного INT_MAX решил не импортировать весь <limits.h>

    if (*min >= *max)
        return *min;
    
    return *min + (seed % (*max - *min + 1));
}

int is_number(const char *str) {
    if (str == NULL || *str == '\0')
		return 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
			return 0;
    }
    return 1;
}

void print_help() {
	puts("This program outputs a random number within a given range.\n\nOptions:\n");
	puts("By default, without arguments, a random number in the range from 1 to 10 is returned.");
	puts("\t-h\tprint help");
	puts("\t-r\tset range. First - MIN, second - MAX separated by commas. Example: \'-r 2,7\'");
};