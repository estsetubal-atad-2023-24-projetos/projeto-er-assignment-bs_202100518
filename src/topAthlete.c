/**
 * @file topAthlete.c
 * 
 * @brief Provides functions for managing the medals and games associated with top athletes.
 * 
 * This file includes functions to access and modify the details of medals awarded in specific games
 * as they pertain to top athletes. It supports the tracking of an athlete's performance across different
 * games and the accumulation of their medals.
 * 
 */

#include <stddef.h>
#include <string.h>
#include "topAthlete.h"

/**
 * @brief Retrieves a pointer to the medals awarded in a specific game for a given athlete.
 * 
 * Searches through an athlete's medals per game to find a specific game and returns a pointer
 * to the structure detailing the medals won in that game.
 * 
 * @param top Pointer to a TopAthlete structure.
 * @param game String representing the game to search for.
 * @return Pointer to the MedalsPerGame structure if found, NULL otherwise.
 */
MedalsPerGame* getMedalsPerGame(TopAthlete *top, char *game) {
    for(int i = 0; i < top->medalsPerGameSize; i++) {
        if(strcmp(top->medalsPerGame[i].game, game) == 0)
            return &top->medalsPerGame[i];
    }

    return NULL;
}

/**
 * @brief Adds a record of medals per game to a top athlete's list of games and medals.
 * 
 * This function appends a new MedalsPerGame structure to the athlete's list, expanding
 * their record of participations and achievements.
 * 
 * @param top Pointer to a TopAthlete structure where the medals per game will be added.
 * @param medalsPerGame The MedalsPerGame structure to add to the athlete's record.
 */
void addMedalsPerGame(TopAthlete *top, MedalsPerGame medalsPerGame) {
    top->medalsPerGame[top->medalsPerGameSize-1] = medalsPerGame;
    top->medalsPerGameSize++;
}