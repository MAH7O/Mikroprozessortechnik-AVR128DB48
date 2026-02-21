#include <stdio.h>
#include <stdlib.h>

char *letters;

void initLetters(){
    if((letters = malloc(25 * sizeof (char))) == NULL){
        perror("letters init error MALLOC !");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]){

    initLetters();

    char *currentChar = letters;

    for(int i = 0; i < 26; i++){
        *currentChar++ = i + 65;
    }

    char *printCurrentChar = letters;
    while(*printCurrentChar != '\0'){
        printf("%c\n", *printCurrentChar);
        printCurrentChar++;
    }

    free(letters);

    return 0;
}