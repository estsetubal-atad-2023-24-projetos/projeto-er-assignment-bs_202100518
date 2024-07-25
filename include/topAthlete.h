/**
 * @file topAthlete.h
 * 
 * @brief Provides definitions and operations for managing top athletes and their medal counts.
 * 
 * This header file defines structures and functions for tracking the performance of top athletes
 * in various games, focusing on the number of medals won and the specific events. It includes
 * operations to add and retrieve medals associated with particular games.
 * 
 * @author Raul Rohjans
 */
#pragma once

#include "athlete.h"
#include "medal.h"

#define MAX_TOP_COUNTRY_LENGTH 50
#define MAX_ATHLETE_NAME_LENGTH 100
#define MAX_GAME_LENGTH 50
#define MAX_MEDALS_GAME_LENGTH 50

/**
 * @brief Structure to store medals won by an athlete in a specific game.
 */
typedef struct medalsPerGame {
    int medals;
    char game[MAX_GAME_LENGTH];
} MedalsPerGame;

/**
 * @brief Structure to represent a top athlete, including overall medals and detailed game performance.
 */
typedef struct topAthlete {
    char athlete[MAX_ID_LENGTH];
    char country[MAX_TOP_COUNTRY_LENGTH];
    int totalMedals;
    MedalsPerGame medalsPerGame[MAX_MEDALS_GAME_LENGTH];
    int medalsPerGameSize;
    int daysPlayed;
} TopAthlete;

/**
 * @brief Retrieves the medals record for a specific game.
 * 
 * Searches an athlete's record for a given game and returns a pointer to the structure detailing
 * the medals won in that game, if it exists.
 * 
 * @param top Pointer to the TopAthlete structure.
 * @param game String representing the game to search for.
 * @return Pointer to the MedalsPerGame structure if found, NULL otherwise.
 */
MedalsPerGame* getMedalsPerGame(TopAthlete *top, char *game);

/**
 * @brief Adds a record of medals for a game to a top athlete's list.
 * 
 * This function appends a new MedalsPerGame entry to the athlete's record.
 * 
 * @param top Pointer to the TopAthlete structure where the entry will be added.
 * @param medalsPerGame The MedalsPerGame structure to add.
 */
void addMedalsPerGame(TopAthlete *top, MedalsPerGame medalsPerGame);