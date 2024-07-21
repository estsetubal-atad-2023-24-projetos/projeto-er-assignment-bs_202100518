#pragma once

#define MAX_DISC_LENGTH 50
#define MAX_GAME_LENGTH 50
#define MAX_EVENT_LENGTH 100
#define MAX_ID_LENGTH 50
#define MAX_COUNTRY_LENGTH 50
#define MAX_GENDER 20

typedef struct medal {
    char discipline[MAX_DISC_LENGTH]; // Modalidade
    char game[MAX_GAME_LENGTH]; // Nome da edição dos jogos olímpicos (ex. beijing-2022)
    char eventTitle[MAX_EVENT_LENGTH]; // Título da prova (ex. Women's Ski cross)
    char gender[MAX_GENDER]; // Género da prova
    char medalType; // G - GOLD, S - SILVER, B - BRONZE
    char participantType; // A - Athlete, G - GameTeam
    char athleteID[MAX_ID_LENGTH]; // Identificador de cada atleta
    char country[MAX_COUNTRY_LENGTH]; // País pelo qual o atleta competiu
} Medal;

// Função para criar uma nova medalha
Medal* createMedal(const char* discipline, const char* event, const char* gender,
                   char medalType, char participantType, const char* athleteId, const char* country);

void printMedal(Medal medal);
