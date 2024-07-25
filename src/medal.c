/**
 * @file medal.c
 * 
 * @brief Provides the implementation for Medal operations.
 * 
 * This file includes functions to create new Medal instances, initialize them with data,
 * and print their contents. It facilitates the management of Medal objects throughout
 * the application.
 * 
 * @author Raul Rohjans
 */
#include "medal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Creates a new Medal instance and initializes it with the provided details.
 * 
 * Allocates memory for a new Medal and sets its properties based on the provided parameters.
 * The strings are copied safely to avoid buffer overflow.
 * 
 * @param discipline Name of the discipline for which the medal is awarded.
 * @param event Title of the event the medal is associated with.
 * @param gender Gender category of the event.
 * @param medalType Type of the medal ('G' for Gold, 'S' for Silver, 'B' for Bronze).
 * @param participantType Type of the participant ('A' for Athlete, 'T' for Team).
 * @param athleteId Identifier for the athlete or team.
 * @param country Country the athlete represents.
 * @return Pointer to the newly created Medal instance, or NULL if memory allocation fails.
 */
Medal* createMedal(const char* discipline, const char* event, const char* gender, char medalType, char participantType, const char* athleteId, const char* country) {
    Medal* newMedal = (Medal*) malloc(sizeof(Medal));
    if (newMedal) {
        strncpy(newMedal->discipline, discipline, MAX_DISC_LENGTH);
        strncpy(newMedal->eventTitle, event, MAX_EVENT_LENGTH);
        strncpy(newMedal->gender, gender, MAX_GENDER);
        newMedal->medalType = medalType;
        newMedal->participantType = participantType;
        strncpy(newMedal->athleteID, athleteId, MAX_ID_LENGTH);
        strncpy(newMedal->country, country, MAX_COUNTRY_LENGTH);
    }
    return newMedal;
}

/**
 * @brief Creates an empty Medal instance.
 * 
 * Allocates memory for a new Medal but does not initialize its fields.
 * 
 * @return Pointer to the newly created empty Medal instance.
 */
Medal* createEmptyMedal() {
    Medal* newMedal = (Medal*) malloc(sizeof(Medal));    
    return newMedal;
}

/**
 * @brief Prints the details of a Medal to standard output.
 * 
 * Displays information about the discipline, event, gender, type of medal, participant,
 * athlete ID, and the country represented.
 * 
 * @param medal The Medal to print.
 */
void printMedal(Medal medal) {
    printf("Discipline: %s\n", medal.discipline);
    printf("Event: %s\n", medal.eventTitle);
    printf("Gender: %s\n", medal.gender);
    printf("Medal Type: %c\n", medal.medalType);
    printf("Participant Type: %c\n", medal.participantType);
    printf("Athlete ID: %s\n", medal.athleteID);
    printf("Country: %s\n", medal.country);
}
