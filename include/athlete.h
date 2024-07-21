#pragma once

#define MAX_ID_LENGTH 50
#define MAX_ATHLETE_NAME_LENGTH 100
#define MAX_GAME_LENGTH 50

typedef struct athlete {
    char athleteID[MAX_ID_LENGTH]; // Identificador único do atleta
    char athleteName[MAX_ATHLETE_NAME_LENGTH]; // Nome do atleta
    int gamesParticipations; // Número de jogos em que participou
    int yearFirstParticipation; // O ano em que participou pela primeira vez
    int athleteBirth;// Ano de nascimento
} Athlete;

Athlete* createAthlete(const char* id, const char* name, int participations, int firstYear, int birthYear);

Athlete* createEmptyAthlete();

void printAthlete(Athlete athlete);
