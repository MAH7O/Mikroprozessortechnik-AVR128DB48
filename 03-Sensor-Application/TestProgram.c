/**
* @file TestProgram.c
* @author Mahmoud Mahmoud
* @date 11/17/2024
* @brief dieses c datei ist da damit man den sensor.h in viele möglichkeiten testen kann
*/

#include "sensor.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc > 1 && strcmp(argv[1], "--test") == 0) {
        if (argc > 2 && strcmp(argv[2], "drucksensor") == 0) {
            printf("----- drücksensor erstellung -----\n");
            printf("Sensor Name: druecksensor\n");
            printf("Busaddresse: 0x1A\n");
            printf("Status Code: SUCCESS\n");
            printf("Read Value: 10\n");
            printf("Write Value: 30\n");

            uinteger32 readvalue;
            readvalue.value = 10;
            uinteger32 writevalue;
            writevalue.value = 30;

            sensor *druecksensor = sensor_create("druecksensor", 0x1A, SUCCESS, readvalue, writevalue);

            printf("----- test durchführung -----\n\n");
            printf("--> read value\n");
            printf("erwartung in dezimal: 10\n");
            printf("erwartung in hexadezimal: 0A 00 00 00\n");
            printf("status erwartung: index 0 (SUCCESS) da der dezimalwert > 0 ist\n\n");
            printf("----- sensor ergebnisse -----\n");
            status readStatus = sensor_read(druecksensor);
            printf("status code: %d\n\n", readStatus);
            printf("----- test durchführung -----\n\n");
            printf("--> write value\n");
            printf("erwartung in dezimal: 30\n");
            printf("erwartung in hexadezimal: 1E 00 00 00\n");
            printf("status erwartung: index 0 (SUCCESS) da der dezimalwert > 0 ist\n\n");
            printf("----- sensor ergebnisse -----\n");
            status writeStatus = sensor_write(druecksensor);
            printf("status code: %d\n\n", writeStatus);

            printf("--> delete sensor\n");
            sensor_delete(druecksensor);
            printf("sensor sucessfully deleted\n");
        } else if (argc > 2 && strcmp(argv[2], "temperatursensor") == 0) {
            printf("----- temperatursensor erstellung -----\n");
            printf("Sensor Name: temperatursensor\n");
            printf("Busaddresse: 0xFA\n");
            printf("Status Code: SUCCESS\n");
            printf("Read Value: 0\n");
            printf("Write Value: 30\n");

            uinteger32 readvalue;
            readvalue.value = 0;
            uinteger32 writevalue;
            writevalue.value = 25;

            sensor *temperatursensor = sensor_create("temperatursensor", 0xFA, SUCCESS, readvalue, writevalue);

            printf("----- test durchführung -----\n\n");
            printf("--> read value\n");
            printf("erwartung in dezimal: 0\n");
            printf("erwartung in hexadezimal: 00 00 00 00\n");
            printf("status erwartung: index 1 (READ_ERR) da der dezimalwert = 0 ist\n\n");
            printf("----- sensor ergebnisse -----\n");
            status readStatus = sensor_read(temperatursensor);
            printf("status code: %d\n\n", readStatus);
            printf("----- test durchführung -----\n\n");
            printf("--> write value\n");
            printf("erwartung in dezimal: 25\n");
            printf("erwartung in hexadezimal: 19 00 00 00\n");
            printf("status erwartung: index 0 (SUCCESS) da der dezimalwert > 0 ist\n\n");
            printf("----- sensor ergebnisse -----\n");
            status writeStatus = sensor_write(temperatursensor);
            printf("status code: %d\n\n", writeStatus);

            printf("--> delete sensor\n");
            sensor_delete(temperatursensor);
            printf("sensor sucessfully deleted\n");
        } else if (argc > 2 && strcmp(argv[2], "feuchtigkeitsensor") == 0) {
            printf("----- feuchtigkeitsensor erstellung -----\n");
            printf("Sensor Name: feuchtigkeitsensor\n");
            printf("Busaddresse: 0xFF\n");
            printf("Status Code: SUCCESS\n");
            printf("Read Value: 0\n");
            printf("Write Value: 0\n");

            uinteger32 readvalue;
            readvalue.value = 0;
            uinteger32 writevalue;
            writevalue.value = 0;

            sensor *feuchtigkeitsensor = sensor_create("temperatursensor", 0xFF, SUCCESS, readvalue, writevalue);

            printf("----- test durchführung -----\n\n");
            printf("--> read value\n");
            printf("erwartung in dezimal: 0\n");
            printf("erwartung in hexadezimal: 00 00 00 00\n");
            printf("status erwartung: index 1 (READ_ERR) da der dezimalwert = 0 ist\n\n");
            printf("----- sensor ergebnisse -----\n");
            status readStatus = sensor_read(feuchtigkeitsensor);
            printf("status code: %d\n\n", readStatus);
            printf("----- test durchführung -----\n\n");
            printf("--> write value\n");
            printf("erwartung in dezimal: 0\n");
            printf("erwartung in hexadezimal: 00 00 00 00\n");
            printf("status erwartung: index 2 (WRITE_ERR) da der dezimalwert = 0 ist\n\n");
            printf("----- sensor ergebnisse -----\n");

            status writeStatus = sensor_write(feuchtigkeitsensor);
            printf("status code: %d\n\n", writeStatus);

            printf("--> delete sensor\n");
            sensor_delete(feuchtigkeitsensor);
            printf("sensor sucessfully deleted\n");
        }else if(argc > 2 && strcmp(argv[2], "--list") == 0){
            printf("----- sensor test list -----\n");
            printf("--> drucksensor\n");
            printf("--> temperatursensor\n");
            printf("--> feuchtigkeitsensor\n");
        }else{
                printf("ERROR! Unbekanntes sensor '%s --test --list' um alle verfügbare sensoren zu zeigen\n", argv[0]);
        }

    }else{
        printf("----- verfügbare commands -----\n");
        printf("-->%s --test <sensor> -/- starte ein test für ein bestimmte verfügbare sensor\n", argv[0]);
        printf("-->%s --test --list -/- liste alle verfügbare sensoren\n", argv[0]);
    }
    return 0;

}
