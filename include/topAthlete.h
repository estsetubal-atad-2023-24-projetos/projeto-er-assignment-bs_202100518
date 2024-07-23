#pragma once

#include "athlete.h"
#include "medal.h"

#define MAX_TOP_COUNTRY_LENGTH 50
#define MAX_ATHLETE_NAME_LENGTH 100
#define MAX_GAME_LENGTH 50
#define MAX_MEDALS_GAME_LENGTH 50

typedef struct medalsPerGame {
    int medals;
    char game[MAX_GAME_LENGTH];
} MedalsPerGame;

typedef struct topAthlete {
    char athlete[MAX_ID_LENGTH];
    char country[MAX_TOP_COUNTRY_LENGTH];
    int totalMedals;
    MedalsPerGame medalsPerGame[MAX_MEDALS_GAME_LENGTH];
    int medalsPerGameSize;
    int daysPlayed;
} TopAthlete;

MedalsPerGame* getMedalsPerGame(TopAthlete *top, char *game);

void addMedalsPerGame(TopAthlete *top, MedalsPerGame medalsPerGame);