#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "backend.h"

int main(int argc, char **argv){
    if(argc != 2){
        printf("USAGE: vbi <path to .b93 source file>\n");
        return 0;
    }

    char prog[25][80];
    FILE *source;
    int64_t *stack = NULL;
    int64_t **stack_ptr = &stack;
    unsigned int stack_size = 0;
    unsigned int *stack_size_ptr = &stack_size;
    char output[21] = "";
    
    source = fopen(argv[1], "r");
    if(source == NULL){
        fprintf(stderr, "VBI: Failed opening file \"%s\"\n", argv[1]);
        return 1;
    }

    for(int i = 0; i < 25; i++)
        for(int j = 0; j < 80; j++) prog[i][j] = ' ';

    for(int i = 0; i < 25; i++){
        char tmp[82]; // two greater than the maximum line length to account for
                      // line breaks and null terminators
        if(fgets(tmp, 82, source) == NULL) break;
        strncpy(prog[i], tmp, strlen(tmp) - 1);
    }
    fclose(source);

    init_field(&(prog[0][0]), stack_ptr, stack_size_ptr, output);
    srand(time(0));

    while(!step()){
        if(strlen(output) > 0){
            printf(output);
            output[0] = '\0';
        }
        stack = *stack_ptr;
    }
    if(stack != NULL) free(stack);
    return 0;
}
