/**
 * @file host.c
 * @brief Implementation file for the Host data type.
 *
 * Implements functions to manage Host structures, including creating,
 * initializing, and displaying details of Host instances. Hosts represent
 * venues for Olympic games, encapsulating dates, locations, and other
 * descriptive information.
 */
#include "host.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Creates a new Host instance with specified details.
 * @param slug Unique slug identifier for the game.
 * @param endDate End date of the game in YYYY-MM-DD format.
 * @param startDate Start date of the game in YYYY-MM-DD format.
 * @param location Physical location of the game.
 * @param gameName Official name of the game.
 * @param season Season during which the game is held.
 * @param year Year the game is hosted.
 * @return Pointer to the newly created Host instance. Returns NULL if memory allocation fails.
 */
Host* createHost(const char* slug, const char* endDate, const char* startDate, const char* location,
                 const char* gameName, const char* season, int year) {
    Host* newHost = (Host*) malloc(sizeof(Host));
    if (newHost) {
        strncpy(newHost->gameSlug, slug, MAX_ID_LENGTH);
        strncpy(newHost->endDate, endDate, MAX_HOST_NAME_LENGTH);
        strncpy(newHost->startDate, startDate, MAX_HOST_NAME_LENGTH);
        strncpy(newHost->location, location, MAX_LOCATION_LENGTH);
        strncpy(newHost->gameName, gameName, MAX_GAME_NAME_LENGTH);
        strncpy(newHost->season, season, MAX_HOST_NAME_LENGTH);
        newHost->year = year;
    }
    return newHost;
}

/**
 * @brief Creates an empty Host instance with uninitialized fields.
 * @return Pointer to the newly created empty Host instance. Returns NULL if memory allocation fails.
 */
Host* createEmptyHost() {
    Host* newHost = (Host*) malloc(sizeof(Host));    
    return newHost;
}

/**
 * @brief Prints the details of a Host to standard output.
 * @param host The Host to print.
 */
void printHost(Host host) {
    char *hostingCity = getCharsOnlyFromString(host.gameName);
    int duration = getDateDiffInDays(host.startDate, host.endDate);

    printf("Hosting City: %s\n", hostingCity);
    printf("Year: %d\n", host.year);
    printf("Location: %s\n", host.location);
    printf("Duration (days): %d\n", duration);

    free(hostingCity);
}
