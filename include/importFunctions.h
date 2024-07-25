/**
 * @file importFunctions.h
 * @brief Header file for functions that import data from CSV files.
 *
 * Defines the interface for functions responsible for importing athletes, medals, and hosts
 * from CSV files into the application. These functions create and populate lists and maps
 * with data structured according to the application's data models.
 */
#pragma once

#include "list.h"
#include "listMedal.h"
#include "map.h"


/**
 * @brief Imports a list of athletes from a CSV file.
 * 
 * Reads athletes data from a predefined CSV file format and constructs a list of Athlete structures.
 * Each line in the CSV is expected to represent one athlete with fields separated by semicolons.
 *
 * @return A pointer to a list of Athlete structures, or NULL if the file cannot be opened or if parsing fails.
 */
PtList importAthletes();

/**
 * @brief Imports a list of medals from a CSV file.
 *
 * Reads medals data from a predefined CSV file format and constructs a list of Medal structures.
 * Each line in the CSV is expected to represent one medal with fields separated by semicolons.
 *
 * @return A pointer to a list of Medal structures, or NULL if the file cannot be opened or if parsing fails.
 */
PtListMedal importMedals();

/**
 * @brief Imports mapping of game hosts from a CSV file.
 *
 * Reads host data from a predefined CSV file format and constructs a map where each key is a game slug
 * and the value is a Host structure representing the host details of that game.
 * Each line in the CSV is expected to represent one host with fields separated by semicolons.
 *
 * @return A pointer to a map of Host structures, or NULL if the file cannot be opened or if parsing fails.
 */
PtMap importHosts();
