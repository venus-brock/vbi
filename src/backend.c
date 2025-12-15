#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "backend.h"

void init_field(char *input, int64_t **stk_ptr, int32_t *size, char *out);
bool step();

int64_t stack_pop();
void stack_push(long value);

const int BLOCK_SIZE = 256;
uint32_t alloc = 1;
int64_t *stack;
int64_t **stack_ptr;
int32_t *stack_size;
char *prog;
char *output;
int pc[2] = {0, 0};
int dir = 0;
bool string_mode = false;
bool skip = false;

void init_field(char *input, int64_t **stk_ptr, int32_t *size, char *out){
    prog = input;
    stack_ptr = stk_ptr;
    stack = *stack_ptr;
    stack_size = size;
    output = out;
    return;
}

bool step(){
    char inst = *(prog + pc[0] * 80 + pc[1]);
    if(string_mode){
        if(inst == '"') string_mode = false;
        else stack_push(inst);
    }else{
        switch(inst){
        case '>':
            dir = 0;
            break;
        case 'v':
            dir = 1;
            break;
        case '<':
            dir = 2;
            break;
        case '^':
            dir = 3;
            break;
        case '?':
            dir = rand() % 4;
            break;
        case '"':
            string_mode = true;
            break;
        case '.':
            sprintf(output, "%li ", stack_pop());
            break;
        case ',':
            sprintf(output, "%c", stack_pop());
            break;
        case '+':
            stack_push(stack_pop() + stack_pop());
            break;
        case '-':{
            int64_t tmp = stack_pop();
            stack_push(-tmp + stack_pop());
            break;
        }
        case '/':{
            int64_t tmp = stack_pop();
            stack_push(stack_pop() / tmp);
            break;
        }
        case '*':
            stack_push(stack_pop() * stack_pop());
            break;
        case '%':{
            int64_t tmp = stack_pop();
            stack_push(stack_pop() % tmp);
            break;
        }
        case '!':
            stack_push(stack_pop() == 0);
            break;
        case '_':
            dir = (stack_pop() != 0) * 2;
            break;
        case '|':
            dir = (stack_pop() != 0) * 2 + 1;
            break;
        case '`':{
            int64_t tmp = stack_pop();
            stack_push(tmp < stack_pop());
            break;
        }
        case ':':{
            int64_t tmp = stack_pop();
            stack_push(tmp);
            stack_push(tmp);
            break;
        }
        case '\\':{
            int64_t tmp1 = stack_pop();
            int64_t tmp2 = stack_pop();
            stack_push(tmp1);
            stack_push(tmp2);
            break;
        }
        case '$':
            stack_pop();
            break;
        case '#':
            skip = true;
            break;
        case '@':
            return true;
        case 'g':{
            // note that no bound checking is performed here nor in case 'p'.
            // the original befunge-93 spec does not define any particular
            // behaviour for if the selected coordinates are outside the bounds
            // of the playfield.
            int64_t tmp = stack_pop();
            stack_push(*(prog + tmp * 80 + stack_pop()));
            break;
        }
        case 'p':{
            int64_t tmp1 = stack_pop();
            int64_t tmp2 = stack_pop();
            *(prog + tmp1 * 80 + tmp2) = stack_pop();
            break;
        }
        case '~':
            stack_push(getchar());
            break;
        case '&':{
            int64_t tmp;
            scanf("%li", &tmp);
            stack_push(tmp);
            break;
        }
        default:
            // if the current character is a numeral
            if(inst > 47 && inst < 58) stack_push(inst - 48);
        }
    }
    switch(dir){
    case 0: case 1:
        pc[!dir] += skip + 1;
        break;
    case 2: case 3:
        pc[!(dir - 2)] -= skip + 1;
        break;
    }

    skip = false;

    if(pc[1] > 79) pc[1] %= 80;
    if(pc[0] > 24) pc[0] %= 25;
    if(pc[1] < 0) pc[1] += 80;
    if(pc[0] < 0) pc[0] += 25;

    return false;
}

int64_t stack_pop(){
    if(*stack_size > 0){
        (*stack_size)--;
        return *(stack + *stack_size);
    }
    return 0;
}

void stack_push(int64_t value){
    if(*stack_size == alloc * BLOCK_SIZE){
        alloc++;
        int64_t *new_stack = (int64_t*)realloc(stack, alloc * BLOCK_SIZE * sizeof(int64_t));
        if(new_stack == NULL){
            fprintf(stderr, "VBI: Memory reallocation failed.\n");
            free(stack);
            exit(1);
        }
        stack = new_stack;
        *stack_ptr = stack;
    }
    *(stack + *stack_size) = value;
    (*stack_size)++;
    return;
}
