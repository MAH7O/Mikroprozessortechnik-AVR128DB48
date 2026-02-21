/**
* @file sensor.c
* @author Mahmoud Mahmoud
* @date 11/17/2024
* @brief dieses c datei gehört zu den sensor.h header datei da die methoden hier deklariert sind
*/

#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"

sensor* sensor_create(char* name, uint8_t busaddress, status statuscode, uinteger32 readvalue, uinteger32 writevalue){

    sensor* s;

    if((s = malloc(sizeof(sensor))) == NULL){
        perror("MALLOC: error while trying to allocate a space for sensor");
        exit(EXIT_FAILURE);
    }
    s->name = name;
    s->busaddress = busaddress;
    s->statuscode = statuscode;
    s->readvalue = readvalue;
    s->writevalue = writevalue;

    return s;
}

void sensor_delete(sensor* sensor){
    if(sensor == NULL){
        perror("DELETE: Error while trying to delete a specific sensor because it is empty");
        exit(EXIT_FAILURE);
    }
    free(sensor);
    sensor = NULL;
}

status sensor_read(sensor* sensor){
    printf("readvalue (Decimal): %d\n", sensor->readvalue.value);
    printf("readvalue (Bytes in Hex): ");
    for(int i = 0; i < sizeof(sensor->readvalue.bytes); i++){
        printf(" %02X", sensor->readvalue.bytes[i]);
    }
    printf("\n");
    return sensor->readvalue.value == 0 ? READ_ERR : SUCCESS;
}

status sensor_write(sensor* sensor){
    printf("writevalue (Decimal): %d\n", sensor->writevalue.value);
    printf("writevalue (Bytes in Hex):");
    for(int i = 0; i < sizeof(sensor->writevalue.bytes); i++){
        printf(" %02X", sensor->writevalue.bytes[i]);
    }

    printf("\n");

    return sensor->writevalue.value == 0 ? WRITE_ERR : SUCCESS;
}