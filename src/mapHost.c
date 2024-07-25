/**
 * @file mapHost.c
 * 
 * @brief Provides an implementation of the ADT Map with an array list
 * as the underlying data structure for storing hosts.
 * 
 * This file contains functions to manage a map of hosts using a dynamic array.
 * It includes functionalities such as creating, destroying, adding, removing,
 * and accessing hosts in the map based on a key.
 * 
 * @author Raul Rohjans
 * @bug No known bugs.
 */
#include "map.h"
#include "host.h"
#include "mapElem.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_CAPACITY 20

typedef struct keyValue {
	MapKey key;
	MapValue value;
} KeyValue;

typedef struct mapImpl {
	KeyValue *elements;
	int capacity;
	int size;
} MapImpl;

/**
 * @brief Finds the index of a specific key in the map.
 * 
 * Keys are compared using the mapKeyEquals function.
 * 
 * @param map Pointer to the map.
 * @param key Key to find.
 * @return Index of 'elements' containing 'key', or -1 if no index contains 'key'.
 */
static int findIndexOfKey(PtMap map, MapKey key) {
	if (map == NULL) return -1;

	for (int i = 0; i < map->size; i++)
		if (mapKeyEquals(map->elements[i].key, key)) return i;

	return -1;
}

/**
 * @brief Ensures that the map has sufficient capacity to store additional key-value pairs.
 * 
 * @param map Pointer to the map.
 * @return True if the capacity is sufficient or successfully expanded, False on memory allocation failure.
 */
static bool ensureCapacity(PtMap map) {
	if (map->size == map->capacity) {
		int newCapacity = map->capacity * 2;
		KeyValue* newArray = (KeyValue*) realloc( map->elements, 
									newCapacity * sizeof(KeyValue) );
		
		if(newArray == NULL) return false;

		map->elements = newArray;
		map->capacity = newCapacity;
	}
	
	return true;
}

/**
 * @brief Creates a new map.
 * 
 * @return Pointer to the created map, or NULL if memory allocation fails.
 */
PtMap mapCreate() {
	PtMap newMap = (PtMap)malloc(sizeof(MapImpl));
	if (newMap == NULL) return NULL;

	newMap->elements = (KeyValue*)calloc(INITIAL_CAPACITY, sizeof(KeyValue));
	if (newMap->elements == NULL) {
		free(newMap);
		return NULL;
	}

	newMap->size = 0;
	newMap->capacity = INITIAL_CAPACITY;

	return newMap;
}

/**
 * @brief Destroys the map and frees allocated memory.
 * 
 * @param ptMap Double pointer to the map.
 * @return MAP_OK if successful, MAP_NULL if the map pointer is NULL.
 */
int mapDestroy(PtMap *ptMap) {
	PtMap map = *ptMap;

	if (map == NULL) return MAP_NULL;

	if(map->elements != NULL) free(map->elements);
	free(map);

	*ptMap = NULL;

	return MAP_OK;
}

/**
 * @brief Adds a key-value pair to the map.
 * 
 * If the key already exists, the value is updated.
 * 
 * @param map Pointer to the map.
 * @param key Key of the element to add.
 * @param value Value of the element to add.
 * @return MAP_OK if successful, MAP_NULL if the map is NULL, or MAP_NO_MEMORY if memory allocation fails.
 */
int mapPut(PtMap map, MapKey key, MapValue value) {
	if (map == NULL) return MAP_NULL;

	int index = findIndexOfKey(map, key);
	if (index != -1) {
		map->elements[index].value = value;
		return MAP_OK;
	}

	if (!ensureCapacity(map)) return MAP_NO_MEMORY;

	map->elements[map->size].key = key;
	map->elements[map->size].value = value;
	map->size++;

	return MAP_OK;
}

/**
 * @brief Removes a key-value pair from the map by key.
 * 
 * @param map Pointer to the map.
 * @param key Key of the element to remove.
 * @param ptValue Pointer to store the value of the removed element.
 * @return MAP_OK if successful, MAP_NULL if the map is NULL, MAP_EMPTY if the map is empty, or MAP_UNKNOWN_KEY if the key does not exist.
 */
int mapRemove(PtMap map, MapKey key, MapValue *ptValue) {
	if (map == NULL) return MAP_NULL;
	if (map->size == 0) return MAP_EMPTY;

	int index = findIndexOfKey(map, key);
	if (index == -1) return MAP_UNKNOWN_KEY;

	*ptValue = map->elements[index].value;

	map->elements[index] = map->elements[map->size - 1];
	map->size--;
	
	return MAP_OK;
}

/**
 * @brief Checks if the map contains a specific key.
 * 
 * @param map Pointer to the map.
 * @param key Key to check for.
 * @return True if the key exists, False otherwise.
 */
bool mapContains(PtMap map, MapKey key) {
	if (map == NULL) return false;

	return findIndexOfKey(map, key) != -1;
}

/**
 * @brief Retrieves the value associated with a specific key.
 * 
 * @param map Pointer to the map.
 * @param key Key to retrieve the value for.
 * @param ptValue Pointer to store the value.
 * @return MAP_OK if successful, MAP_NULL if the map is NULL, MAP_EMPTY if the map is empty, or MAP_UNKNOWN_KEY if the key does not exist.
 */
int mapGet(PtMap map, MapKey key, MapValue *ptValue) {
	if (map == NULL) return MAP_NULL;
	if (map->size == 0) return MAP_EMPTY;

	int index = findIndexOfKey(map, key);
	if (index == -1) return MAP_UNKNOWN_KEY;

	*ptValue = map->elements[index].value;
	
	return MAP_OK;
}

/**
 * @brief Returns an array of all keys in the map.
 * 
 * @param map Pointer to the map.
 * @return Array of keys, or NULL if the map is empty or NULL.
 */
MapKey* mapKeys(PtMap map) {
	if (map == NULL || map->size == 0) return NULL;

	MapKey *keys = (MapKey*)malloc(map->size * sizeof(MapKey));
	if (keys == NULL) return NULL;

	for (int i = 0; i < map->size; i++)
		keys[i] = map->elements[i].key;	

	return keys;
}

/**
 * @brief Returns an array of all values in the map.
 * 
 * @param map Pointer to the map.
 * @return Array of values, or NULL if the map is empty or NULL.
 */
MapValue* mapValues(PtMap map) {
	if (map == NULL || map->size == 0) return NULL;

	MapValue *values = (MapValue*)malloc(map->size * sizeof(MapValue));
	if (values == NULL) return NULL;

	for (int i = 0; i < map->size; i++)
		values[i] = map->elements[i].value;

	return values;
}

/**
 * @brief Returns the number of key-value pairs in the map.
 * 
 * @param map Pointer to the map.
 * @param ptSize Pointer to store the number of key-value pairs.
 * @return MAP_OK if successful, MAP_NULL if the map is NULL.
 */
int mapSize(PtMap map, int *ptSize) {
	if (map == NULL) return MAP_NULL;

	*ptSize = map->size;

	return MAP_OK;
}

/**
 * @brief Checks if the map is empty.
 * 
 * @param map Pointer to the map.
 * @return True if the map is empty, False otherwise.
 */
bool mapIsEmpty(PtMap map) {
	if (map == NULL) return true;
	return (map->size == 0);
}

/**
 * @brief Clears all key-value pairs from the map.
 * 
 * @param map Pointer to the map.
 * @return MAP_OK if successful, MAP_NULL if the map is NULL.
 */
int mapClear(PtMap map) {
	if (map == NULL) return MAP_NULL;
	
	map->size = 0;

	return MAP_OK;
}

/**
 * @brief Prints all key-value pairs in the map.
 * 
 * @param map Pointer to the map.
 */
void mapPrint(PtMap map) {
	if (map == NULL)
		printf("(MAP NULL)\n");	
	else if (mapIsEmpty(map))
		printf("(MAP EMPTY)\n");
	else {
		printf("Key -> Value\n");
		printf("------------\n");

		for (int i = 0; i < map->size; i++) {
			printf("%s -> \n", map->elements[i].key);

            printHost(map->elements[i].value);
			printf("\n\n");
		}
	}
}
