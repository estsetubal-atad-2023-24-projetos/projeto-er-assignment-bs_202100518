#include "medal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Medal* createMedal(const char* discipline, const char* event, const char* gender, char medalType, char participantType, const char* athleteId, const char* country) {
    Medal* newMedal = (Medal*) malloc(sizeof(Medal));
    if (newMedal) {
        strncpy(newMedal->discipline, discipline, MAX_DISC_LENGTH);
        strncpy(newMedal->eventTitle, event, MAX_EVENT_LENGTH);
        strncpy(newMedal->gender, gender, MAX_GENDER);
        newMedal->medalType = medalType;
        newMedal->participantType = participantType;
        strncpy(newMedal->athleteID, athleteId, MAX_ID_LENGTH);
        strncpy(newMedal->country, country, MAX_COUNTRY_LENGTH);
    }
    return newMedal;
}

// Função para imprimir informações da medalha
void printMedal(Medal* medal) {
    if (medal) {
        printf("Discipline: %s\n", medal->discipline);
        printf("Event: %s\n", medal->eventTitle);
        printf("Gender: %s\n", medal->gender);
        printf("Medal Type: %c\n", medal->medalType);
        printf("Participant Type: %c\n", medal->participantType);
        printf("Athlete ID: %s\n", medal->athleteID);
        printf("Country: %s\n", medal->country);
    }
}