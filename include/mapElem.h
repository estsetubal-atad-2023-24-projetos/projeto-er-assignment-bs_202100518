/**
 * @file mapElem.h
 * @brief Defines the types MapKey and MapValue.
 * 
 * The MapKey is an alias to the type of keys 
 * held by an instance of the ADT Map (PtMap).
 * 
 * The MapValue is an alias to the type of values 
 * held by an instance of the ADT Map (PtMap).
 *  
 * These aliases must be changed according to the use-case.
 * 
 * @author Raul Rohjans
 * @bug No known bugs.
 */

#pragma once

#include <stdbool.h>
#include "host.h"

/**
 * @typedef MapKey
 * @brief Typedef for the key used in the map.
 * 
 * Define MapKey according to the data type required for keys in the map.
 * For this implementation, the key is a string (char pointer).
 */
typedef char *MapKey;

/**
 * @typedef MapValue
 * @brief Typedef for the value stored in the map.
 * 
 * Define MapValue according to the structure or type that represents the value in the map.
 * For this implementation, the value is a Host structure.
 */
typedef Host MapValue;

/**
 * @brief Compares two map keys for equality.
 * 
 * This function determines if two keys of type MapKey are equal. It is crucial for managing keys
 * in map data structures, particularly for operations that involve key comparison such as insertion,
 * deletion, and key retrieval.
 * 
 * @param key1 The first key to compare.
 * @param key2 The second key to compare.
 * @return True if the keys are equal, False otherwise.
 */
bool mapKeyEquals(MapKey key1, MapKey key2);