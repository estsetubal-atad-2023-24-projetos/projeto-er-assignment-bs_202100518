#ifndef HOST_H
#define HOST_H

#define MAX_ID_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_LOCATION_LENGTH 100
#define MAX_GAME_NAME_LENGTH 50

typedef struct {
    char gameSlug[MAX_ID_LENGTH];
    char endDate[MAX_NAME_LENGTH];
    char startDate[MAX_NAME_LENGTH];
    char location[MAX_LOCATION_LENGTH];
    char gameName[MAX_GAME_NAME_LENGTH];
    char season[MAX_NAME_LENGTH];
    int year;
} Host;

Host* createHost(const char* slug, const char* endDate, const char* startDate, const char* location,
                 const char* gameName, const char* season, int year);

void printHost(Host* host);

#endif