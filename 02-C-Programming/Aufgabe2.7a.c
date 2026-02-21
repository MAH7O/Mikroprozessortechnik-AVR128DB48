#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_TO_STRING_ARRAY_SIZE 11

char numToStr[NUM_TO_STRING_ARRAY_SIZE];

void convertUint32ToString(uint32_t number){

    int i = NUM_TO_STRING_ARRAY_SIZE - 2;
    numToStr[NUM_TO_STRING_ARRAY_SIZE - 1] = 0;

    if(number == 0){
        numToStr[i--] = 48;
    }

    while(number > 0){
        numToStr[i--] = (number % 10) + 48;
        number /= 10;
    }

    printf("%s\n", &numToStr[i+1]);
}

int main(int argc, char *argv[]){

    convertUint32ToString(140721);

    return 0;
}