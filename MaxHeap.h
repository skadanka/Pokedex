/*
 * maxheap.h
 *
 *  Created on: Dec 8, 2021
 *      Author: ise
 */


#ifndef MAXHEAP_H_
#define MAXHEAP_H_
#include "Defs.h"

typedef struct MaxHeap_t* MaxHeap;

typedef enum{MaxHeap_Failure, MaxHeap_Success, MaxHeap_FULL, MaxHeap_Empty} MaxHeapResult;

MaxHeap createHeap(freeFunction freefunction, copyFunction copyfunction, printFunction printfunction,
					int maxSize, char* id, equalFunction equalfunction);
status destroyHeap(element elem);
MaxHeapResult insertToHeap(MaxHeap maxheap, element ele);

// The user given Print function will print the wanted elements details. print Ordered elements By key.
/* print template
 	 printf("*%s*\n", maxheap->id);
 	 printf("No elements.) if the heap is empty.
 */
status printHeap(element elem);

element returnsameHeap(element ele);
/* return null if the heap is empty.
 	 else remove the maximum value from the heap and return it.
 */
element PopMaxHeap(MaxHeap maxheap);

// return pointer to the maximum element in the heap
element TopMaxHeap(MaxHeap maxheap);
int equalHeapTopMax(element ele1, element ele2);
int equalHeapNames(element ele1, element ele2);

// return the size of the heap
int getHeapCurrentSize(MaxHeap maxheap);

char* getHeapid(MaxHeap maxheap);

#endif /* MAXHEAP_H_ */
