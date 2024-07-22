#pragma once

#include "list.h"

void paginate(PtList athletes);

void orderAthletesAlphabetic(PtList *athletes);

PtList listAthleteShallowCopy(PtList athletes);

PtList filterAthletesPerParticipation(PtList athletes, int participations);

PtList filterAthletesPerFirstYear(PtList athletes, int year);
