/**
 * @file athlete.c
 * @brief Implementation file for the Athlete data type.
 *
 * Implements the functions declared in athlete.h for managing and
 * displaying Athlete information. It includes functions to create new
 * athlete instances, initialize them with data, and print their details.
 * Memory management and string operations are handled carefully to prevent
 * errors and ensure data integrity.
 * @author Raul Rohjans
 */
#include "athlete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Creates a new athlete instance with specified details.
 * @param id Athlete's unique identifier.
 * @param name Athlete's name.
 * @param participations Number of games the athlete has participated in.
 * @param firstYear Year of the athlete's first participation.
 * @param birthYear Athlete's year of birth.
 * @return Pointer to the newly created Athlete instance, or NULL if allocation fails.
 */
Athlete* createAthlete(const char* id, const char* name, int participations, int firstYear, int birthYear) {
    Athlete *newAthlete = createEmptyAthlete();
    if (newAthlete) {
        strncpy(newAthlete->athleteID, id, MAX_ID_LENGTH);
        strncpy(newAthlete->athleteName, name, MAX_ATHLETE_NAME_LENGTH);
        newAthlete->gamesParticipations = participations;
        newAthlete->yearFirstParticipation = firstYear;
        newAthlete->athleteBirth = birthYear;
    }
    return newAthlete;
}

/**
 * @brief Creates an empty athlete instance with uninitialized fields.
 * @return Pointer to the newly created empty Athlete instance, or NULL if allocation fails.
 */
Athlete* createEmptyAthlete() {
    Athlete* newAthlete = (Athlete*) malloc(sizeof(Athlete));    
    return newAthlete;
}

/**
 * @brief Prints the details of an athlete to standard output.
 * @param athlete The Athlete to print.
 */
void printAthlete(Athlete athlete) {
    printf("Athlete ID: %s\n", athlete.athleteID);
    printf("Name: %s\n", athlete.athleteName);
    printf("Games Participations: %d\n", athlete.gamesParticipations);
    printf("First Participation: %d\n", athlete.yearFirstParticipation);
    printf("Birth Year: %d\n", athlete.athleteBirth);
}
