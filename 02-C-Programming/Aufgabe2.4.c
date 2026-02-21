#include <stdio.h>

int main(int argc, char *argv[]){
    printf("for loop version \n");
    for(int i = 0; i <= 9; i++){
        printf("%d\n", i);
    }
    printf("while loop version \n");
    int counter = 0;
    while (counter <= 9){
        printf("%d\n", counter);
        counter++;
    }
    return 0;
}