#pragma once

#include "list.h"
#include "listMedal.h"
#include "map.h"
#include "adtSet.h"

void paginate(PtList athletes);

void orderAthletesAlphabetic(PtList *athletes);

PtList listAthleteShallowCopy(PtList athletes);

PtList filterAthletesPerParticipation(PtList athletes, int participations);

PtList filterAthletesPerFirstYear(PtList athletes, int year);

void showAthleteInfo(PtList athletes, PtListMedal medals, char *athleteID);

PtListMedal getMedalsPerAthlete(PtListMedal medals, char *athleteID);

bool getAthleteById(PtList athletes, char *athleteID, Athlete* athlete);

PtListMedal filterMedalsPerDate(int startYear, int endYear, PtListMedal medals, PtMap hosts);

PtListMedal filterMedalsPerGameType(char *gameType, PtListMedal medals, PtMap hosts);

void showTopN(int n, int startYear, int endYear, char *gameType, PtList athletes, PtListMedal medals, PtMap hosts);

PtAdtSet getGameSlugDisciplines(PtListMedal medals, char* gameSlug);

void showDisciplineStatistics(PtAdtSet disciplines, PtListMedal medals);

char* countryMostMedalsInDiscipline(PtListMedal medals, char* discipline);

void getDisciplineWomenProportion(PtListMedal medals, char* discipline, int *womenCount, int *athleteCount);
