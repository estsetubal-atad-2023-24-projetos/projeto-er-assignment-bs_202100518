/**
 * @file listAthlete.c
 * 
 * @brief Provides an implementation of the ADT List with an array list
 * as the underlying data structure.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
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


static bool ensureMedalCapacity(PtListMedal list) {
    if (list->size < list->capacity) return true;
    
    int newCapacity = list->capacity * 2;

    Medal *newElements = (Medal*) realloc(list->elements, newCapacity * sizeof(Medal));
    
    if (newElements == NULL) return false;

    list->capacity = newCapacity;
    list->elements = newElements;
    
    return true;
}

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

int listMedalDestroy(PtListMedal *ptList) {
	if (ptList == NULL || *ptList == NULL) return LIST_NULL;

    ListImpl *list = (ListImpl *)ptList;

    free(list->elements);
	// This throws an exception
	//free(list);

    *ptList = NULL;

    return LIST_OK;
}

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

int listMedalGet(PtListMedal list, int rank, Medal *ptElem) {
    if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    if(ptElem == NULL) ptElem = (Medal*) malloc(sizeof(Medal));
    
    *ptElem = lst->elements[rank];

    return LIST_OK;
}

int listMedalSet(PtListMedal list, int rank, Medal elem, Medal *ptOldElem) {
	if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    if(ptOldElem != NULL) *ptOldElem = lst->elements[rank];

    lst->elements[rank] = elem;

    return LIST_OK;
}

int listMedalSize(PtListMedal list, int *ptSize) {
	if (list == NULL) return LIST_NULL;

    *ptSize = ((ListImpl *)list)->size;
    return LIST_OK;
}

bool listMedalIsEmpty(PtListMedal list) {
	if (list == NULL) return 1;

	ListImpl *lst = (ListImpl *)list;

	return (lst->size != 0);
}

int listMedalClear(PtListMedal list) {
	if (list == NULL) return LIST_NULL;
    ListImpl *lst = (ListImpl *)list;

    free(lst->elements);

    lst->size = 0;
	
    return LIST_OK;
}

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