/**
 * @file athlete.h
 * @brief Header file for the Athlete data type.
 *
 * This file defines the structure of the Athlete type and provides function
 * prototypes for creating, managing, and displaying athletes. The Athlete
 * structure includes fields for ID, name, number of games participated in,
 * the year of the first participation, and the birth year of the athlete.
 * This supports managing and displaying athlete records.
 * @author Raul Rohjans
 */
#pragma once

#define MAX_ID_LENGTH 50             ///< Maximum length for athlete ID.
#define MAX_ATHLETE_NAME_LENGTH 100  ///< Maximum length for athlete name.
#define MAX_GAME_LENGTH 50           ///< Maximum length for game name.

/**
 * Represents an athlete with various personal and participation details.
 */
typedef struct athlete {
    char athleteID[MAX_ID_LENGTH];              ///< Unique identifier for the athlete.
    char athleteName[MAX_ATHLETE_NAME_LENGTH];  ///< Athlete's name.
    int gamesParticipations;                    ///< Total number of games participated.
    int yearFirstParticipation;                 ///< Year of first participation in games.
    int athleteBirth;                           ///< Athlete's year of birth.
} Athlete;

/**
 * Creates a new athlete instance with provided details.
 * @param id Athlete's unique identifier.
 * @param name Athlete's name.
 * @param participations Number of games the athlete has participated in.
 * @param firstYear Year of the athlete's first participation.
 * @param birthYear Athlete's year of birth.
 * @return Pointer to the newly created Athlete instance.
 */
Athlete* createAthlete(const char* id, const char* name, int participations, int firstYear, int birthYear);

/**
 * Creates an empty athlete instance with default values.
 * @return Pointer to the newly created empty Athlete instance.
 */
Athlete* createEmptyAthlete();

/**
 * Prints the details of an athlete to standard output.
 * @param athlete The Athlete to print.
 */
void printAthlete(Athlete athlete);
