#include "config.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h> 

static UserData* userData = NULL; // Puntero estático para la instancia

UserData* initUserData() {

    // Verificar si ya existe una instancia
    if (userData != NULL) {
        return userData;
    }

    // Abrir el archivo 
    FILE *fp = fopen("config-file/config.json", "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return NULL; 
    } 
  
    // Leer el contenido del archivo en una cadena 
    char buffer[1024]; 
    int len = fread(buffer, 1, sizeof(buffer) - 1, fp); 
    buffer[len] = '\0'; // Asegurarse de que la cadena esté terminada en null
    fclose(fp); 
  
    // Analizar los datos JSON 
    cJSON *json = cJSON_Parse(buffer); 
    if (json == NULL) { 
        const char *error_ptr = cJSON_GetErrorPtr(); 
        if (error_ptr != NULL) { 
            printf("Error: %s\n", error_ptr); 
        } 
        return NULL; 
    } 

    // Asignar memoria para el UserData
    userData = malloc(sizeof(UserData));
    if (userData == NULL) {
        printf("Error: Unable to allocate memory for UserData.\n");
        cJSON_Delete(json);
        return NULL;
    }

    // Acceder a los datos JSON 
    cJSON *controlMethod = cJSON_GetObjectItemCaseSensitive(json, "controlMethod"); 
    cJSON *scheduler = cJSON_GetObjectItemCaseSensitive(json, "scheduler");
    cJSON *canalLength = cJSON_GetObjectItemCaseSensitive(json, "canalLength");
    cJSON *shipSpeed = cJSON_GetObjectItemCaseSensitive(json, "shipSpeed");
    cJSON *amountShipsInQ = cJSON_GetObjectItemCaseSensitive(json, "amountShipsInQ");
    cJSON *controlSignTime = cJSON_GetObjectItemCaseSensitive(json, "controlSignTime");
    cJSON *W = cJSON_GetObjectItemCaseSensitive(json, "W");

    // Asignar el método de control
    if (cJSON_IsString(controlMethod) && (controlMethod->valuestring != NULL)) {
        userData->controlMethod = malloc(strlen(controlMethod->valuestring) + 1);
        if (userData->controlMethod != NULL) {
            strcpy(userData->controlMethod, controlMethod->valuestring);
        }
    } else {
        userData->controlMethod = NULL; // Manejar el caso en que no sea una cadena válida
    }

    // Asignar el calendarizador
    if (cJSON_IsString(scheduler) && (scheduler->valuestring != NULL)) {
        userData->scheduler = malloc(strlen(scheduler->valuestring) + 1);
        if (userData->scheduler != NULL) {
            strcpy(userData->scheduler, scheduler->valuestring);
        }
    } else {
        userData->scheduler = NULL; // Manejar el caso en que no sea una cadena válida
    }

    // Asignar los valores restantes
    userData->canalLength = cJSON_GetNumberValue(canalLength);
    userData->shipSpeed = cJSON_GetNumberValue(shipSpeed);
    userData->amountShipsInQ = cJSON_GetNumberValue(amountShipsInQ);
    userData->controlSignTime = cJSON_GetNumberValue(controlSignTime);
    userData->W = cJSON_GetNumberValue(W);

    // Eliminar el objeto JSON 
    cJSON_Delete(json); 

    return userData; // Retorna el puntero
}

void printUserData() {
    if (userData == NULL) {
        printf("No user data to print.\n");
        return;
    }
    printf("Control Method: %s\n", userData->controlMethod ? userData->controlMethod : "NULL");
    printf("Scheduler: %s\n", userData->scheduler ? userData->scheduler : "NULL");
    printf("Canal Length: %d\n", userData->canalLength);
    printf("Ship Speed: %d\n", userData->shipSpeed);
    printf("Amount of Ships in Queue: %d\n", userData->amountShipsInQ);
    printf("Control Sign Time: %d s\n", userData->controlSignTime);
    printf("W: %d\n", userData->W);
}

void freeUserData() {
    if (userData != NULL) {
        free(userData->controlMethod); // Liberar la memoria del controlMethod
        free(userData->scheduler); // Liberar la memoria del scheduler

        free(userData); // Liberar la memoria del UserData
        userData = NULL; // Establecer a NULL para evitar acceso posterior
    }
}
