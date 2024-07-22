#include <stddef.h>
#include <string.h>
#include "topAthlete.h"

MedalsPerGame* getMedalsPerGame(TopAthlete *top, char *game) {
    for(int i = 0; i < top->medalsPerGameSize; i++) {
        if(strcmp(top->medalsPerGame[i].game, game) == 0)
            return &top->medalsPerGame[i];
    }

    return NULL;
}

void addMedalsPerGame(TopAthlete *top, MedalsPerGame medalsPerGame) {
    top->medalsPerGame[top->medalsPerGameSize-1] = medalsPerGame;
    top->medalsPerGameSize++;
}