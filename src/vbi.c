#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "backend.h"

int main(int argc, char **argv){
    if(argc != 2){
        printf("USAGE: vbi <path to .b93 source file>\n");
        return 0;
    }

    char prog[25][80];
    FILE *source;
    const int BLOCK_SIZE = 256;
    int32_t stack_size = 0;
    int32_t *stack_size_ptr = &stack_size;
    int64_t *stack;
    int64_t **stack_ptr = &stack;
    char output[21] = "";
    source = fopen(argv[1], "r");
    if(source == NULL){
        fprintf(stderr, "VBI: Failed opening file \"%s\"\n", argv[1]);
        exit(1);
    }

    for(int i = 0; i < 25; i++){
        for(int j = 0; j < 80; j++){
            prog[i][j] = '\0';
        }
    }

    for(int i = 0; i < 25; i++){
        char tmp[82];
        if(fgets(tmp, 82, source) == NULL) break;
        strncpy(prog[i], tmp, 80);
        if(strlen(prog[i]) < 80) prog[i][strlen(prog[i]) - 1] = '\0';
    }
    fclose(source);

    stack = (int64_t*)malloc(BLOCK_SIZE * sizeof(int64_t));
    if(stack == NULL){
        fprintf(stderr, "VBI: Memory allocation failed.\n");
        exit(1);
    }

    init_field(&(prog[0][0]), stack_ptr, stack_size_ptr, output);
    srand(time(0));
    while(!step()){
        if(strlen(output) > 0){ 
            printf(output);
            output[0] = '\0';
        }
        if(*stack_ptr != stack) stack = *stack_ptr;
        fflush(stdout);
        usleep(10000);
    }

    printf("\n");
    return 0;
}
