/**
 * @file host.h
 * @brief Header file for the Host data type.
 *
 * This file defines the Host structure and declares functions for creating,
 * initializing, and displaying Host instances. Hosts represent locations and
 * other details about the venues of Olympic games, including dates and names.
 */
#pragma once

#define MAX_ID_LENGTH 50         ///< Maximum length for unique identifier.
#define MAX_HOST_NAME_LENGTH 50  ///< Maximum length for names related to the host.
#define MAX_LOCATION_LENGTH 100  ///< Maximum length for the location description.
#define MAX_GAME_NAME_LENGTH 50  ///< Maximum length for the name of the game.

/**
 * Represents a host venue for an Olympic event.
 */
typedef struct {
    char gameSlug[MAX_ID_LENGTH];          ///< Unique slug identifier for the game.
    char endDate[MAX_HOST_NAME_LENGTH];    ///< End date of the game.
    char startDate[MAX_HOST_NAME_LENGTH];  ///< Start date of the game.
    char location[MAX_LOCATION_LENGTH];    ///< Physical location of the event.
    char gameName[MAX_GAME_NAME_LENGTH];   ///< Official name of the game.
    char season[MAX_HOST_NAME_LENGTH];     ///< Season during which the game is held.
    int year;                              ///< Year the event is hosted.
} Host;

/**
 * @brief Creates a new Host instance with specified details.
 * @param slug Unique slug identifier for the game.
 * @param endDate End date of the game.
 * @param startDate Start date of the game.
 * @param location Physical location of the game.
 * @param gameName Official name of the game.
 * @param season Season during which the game is held.
 * @param year Year the game is hosted.
 * @return Pointer to the newly created Host instance.
 */
Host* createHost(const char* slug, const char* endDate, const char* startDate, const char* location,
                 const char* gameName, const char* season, int year);

/**
 * @brief Prints the details of a Host to standard output.
 * @param host The Host to print.
 */
void printHost(Host host);

/**
 * @brief Creates an empty Host instance with uninitialized fields.
 * @return Pointer to the newly created empty Host instance.
 */
Host* createEmptyHost();
