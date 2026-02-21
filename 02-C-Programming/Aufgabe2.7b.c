#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STACK_SIZE 32


unsigned int *stack;
int sp;

char* numToStr;

void push(int num){
    if(sp >= STACK_SIZE){
        perror("ERROR! stack overflow");
        exit(EXIT_FAILURE);
    }else{
        stack[sp++] = num;
    }
}

int pop(){
    if(sp <= 0){
        perror("ERROR! stack underflow");
        exit(EXIT_FAILURE);
    }
    return stack[--sp];
}

void initStack(size_t size){
    if((stack = malloc(size * sizeof (unsigned int))) == NULL){
        perror("stack init error MALLOC !");
        exit(EXIT_FAILURE);
    }
}

void initNumToStr(size_t size){
    if((numToStr = malloc(size * sizeof(char))) == NULL){
        perror("MALLOC ERROR! while trying to convert the int into a String");
        exit(EXIT_FAILURE);
    }
}

char* convertUint32ToString(uint32_t number){
    if(number == 0){
        initNumToStr(sp + 1);
        *(numToStr + 0) = 48;
        return numToStr;
    }
    uint32_t num = number;

    while(num != 0){
        push(num % 10);
        num /= 10;
    }

    initNumToStr(sp + 1);

    for(int i = 0; sp != 0; i++){
        *(numToStr + i) = pop() + 48;
    }


    return numToStr;
}

int main(int argc, char *argv[]){

    initStack(STACK_SIZE);

    printf("%s\n", convertUint32ToString(140721));

    free(numToStr);
    free(stack);

    return 0;
}