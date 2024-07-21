/**
 * @file listAthlete.c
 * 
 * @brief Provides an implementation of the ADT List with an array list
 * as the underlying data structure.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include "list.h"
#include "athlete.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 20

typedef struct listImpl {
	ListElem *elements;
    int size;
    int capacity;
} ListImpl;


static bool ensureCapacity(PtList list) {
	ListImpl *lst = (ListImpl *)list;

    if (lst->size >= lst->capacity) {
        int newCapacity = lst->capacity * 2;

        ListElem *newElements = (ListElem*) realloc(lst->elements, newCapacity * sizeof(ListElem *));
        
        if (newElements == NULL) return false;

        lst->capacity = newCapacity;
        lst->elements = newElements;
    }

    return true;
}

PtList listCreate() {
	ListImpl *list = malloc(sizeof(ListImpl));

    if (list == NULL) return NULL;

    list->elements = malloc(INITIAL_CAPACITY * sizeof(ListElem *));
    
	if (list->elements == NULL) {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;

    return list;
}

int listDestroy(PtList *ptList) {
	if (ptList == NULL || *ptList == NULL) return LIST_NULL;

    ListImpl *list = (ListImpl *)ptList;

    // Free each element since they were dynamically allocated
    for (int i = 0; i < list->size; i++)
        free(&list->elements[i]);
	
    free(list->elements);
    free(list);

    *ptList = NULL;

    return LIST_OK;
}

int listAdd(PtList list, int rank, ListElem elem) {
	if (list == NULL) return LIST_NULL;
    if (rank < 0 || rank > ((ListImpl *)list)->size) return LIST_INVALID_RANK;
    if (!ensureCapacity(list)) return LIST_NO_MEMORY;

    ListImpl *athList = (ListImpl *)list;
    // Make space for the new element
    for (int i = athList->size; i > rank; i--)
        athList->elements[i] = athList->elements[i - 1];
    
    athList->elements[rank] = elem;
    athList->size++;

    return LIST_OK;
}

int listRemove(PtList list, int rank, ListElem *ptElem) {
	if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    *ptElem = lst->elements[rank];

    // Shift elements
    for (int i = rank; i < lst->size - 1; i++)
        lst->elements[i] = lst->elements[i + 1];
		
    lst->size--;
    return LIST_OK;
}

int listGet(PtList list, int rank, ListElem *ptElem) {
	if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    *ptElem = lst->elements[rank];

    return LIST_OK;
}

int listSet(PtList list, int rank, ListElem elem, ListElem *ptOldElem) {
	if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    *ptOldElem = lst->elements[rank];

    lst->elements[rank] = elem;

    return LIST_OK;
}

// This method is a bit stupid but I'll implement it
// since its in the mandatory list.h
int listSize(PtList list, int *ptSize) {
	if (list == NULL) return LIST_NULL;

    *ptSize = ((ListImpl *)list)->size;
    return LIST_OK;
}

bool listIsEmpty(PtList list) {
	if (list == NULL) return 1;

	ListImpl *lst = (ListImpl *)list;

	return (lst->size != 0);
}

int listClear(PtList list) {
	if (list == NULL) return LIST_NULL;
    ListImpl *lst = (ListImpl *)list;

    // Free each element
    for (int i = 0; i < lst->size; i++)
        free(&lst->elements[i]);

    lst->size = 0;
	
    return LIST_OK;
}

void listPrint(PtList list) {
	if (list == NULL) printf("(List NULL)\n");
    else if (listIsEmpty(list)) 
		printf("(List EMPTY)\n");
	else {        
        printf("Athletes List (by rank): \n");

        ListImpl *lst = (ListImpl *)list;
        for(int i = 0; i < lst->size; i++) {
            printAthlete(lst->elements[i]);
            printf("\n");
        }
    }

    printf("\n");
}