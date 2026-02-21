#include <stdio.h>
#include <stdint.h>

uint16_t set_bit (uint16_t number, uint8_t position){
return number |= 1 << position;
}

uint16_t swap_bytes (uint16_t number){
    uint16_t first8bits = number >> 8;
    uint16_t second8bits = number << 8;

    return first8bits | second8bits;
}

uint8_t get_high_nibble (uint8_t number){
    return number & 0xF0;
}

int main(int argc, char *argv[]){
    printf("set bit: %X\n", set_bit(0x0F, 4));
    printf("swap bytes: %X\n", swap_bytes (0x1234));
    printf("get high nibble: %X\n", get_high_nibble(0x67));

    return 0;
}