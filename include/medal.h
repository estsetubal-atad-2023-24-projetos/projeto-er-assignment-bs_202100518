/**
 * @file medal.h
 * 
 * @brief Defines the Medal structure and provides functions for creating and managing medals.
 * 
 * This header file describes the structure of a Medal object, which includes detailed information
 * about the competition, the type of medal, and the recipient. It also provides function prototypes
 * for creating new medals, initializing them with data, and displaying medal information.
 * 
 * @author Raul Rohjans
 */
#pragma once

#define MAX_DISC_LENGTH 50     ///< Maximum length for discipline names.
#define MAX_GAME_LENGTH 50     ///< Maximum length for game names.
#define MAX_EVENT_LENGTH 100   ///< Maximum length for event titles.
#define MAX_ID_LENGTH 50       ///< Maximum length for athlete IDs.
#define MAX_COUNTRY_LENGTH 50  ///< Maximum length for country names.
#define MAX_GENDER 20          ///< Maximum length for gender description.

typedef struct medal {
    char discipline[MAX_DISC_LENGTH];   ///< Discipline of the competition.
    char game[MAX_GAME_LENGTH];         ///< Name of the game (e.g., Olympics 2020).
    char eventTitle[MAX_EVENT_LENGTH];  ///< Specific event title.
    char gender[MAX_GENDER];            ///< Gender category of the event.
    char medalType;                     ///< Type of medal ('G' for Gold, 'S' for Silver, 'B' for Bronze).
    char participantType;               ///< Type of participant ('A' for athlete, 'T' for team).
    char athleteID[MAX_ID_LENGTH];      ///< Unique identifier for the athlete.
    char country[MAX_COUNTRY_LENGTH];   ///< Country the athlete represents.
} Medal;

/**
 * @brief Creates and initializes a new Medal object.
 * 
 * Allocates memory for a new Medal and sets its properties based on the provided parameters.
 * Strings are copied safely to avoid buffer overflows.
 * 
 * @param discipline Name of the discipline.
 * @param event Title of the event.
 * @param gender Gender category of the competitors.
 * @param medalType Character representing the type of medal.
 * @param participantType Character representing the type of participant.
 * @param athleteId String representing the athlete's ID.
 * @param country Country the athlete represents.
 * @return Pointer to the newly created Medal, or NULL if memory allocation fails.
 */
Medal* createMedal(const char* discipline, const char* event, const char* gender,
                   char medalType, char participantType, const char* athleteId, const char* country);

/**
 * @brief Creates a Medal object without initializing its fields.
 * 
 * Allocates memory for a Medal but leaves its fields uninitialized. This function is typically
 * used when the Medal needs to be created before all its details are known.
 * 
 * @return Pointer to the newly created, uninitialized Medal.
 */
Medal* createEmptyMedal();

/**
 * @brief Prints the details of a Medal to standard output.
 * 
 * Displays comprehensive information about the medal, including the event, discipline, and recipient.
 * 
 * @param medal The Medal to print.
 */
void printMedal(Medal medal);
