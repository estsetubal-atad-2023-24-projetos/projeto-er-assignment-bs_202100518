/**
 * @file mapElem.c
 * 
 * @brief Provides utility functions for map element operations.
 * 
 * This file includes essential functions for comparing keys in map data structures,
 * facilitating key-based operations such as insertions, deletions, and searches.
 * 
 * @author Raul Rohjans
 */
#include "mapElem.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Compares two map keys for equality.
 * 
 * This function compares two map keys (strings in this case) and determines
 * whether they are identical.
 * 
 * @param key1 The first key to compare.
 * @param key2 The second key to compare.
 * @return True if the keys are equal, False otherwise.
 */
bool mapKeyEquals(MapKey key1, MapKey key2) {
    int res = strcmp(key1, key2);

    return res == 0;
}