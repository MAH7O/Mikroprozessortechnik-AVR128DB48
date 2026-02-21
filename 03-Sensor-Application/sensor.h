/**
* @file sensor.h
* @author Mahmoud Mahmoud
* @date 11/11/2024
* @brief dieses header datei simuliert einen sensor mann kan einen sensor erstellen löschen lesen und überschreiben
*/

#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

typedef enum{
    SUCCESS,
    READ_ERR,
    WRITE_ERR
}status;

typedef union uinteger{
    uint32_t value;
    char bytes[4];
}uinteger32;

typedef struct{
    char* name;
    uint8_t busaddress;
    status statuscode;
    uinteger32 readvalue;
    uinteger32 writevalue;
} sensor;

/**
 * diese methode gillt für den ein neuen sensor erstellung
 * @param name name für den neuen sensor
 * @param busaddress liege den busaddresse des sensors
 * @param statuscode die aktuelle status code des sensors kann entweder SUCCESS, READ_ERR oder WRITE_ERR sein
 * @param readvalue liege den lese wert die beim lesen zurückgibt
 * @param writevalue liege den schreib wert die beim überschreiben zurückgibt
 * @return gibt ein zeiger auf den erstellten sensor zurück
 */
extern sensor* sensor_create(char* name, uint8_t busaddress, status statuscode, uinteger32 readvalue, uinteger32 writevalue);
/**
 * diese methode löscht ein aktueellen sensor
 * @param sensor zeiger auf den sensor die man löschen möchte
 */
extern void sensor_delete(sensor* sensor);
/**
 * diese methode gibt in der konsole den momentanige lese wert (readvalue) des sensors in dezimal als auch den bytes werte
 * @param sensor zeiger auf den sensor die man löschen möchte
 * @return gibt den aktuellen status des sensors zurück das kann entweder SUCCESS oder READ_ERR sein
 */
extern status sensor_read(sensor* sensor);
/**
 * diese methode gibt in der konsole den momentanige schreibe wert (writevalue) des sensors in dezimal als auch den bytes werte
 * @param sensor zeiger auf den sensor die man löschen möchte
 * @return gibt den aktuellen status des sensors zurück das kann entweder SUCCESS oder WRITE_ERR sein
 */
extern status sensor_write(sensor* sensor);
#endif


