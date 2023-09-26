#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");

    if(file == NULL) {
        printf("Error: cannot open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    while(!feof(file)) {
        char c = fgetc(file);
        printf("%c", c);
    }

    return EXIT_SUCCESS;
}