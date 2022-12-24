#include "BattleByCategory.h"

#include "LinkedList.h"
#include "MaxHeap.h"

typedef struct Node_t* Node;
char** slice_str(char* str, char* del);
// creating LinkedList with each Node been the MaxHeap
// keep track of the amount of the current categories at the moment.
//
struct battle_s{
	LinkedList categories;
	int numberOfCategories;
	getCategoryFunction getCategory;
	getAttackFunction getAttack;
	printFunction printElement;

};

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,
		equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,
		getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement){

		Battle battle = (Battle) malloc(sizeof(struct battle_s));
		if(battle == NULL)
			return NULL;



		/* NOTES : What doe's equalElement good for? for deleting from heap based on search?
		 * should i use getAttack to be my equalfunction for maxheap?
		 * maximum attack at the top?.
		 */
		LinkedList ll_categories = (LinkedList) createLinkedList(*returnsameHeap, *destroyHeap, *printHeap, *equalHeapNames);
		if(ll_categories == NULL)
			return NULL;


		battle->categories = ll_categories;
		battle->getAttack =  getAttack;
		battle->getCategory = getCategory;
		battle->numberOfCategories = 0;
		battle->printElement = printElement;


		char* categories_alloc = (char*) malloc(sizeof(char)*(strlen(categories)+1));
		if(categories_alloc == NULL)
			return NULL;


		strcpy(categories_alloc, categories);
		char** categories_slice = slice_str(categories_alloc, ",");


		for(int i = 0; i < numberOfCategories; i++){
			MaxHeap catagory = createHeap(freeElement, copyElement, printElement,
								capacity, categories_slice[i], equalElement);
		if(catagory == NULL)
			return NULL;

			appendNode(battle->categories, catagory);
			battle->numberOfCategories++;
		}
		free(categories_alloc);
		free(categories_slice);

		return battle;
}

status destroyBattleByCategory(Battle b){
	if(b == NULL) return failure;
	destroyList(b->categories);
	free(b);
	b = NULL;
	return success;
}

// Inserting new element to our currect maxheap saved in category linkedlist
// Yet to understand if failed to allocate memory for node inside
// the maxheap may cause problams. mmaybe to return the maxheap status all togther?
status insertObject(Battle b, element elem){
	char* category = b->getCategory(elem);
	MaxHeap maxheap = (MaxHeap) searchByKeyInList(b->categories, category);
	if(maxheap == NULL) return failure;
	if(insertToHeap(maxheap, elem) == MaxHeap_FULL){
		printf("%s at full capacity.\n", category);
		return failure;
	}
	return success;
}

void displayObjectsByCategories(Battle b){
	displayList(b->categories);
}

element removeMaxByCategory(Battle b,char* category){
	MaxHeap maxheap = (MaxHeap) searchByKeyInList(b->categories, category);
	element ele = PopMaxHeap(maxheap);
	return ele;
}

int getNumberOfObjectsInCategory(Battle b,char* category){
	MaxHeap maxheap = (MaxHeap) searchByKeyInList(b->categories, category);
	if(maxheap == NULL) return 0;
	return getHeapCurrentSize(maxheap);
}

element fight(Battle b,element elem){
	int attack_first = 0;
	int attack_second = 0;
	int heighest_attack = -100000;
	int current_attack = 0 ;
	MaxHeap cata = NULL;
	element opponent = NULL;
	element temp = NULL;
	int index = 0;
	for(int i = 0; i < b->numberOfCategories; i++){
		cata = (MaxHeap) getElementAt(b->categories, i);
		if(getHeapCurrentSize(cata) > 0){
			temp = TopMaxHeap(cata);
			current_attack = b->getAttack(temp , elem, &attack_first, &attack_second);
			if( heighest_attack  < current_attack){
				heighest_attack = current_attack;
				index = i;
				opponent = temp;
			}
		}
	}
	if(opponent == NULL){
		printf("There are no Pokemons to fight against you.\n");
		return elem;
	}


	int fight = b->getAttack(opponent, elem, &attack_first, &attack_second);
	printf("The final battle between:\n");
		b->printElement(elem);
		printf("In this battle his attack is :%d\n\n" ,attack_second);
		printf("against ");
		b->printElement(opponent);
		printf("In this battle his attack is :%d\n\n" ,attack_first);


	if(fight > 0){
		printf("THE WINNER IS:\n");
		b->printElement(opponent);
		return opponent;
	}
	else if(fight < 0){
		printf("THE WINNER IS:\n");
		b->printElement(elem);
		return elem;
	}
	else{
		printf("IT IS A DRAW.\n");
		if(index-1 < 0) return NULL;
		cata = (MaxHeap) getElementAt(b->categories, index-1);
		if(cata == NULL) return NULL;
		opponent = TopMaxHeap(cata);
		if(opponent == NULL) return NULL;

		fight = b->getAttack(opponent, elem, &attack_first, &attack_second);
		printf("The final battle between:\n");
		b->printElement(elem);
		printf("In this battle his attack is :%d\n\n" ,attack_second);
		printf("against ");
		b->printElement(opponent);
		printf("In this battle his attack is :%d\n\n" ,attack_first);

		if(fight > 0){
			printf("THE WINNER IS:\n");
			b->printElement(opponent);
			return opponent;
		}
		else if(fight < 0){
			printf("THE WINNER IS:\n");
			b->printElement(elem);
			return elem;
			}
		else
			return opponent;
	}
	return NULL;

}



