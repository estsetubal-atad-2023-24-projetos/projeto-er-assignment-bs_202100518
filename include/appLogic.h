#pragma once

#include "list.h"

void paginate(PtList athletes);

void orderAthletesAlphabetic(PtList *athletes);

PtList listAthleteShallowCopy(PtList athletes);

void filterAthletesPerParticipation(PtList *athletes, int participations);

void filterAthletesPerFirstYear(PtList *athletes, int year);
