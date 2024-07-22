#include "host.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Host* createHost(const char* slug, const char* endDate, const char* startDate, const char* location,
                 const char* gameName, const char* season, int year) {
    Host* newHost = (Host*) malloc(sizeof(Host));
    if (newHost) {
        strncpy(newHost->gameSlug, slug, MAX_ID_LENGTH);
        strncpy(newHost->endDate, endDate, MAX_HOST_NAME_LENGTH);
        strncpy(newHost->startDate, startDate, MAX_HOST_NAME_LENGTH);
        strncpy(newHost->location, location, MAX_LOCATION_LENGTH);
        strncpy(newHost->gameName, gameName, MAX_GAME_NAME_LENGTH);
        strncpy(newHost->season, season, MAX_HOST_NAME_LENGTH);
        newHost->year = year;
    }
    return newHost;
}

Host* createEmptyHost() {
    Host* newHost = (Host*) malloc(sizeof(Host));    
    return newHost;
}

void printHost(Host host) {
    char *hostingCity = getCharsOnlyFromString(host.gameName);
    int duration = getDateDiffInDays(host.startDate, host.endDate);

    printf("Hosting City: %s\n", hostingCity);
    printf("Year: %d\n", host.year);
    printf("Location: %s\n", host.location);
    printf("Duration (days): %d\n", duration);

    free(hostingCity);
}