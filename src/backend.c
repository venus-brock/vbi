#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "backend.h"

void init_field(char *input, int *counter, int64_t **stk_ptr, unsigned int *size, char *out);
bool step();

void stack_alloc(int dir);
int64_t stack_pop();
void stack_push(int64_t value);

unsigned int alloc = 0;
const int BLOCK_SIZE = 256;
int dir = 0;
char *output;
char *prog;
int *pc;
bool skip = false;
bool string_mode = false;
int64_t *stack;
int64_t **stack_ptr;
unsigned int *stack_size;

void init_field(char *input, int *counter, int64_t **stk_ptr, unsigned int *size, char *out){
    prog = input;
    pc = counter;
    stack_ptr = stk_ptr;
    stack = *stack_ptr;
    stack_size = size;
    output = out;
    return;
}

bool step(){
    char inst = *(prog + *pc * 80 + *(pc + 1));
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

    if(*(pc + 1) > 79) *(pc + 1) -= 80;
    if(*pc > 24) *pc -= 25;
    if(*(pc + 1) < 0) *(pc + 1) += 80;
    if(*pc < 0) *pc += 25;

    return false;
}

void stack_alloc(int alloc_dir){
    alloc += alloc_dir;
    size_t size = alloc * BLOCK_SIZE * sizeof(int64_t);
    int64_t *new_stack;
    if(alloc == 1 && alloc_dir == 1) new_stack = (int64_t*)malloc(size);
    else new_stack = (int64_t*)realloc(stack, size);
    if(new_stack == NULL){
        fprintf(stderr, "VBI: Memory (re)allocation failed.\n");
        free(stack);
        exit(1);
    }
    *stack_ptr = stack = new_stack;
}

int64_t stack_pop(){
    if(*stack_size > 0){
        (*stack_size)--;
        if(*stack_size == (alloc - 1) * BLOCK_SIZE && alloc > 1) stack_alloc(-1);
        return *(stack + *stack_size);
    }
    return 0;
}

void stack_push(int64_t value){
    if(*stack_size == alloc * BLOCK_SIZE) stack_alloc(1);
    *(stack + *stack_size) = value;
    (*stack_size)++;
    return;
}
