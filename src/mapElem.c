#include "mapElem.h"

#include <stdio.h>
#include <string.h>

bool mapKeyEquals(MapKey key1, MapKey key2) {
    int res = strcmp(key1, key2);

    return res == 0;
}