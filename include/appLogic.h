/**
 * @file appLogic.h
 * @brief Header file for application logic functions in the Olympics Super Parser program.
 *
 * Declares functions for manipulating and querying athlete and medal data,
 * including sorting, filtering, pagination, and detailed analytics. This header
 * provides interfaces for displaying data, handling user interactions for data
 * retrieval, and performing complex queries on the dataset.
 */
#pragma once

#include "list.h"
#include "listMedal.h"
#include "map.h"
#include "adtSet.h"

/**
 * @brief Paginates and displays a list of athletes.
 * @param athletes The list of athletes to paginate.
 */
void paginate(PtList athletes);

/**
 * @brief Sorts a list of athletes alphabetically by their names.
 * @param athletes Pointer to the list of athletes to be sorted.
 */
void orderAthletesAlphabetic(PtList *athletes);

/**
 * @brief Creates a shallow copy of a list of athletes.
 * @param athletes The original list of athletes.
 * @return A new list containing a shallow copy of the athletes.
 */
PtList listAthleteShallowCopy(PtList athletes);

/**
 * @brief Filters athletes based on the number of participations.
 * @param athletes The list of athletes to filter.
 * @param participations Minimum number of participations to filter by.
 * @return A new list containing athletes who meet the criteria.
 */
PtList filterAthletesPerParticipation(PtList athletes, int participations);

/**
 * @brief Filters athletes who first participated in a specific year.
 * @param athletes The list of athletes to filter.
 * @param year The year to filter by.
 * @return A new list containing athletes who first participated in the specified year.
 */
PtList filterAthletesPerFirstYear(PtList athletes, int year);

/**
 * @brief Displays detailed information for a specific athlete based on their ID.
 * @param athletes The list of all athletes.
 * @param medals The list of all medals.
 * @param athleteID The ID of the athlete to display information for.
 */
void showAthleteInfo(PtList athletes, PtListMedal medals, char *athleteID);

/**
 * @brief Retrieves all medals won by a specific athlete.
 * @param medals The list of all medals.
 * @param athleteID The ID of the athlete to search for.
 * @return A new list containing all medals won by the specified athlete.
 */
PtListMedal getMedalsPerAthlete(PtListMedal medals, char *athleteID);

/**
 * @brief Searches for an athlete by ID.
 * @param athletes The list of athletes.
 * @param athleteID The ID of the athlete to find.
 * @param athlete Pointer to an Athlete structure to store the found athlete.
 * @return True if the athlete is found, false otherwise.
 */
bool getAthleteById(PtList athletes, char *athleteID, Athlete* athlete);

/**
 * @brief Filters medals between specified start and end years.
 * @param startYear The starting year of the period.
 * @param endYear The ending year of the period.
 * @param medals The list of medals to filter.
 * @param hosts Mapping of game identifiers to hosts.
 * @return A list of medals that fall within the specified years.
 */
PtListMedal filterMedalsPerDate(int startYear, int endYear, PtListMedal medals, PtMap hosts);

/**
 * @brief Filters medals by game type (e.g., Summer or Winter Olympics).
 * @param gameType The type of games to filter (e.g., "Summer").
 * @param medals The list of medals to filter.
 * @param hosts Mapping of game identifiers to hosts, which include the season.
 * @return A list of medals from the specified type of games.
 */
PtListMedal filterMedalsPerGameType(char *gameType, PtListMedal medals, PtMap hosts);

/**
 * @brief Displays statistics and information for the top N athletes.
 * @param n Number of top athletes to display.
 * @param startYear Start year of the period to consider.
 * @param endYear End year of the period to consider.
 * @param gameType Type of games (e.g., "Summer").
 * @param athletes List of all athletes.
 * @param medals List of all medals.
 * @param hosts Mapping of game identifiers to hosts.
 */
void showTopN(int n, int startYear, int endYear, char *gameType, PtList athletes, PtListMedal medals, PtMap hosts);

/**
 * @brief Retrieves the disciplines of a given game from a set of medals.
 * @param medals The list of medals.
 * @param gameSlug The identifier for the game.
 * @return A set of disciplines associated with the specified game.
 */
PtAdtSet getGameSlugDisciplines(PtListMedal medals, char* gameSlug);

/**
 * @brief Displays statistics for a set of disciplines.
 * @param disciplines The set of disciplines to analyze.
 * @param medals The list of medals to consider for the analysis.
 */
void showDisciplineStatistics(PtAdtSet disciplines, PtListMedal medals);

/**
 * @brief Determines the country with the most medals in a particular discipline.
 * @param medals List of all medals.
 * @param discipline The discipline to analyze.
 * @return String containing the name of the country with the most medals in the specified discipline.
 */
char* countryMostMedalsInDiscipline(PtListMedal medals, char* discipline);

/**
 * @brief Calculates the proportion of female participants in a specific discipline.
 * @param medals List of all medals.
 * @param discipline The discipline to analyze.
 * @param womenCount Pointer to store the count of women.
 * @param athleteCount Pointer to store the total count of athletes.
 */
void getDisciplineWomenProportion(PtListMedal medals, char* discipline, int *womenCount, int *athleteCount);
