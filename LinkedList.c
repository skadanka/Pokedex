/*
 ============================================================================
 Name        : PokemonWars.c
 Author      : Eden
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "LinkedList.h"


struct LinkedList_t{
	/* The LinkedList implemented as chain of Node
	 	 	 Starting at head and end at tail? maybe never ends
	 	 	 int size display the current amount of nodes in our List.
	 */
	Node head;
	Node tail;
	int size;
	copyFunction copyfunction;
	freeFunction freefunction;
	printFunction printfunction;
	equalFunction equal;
};

struct Node_t{
	/* Each node will be recgonzied by the generic (void*) key
	 	 next is the next Node in the list
	 	 perv is the previous Node in the list
	 	 Element the generic data type stored in our LinekdList
	 */
	Node next;
	Node perv;
	element ele;
};

/* from the searchByKeyInList, need to understand what the key mapping function, key type should be*/
LinkedList createLinkedList(copyFunction copyfunction, freeFunction freefunction,
		printFunction printfunction, equalFunction equal){

	LinkedList linkedlist = (LinkedList) malloc(sizeof(struct LinkedList_t));
	if(linkedlist == NULL) return NULL;

	Node node = (Node) malloc(sizeof(struct Node_t));
	if(node == NULL) return NULL;

	/* Init the head&tail Node to be NULL, will stay Null till the end of the program
	 	 element,next,perv,key null, there is nothing to init here only the start of the list
	 */
	node->next = NULL;
	node->perv = NULL;
	node->ele = NULL;

	/* init the LinkedList size to be 0
	 	 set the node to be head&tail
	 	 set the functions needed for our LinkedList
	 	 copyfunction: copy the generic element passed to our ADT
	 	 freefunction: free all allocated memory of the element, based on elements fields,
	 	 printfunction: printing the elements fields based on how the element implemented
	 	 asssigenkey: IDEA*** To map each element to key, will be used later for delete.
	 */
	linkedlist->size = 0;
	linkedlist->tail = node;
	linkedlist->head = linkedlist->tail;
	linkedlist->copyfunction = copyfunction;
	linkedlist->freefunction = freefunction;
	linkedlist->printfunction = printfunction;
	linkedlist->equal = equal;

	return linkedlist;
}


status appendNode(LinkedList linkedlist, element ele){
	/* with each passed element to append we check for nullity
	 	 return LinkedList_Failure;
	 	 creating copy of the element for protection reasons
	 	 adding to the end of list: updating tail->next, tail to be the new node
	 	 assign for each node->key with function given assignkey(element);
	 */
	if(ele == NULL || linkedlist == NULL) return failure;

	element newEle = linkedlist->copyfunction(ele);
	if(newEle == NULL) return failure;

	Node node = (Node) malloc(sizeof(struct Node_t));
	if(node == NULL) return failure;

	node->ele = newEle;
	node->next = NULL;
	node->perv = linkedlist->tail;
	linkedlist->tail->next = node;

	linkedlist->tail = node;
	if(linkedlist->head->next == NULL){
		linkedlist->head->next = node;
		node->perv = linkedlist->head;
	}
	linkedlist->size++;
	return success;
}

status displayList(LinkedList linkedlist){
	if(NULL == linkedlist || linkedlist->head->next == NULL){
		printf("LinkedList is Empty\n");
		return failure;
	}

	Node Iter = linkedlist->head->next;
	while(Iter != NULL){
		if(linkedlist->printfunction(Iter->ele) == failure)
			return failure;
		Iter = Iter->next;
	}
	return success;
}

// comparing each node->key in the list till reaching the end of list,
//	return null if failed, return the node if
element searchByKeyInList(LinkedList linkedlist, void* key){
	Node Iter = linkedlist->head->next;
	while(Iter != NULL){
		if(linkedlist->equal(Iter->ele, key) == 0)
			return Iter->ele;
		Iter = Iter->next;
	}
	return NULL;
}

/* search for the node based on the assignkey function using the searchByKeyInList method
 	 if return is NULL then failed to delete non-existing element
 	 else delete and decrease the size of the linked list by 1.
 */
status deleteNode(LinkedList linkedlist, element ele){
	if(ele == NULL) return failure;
	Node Iter = linkedlist->head;
	Node temp = NULL;
	for(;Iter->next != NULL && Iter->next->ele != ele; Iter=Iter->next);
	if(Iter->next == NULL) return failure;
	temp = Iter->next;
	Iter->next = temp->next;
	temp->next->perv = Iter;
	linkedlist->size--;
	linkedlist->freefunction(temp->ele);
	free(temp);
	return success;
}

element getElementAt(LinkedList linkedlist, int index){
	if(index < 0 || index > linkedlist->size) return NULL;
	Node result = linkedlist->head->next;
	for(int i = 0; i != index && i < linkedlist->size ; result = result->next, i++);
	return result->ele;
}
/* delete from the head, deleting head->next && head->next head->next->next,
 	 Iter = head till the end of the program when head->next = NULL, we done, free(head), free(LinkedList)*/
status destroyList(LinkedList linkedlist){
	Node temp = NULL;
	Node head = linkedlist->head;
	for(temp=head->next;head->next !=NULL; temp = head->next){
		head->next = temp->next;
		if(temp->next != NULL)
			temp->next->perv = head;
		linkedlist->freefunction(temp->ele);
		free(temp);
	}
	free(linkedlist->head);
	free(linkedlist);
	linkedlist = NULL;
	return success;

}

