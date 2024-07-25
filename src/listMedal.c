/**
 * @file listMedal.c
 * 
 * @brief Provides an implementation of the ADT List with an array list
 * as the underlying data structure for storing medals.
 * 
 * This file contains functions to manage a list of medals using a dynamic array.
 * It includes functionalities such as creating, destroying, adding, removing,
 * and accessing medals in the list.
 * 
 * @author Raul Rohjans
 * @bug No known bugs.
 */

#include "listMedal.h"
#include "medal.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 20

typedef struct listImpl {
	Medal *elements;
    int size;
    int capacity;
} ListImpl;

/**
 * @brief Ensures the list has sufficient capacity to store more medals.
 * @param list Pointer to the list.
 * @return True if capacity is sufficient or successfully expanded, False on memory allocation failure.
 */
static bool ensureMedalCapacity(PtListMedal list) {
    if (list->size < list->capacity) return true;
    
    int newCapacity = list->capacity * 2;

    Medal *newElements = (Medal*) realloc(list->elements, newCapacity * sizeof(Medal));
    
    if (newElements == NULL) return false;

    list->capacity = newCapacity;
    list->elements = newElements;
    
    return true;
}

/**
 * @brief Creates a new list for storing medals.
 * @return Pointer to the created list or NULL if memory allocation fails.
 */
PtListMedal listMedalCreate() {
	PtListMedal list = (PtListMedal)malloc(sizeof(ListImpl));

    if (list == NULL) return NULL;

    list->elements = malloc(INITIAL_CAPACITY * sizeof(Medal));
    
	if (list->elements == NULL) {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;

    return list;
}

/**
 * @brief Destroys the list and frees the allocated memory.
 * @param ptList Double pointer to the list to be destroyed.
 * @return LIST_OK if successful, LIST_NULL if the list pointer is NULL.
 */
int listMedalDestroy(PtListMedal *ptList) {
	if (ptList == NULL || *ptList == NULL) return LIST_NULL;

    ListImpl *list = (ListImpl *)ptList;

    free(list->elements);
	// This throws an exception
	//free(list);

    *ptList = NULL;

    return LIST_OK;
}

/**
 * @brief Adds a medal to the list at the specified rank.
 * @param list Pointer to the list.
 * @param rank The position at which to insert the new medal.
 * @param elem The medal to be inserted.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL, LIST_INVALID_RANK if rank is out of bounds, or LIST_NO_MEMORY if memory allocation fails.
 */
int listMedalAdd(PtListMedal list, int rank, Medal elem) {
    if (list == NULL) return LIST_NULL;
    if (rank < 0 || rank > ((ListImpl *)list)->size) return LIST_INVALID_RANK;
    if (!ensureMedalCapacity(list)) return LIST_NO_MEMORY;

    ListImpl *medalList = (ListImpl *)list;
    // Make space for the new element
    for (int i = list->size; i > rank; i--)
        medalList->elements[i] = medalList->elements[i - 1];
    
    medalList->elements[rank] = elem;
    medalList->size++;

    return LIST_OK;
}

/**
 * @brief Removes a medal from the list at the specified rank.
 * @param list Pointer to the list.
 * @param rank The position from which to remove the medal.
 * @param ptElem Pointer to store the removed medal.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL, LIST_INVALID_RANK if rank is out of bounds.
 */
int listMedalRemove(PtListMedal list, int rank, Medal *ptElem) {
	if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    if(ptElem != NULL) *ptElem = lst->elements[rank];

    // Shift elements
    for (int i = rank; i < lst->size - 1; i++)
        lst->elements[i] = lst->elements[i + 1];
		
    lst->size--;
    return LIST_OK;
}

/**
 * @brief Retrieves a medal from the list at the specified rank.
 * @param list Pointer to the list.
 * @param rank The position from which to retrieve the medal.
 * @param ptElem Pointer to store the retrieved medal.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL, LIST_INVALID_RANK if rank is out of bounds.
 */
int listMedalGet(PtListMedal list, int rank, Medal *ptElem) {
    if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    if(ptElem == NULL) ptElem = (Medal*) malloc(sizeof(Medal));
    
    *ptElem = lst->elements[rank];

    return LIST_OK;
}

/**
 * @brief Replaces a medal in the list at the specified rank.
 * @param list Pointer to the list.
 * @param rank The position at which to replace the medal.
 * @param elem The new medal to be placed.
 * @param ptOldElem Pointer to store the old medal being replaced.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL, LIST_INVALID_RANK if rank is out of bounds.
 */
int listMedalSet(PtListMedal list, int rank, Medal elem, Medal *ptOldElem) {
	if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    if(ptOldElem != NULL) *ptOldElem = lst->elements[rank];

    lst->elements[rank] = elem;

    return LIST_OK;
}

/**
 * @brief Returns the number of medals in the list.
 * @param list Pointer to the list.
 * @param ptSize Pointer to store the number of medals.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL.
 */
int listMedalSize(PtListMedal list, int *ptSize) {
	if (list == NULL) return LIST_NULL;

    *ptSize = ((ListImpl *)list)->size;
    return LIST_OK;
}

/**
 * @brief Checks if the list is empty.
 * @param list Pointer to the list.
 * @return True if the list is empty, False otherwise.
 */
bool listMedalIsEmpty(PtListMedal list) {
	if (list == NULL) return 1;

	ListImpl *lst = (ListImpl *)list;

	return (lst->size != 0);
}

/**
 * @brief Clears the list of all medals.
 * @param list Pointer to the list.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL.
 */
int listMedalClear(PtListMedal list) {
	if (list == NULL) return LIST_NULL;
    ListImpl *lst = (ListImpl *)list;

    free(lst->elements);

    lst->size = 0;
	
    return LIST_OK;
}

/**
 * @brief Prints all medals in the list.
 * @param list Pointer to the list.
 */
void listMedalPrint(PtListMedal list) {
	if (list == NULL) printf("(List NULL)\n");
    else if (listMedalIsEmpty(list)) 
		printf("(List EMPTY)\n");
	else {        
        printf("Medals List (by rank): \n");

        ListImpl *lst = (ListImpl *)list;
        for(int i = 0; i < lst->size; i++) {
            printMedal((Medal)lst->elements[i]);
            printf("\n");
        }
    }

    printf("\n");
}