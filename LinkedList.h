/*
 * linkedlist.h
 *
 *  Created on: Dec 8, 2021
 *      Author: ise
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Defs.h"

typedef struct LinkedList_t *LinkedList;
typedef struct Node_t* Node;

typedef enum
	{LinkedList_FULL, LinkedList_Empty, LinkedList_Success,
	LinkedList_Failure, LinkedList_BadArgument} LinkedListResult;

// Creating List passed with the copyfunction and freefunction needed for all ADT
// ***need to understand if more arguments are needed for the creating of the lsit
LinkedList createLinkedList(copyFunction copyfunction, freeFunction freefunction,
			printFunction printfunction, equalFunction equal);
status destroyList(LinkedList linkedlist);
status appendNode(LinkedList linkedlist, element ele);
status deleteNode(LinkedList linkedlist, element ele);
status displayList(LinkedList linkedlist);
element searchByKeyInList(LinkedList linkedlist, void* key);
element getElementAt(LinkedList linkedlist, int index);
#endif /* LINKEDLIST_H_ */
