/**
 * @file listAthlete.c
 * 
 * @brief Provides an implementation of the ADT List with an array list
 * as the underlying data structure.
 * 
 * @author Raul Rohajns
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

/**
 * @brief Ensures the capacity of the list to store more elements.
 * @param list Pointer to the list.
 * @return True if capacity is sufficient or successfully expanded, False on memory allocation failure.
 */
static bool ensureCapacity(PtList list) {
    if (list->size < list->capacity) return true;
    
    int newCapacity = list->capacity * 2;

    ListElem *newElements = (ListElem*) realloc(list->elements, newCapacity * sizeof(ListElem));
    
    if (newElements == NULL) return false;

    list->capacity = newCapacity;
    list->elements = newElements;
    
    return true;
}

/**
 * @brief Creates a new list for storing athletes.
 * @return Pointer to the created list or NULL if memory allocation fails.
 */
PtList listCreate() {
	PtList list = (PtList)malloc(sizeof(ListImpl));

    if (list == NULL) return NULL;

    list->elements = malloc(INITIAL_CAPACITY * sizeof(ListElem));
    
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
int listDestroy(PtList *ptList) {
	if (ptList == NULL || *ptList == NULL) return LIST_NULL;

    ListImpl *list = (ListImpl *)ptList;

    free(list->elements);

    // This throws an exception
	//free(list);

    *ptList = NULL;

    return LIST_OK;
}

/**
 * @brief Adds an element to the list at the specified rank.
 * @param list Pointer to the list.
 * @param rank The position at which to insert the new element.
 * @param elem The element to be inserted.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL, LIST_INVALID_RANK if rank is out of bounds, or LIST_NO_MEMORY if memory allocation fails.
 */
int listAdd(PtList list, int rank, ListElem elem) {
	if (list == NULL) return LIST_NULL;
    if (rank < 0 || rank > ((ListImpl *)list)->size) return LIST_INVALID_RANK;
    if (!ensureCapacity(list)) return LIST_NO_MEMORY;

    // Make space for the new element
    for (int i = list->size; i > rank; i--)
        list->elements[i] = list->elements[i - 1];
    
    list->elements[rank] = elem;
    list->size++;

    return LIST_OK;
}

/**
 * @brief Removes an element from the list at the specified rank.
 * @param list Pointer to the list.
 * @param rank The position from which to remove the element.
 * @param ptElem Pointer to store the removed element.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL, LIST_INVALID_RANK if rank is out of bounds.
 */
int listRemove(PtList list, int rank, ListElem *ptElem) {
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
 * @brief Retrieves an element from the list at the specified rank.
 * @param list Pointer to the list.
 * @param rank The position from which to retrieve the element.
 * @param ptElem Pointer to store the retrieved element.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL, LIST_INVALID_RANK if rank is out of bounds.
 */
int listGet(PtList list, int rank, ListElem *ptElem) {
	if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    if(ptElem == NULL) ptElem = (ListElem*) malloc(sizeof(ListElem));
    
    *ptElem = lst->elements[rank];

    return LIST_OK;
}

/**
 * @brief Replaces an element in the list at the specified rank.
 * @param list Pointer to the list.
 * @param rank The position at which to replace the element.
 * @param elem The new element to be placed.
 * @param ptOldElem Pointer to store the old element being replaced.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL, LIST_INVALID_RANK if rank is out of bounds.
 */
int listSet(PtList list, int rank, ListElem elem, ListElem *ptOldElem) {
	if (list == NULL) return LIST_NULL;

    ListImpl *lst = (ListImpl *)list;
    if (rank < 0 || rank >= lst->size) return LIST_INVALID_RANK;

    // This may be null if we don't want to keep the old element
    if(ptOldElem != NULL) *ptOldElem = lst->elements[rank];

    lst->elements[rank] = elem;

    return LIST_OK;
}

/**
 * @brief Returns the number of elements in the list.
 * @param list Pointer to the list.
 * @param ptSize Pointer to store the number of elements.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL.
 */
int listSize(PtList list, int *ptSize) {
	if (list == NULL) return LIST_NULL;

    *ptSize = ((ListImpl *)list)->size;
    return LIST_OK;
}

/**
 * @brief Checks if the list is empty.
 * @param list Pointer to the list.
 * @return True if the list is empty, False otherwise.
 */
bool listIsEmpty(PtList list) {
	if (list == NULL) return 1;

	ListImpl *lst = (ListImpl *)list;

	return (lst->size != 0);
}

/**
 * @brief Clears the list of all elements.
 * @param list Pointer to the list.
 * @return LIST_OK if successful, LIST_NULL if the list is NULL.
 */
int listClear(PtList list) {
	if (list == NULL) return LIST_NULL;
    ListImpl *lst = (ListImpl *)list;

    free(lst->elements);

    lst->size = 0;
	
    return LIST_OK;
}

/**
 * @brief Prints all elements in the list.
 * @param list Pointer to the list.
 */
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