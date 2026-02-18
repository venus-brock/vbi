#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "vbi.h"
#include "vbi_version.h"

int64_t cli_get_int(void);

int main(int argc, char **argv){
    if(argc != 2){
        printf("USAGE: vbi <path to .b93 source file>\n");
        return 0;
    }

    if(!strncmp(argv[1], "--version", 10)){
        printf("VBI " VBI_VERSION "\n");
        printf("Copyright (c) " VBI_COPYRIGHT_YEARS
            " Venus Brock - venus@brock-v.dev\n");
        return 0;
    }

    char output[21] = "";
    int pc[2] = {0, 0};
    char prog[25][80];
    FILE *source;
    int64_t *stack = NULL;
    int64_t **stack_ptr = &stack;
    unsigned int stack_size = 0;
    
    if(strncmp(argv[1], "-i", 3)){
        source = fopen(argv[1], "r");
        if(source == NULL){
            fprintf(stderr, "VBI: Failed opening file \"%s\"\n", argv[1]);
            return 1;
        }
    } else source = stdin;

    for(int i = 0; i < 25; i++)
        for(int j = 0; j < 80; j++) prog[i][j] = ' ';

    for(int i = 0; i < 25; i++){
        bool file_end = false;
        int j = 0;
        for(j = 0; j < 80; j++){
            prog[i][j] = fgetc(source);
            if(prog[i][j] == EOF) file_end = true;
            if(prog[i][j] == EOF || prog[i][j] == '\n'){
                prog[i][j] = ' ';
                break;
            }
        }
        if(file_end) break;
    }
    
    if(source != stdin) fclose(source);

    init_field(&(prog[0][0]), pc, stack_ptr, &stack_size, output);
    set_inputs((char(*)(void))getchar, cli_get_int);
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

int64_t cli_get_int(void){
    int64_t tmp;
    scanf("%li", &tmp);
    return tmp;
}
