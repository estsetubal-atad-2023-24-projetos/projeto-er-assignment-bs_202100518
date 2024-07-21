#include "athlete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Criar um novo atleta
Athlete* createAthlete(const char* id, const char* name, int participations, int firstYear, int birthYear) {
    Athlete* newAthlete = (Athlete*) malloc(sizeof(Athlete));
    if (newAthlete) {
        strncpy(newAthlete->athleteID, id, MAX_ID_LENGTH);
        strncpy(newAthlete->athleteName, name, MAX_NAME_LENGTH);
        newAthlete->gamesParticipations = participations;
        newAthlete->yearFirstParticipation = firstYear;
        newAthlete->athleteBirth = birthYear;
    }
    return newAthlete;
}

// Imprimir informações do atleta
void printAthlete(Athlete athlete) {
    printf("Athlete ID: %s\n", athlete.athleteID);
    printf("Name: %s\n", athlete.athleteName);
    printf("Games Participations: %d\n", athlete.gamesParticipations);
    printf("First Participation: %d\n", athlete.yearFirstParticipation);
    printf("Birth Year: %d\n", athlete.athleteBirth);
}