#include "MaxHeap.h"

typedef struct Node_t* Node;
void exchange(int i, int j, MaxHeap maxheap);
int parent(int index);
void Increase_key(int start, MaxHeap maxheap);
Node Extract(int index, MaxHeap maxheap);
void down_Heapify(int i, MaxHeap maxheap);
void up_Heapify(int i, MaxHeap maxheap);
int Left(int i);
int Right(int i);


struct MaxHeap_t{
	int size;
	int maxSize;
	Node *heap;
	copyFunction copyfunction;
	freeFunction freefunction;
	printFunction printfunction;
	equalFunction  equalfunction;
	char* id;
};

struct Node_t{
	element ele;
	int index;
};

MaxHeap createHeap(freeFunction freefunction, copyFunction copyfunction, printFunction printfunction,
					int maxSize, char* id, equalFunction equalfunction){
	MaxHeap maxheap = (MaxHeap) malloc(sizeof(struct MaxHeap_t));
	if(maxheap == NULL)
		return NULL;


	maxheap->maxSize = maxSize;
	maxheap->heap = (Node*) malloc(sizeof(Node)*(maxSize+1));
	for(int i = 0; i < maxSize; maxheap->heap[i]=NULL, i++);
	maxheap->id = (char*) malloc(sizeof(char)*(strlen(id)+1));
	if(maxheap->id == NULL) return NULL;
	strcpy(maxheap->id, id);
	maxheap->size = 0;

	maxheap->copyfunction = copyfunction;
	maxheap->printfunction = printfunction;
	maxheap->equalfunction = equalfunction;
	maxheap->freefunction = freefunction;


	return maxheap;
}


MaxHeapResult insertToHeap(MaxHeap maxheap, element ele){
	if(maxheap == NULL || ele == NULL) return MaxHeap_Failure;

	if(maxheap->maxSize == maxheap->size) return MaxHeap_FULL;

	Node node = (Node) malloc(sizeof(struct Node_t));
	if(node == NULL) return MaxHeap_Failure;

	element newEle = maxheap->copyfunction(ele);
	if(newEle == NULL) return MaxHeap_Failure;

	maxheap->size++;
	node->ele = newEle;
	node->index = maxheap->size;

	maxheap->heap[maxheap->size] = node;

	Increase_key(maxheap->size, maxheap);
	return MaxHeap_Success;
}


void Increase_key(int start, MaxHeap maxheap){
	int index = start;
	while(index> 1 && maxheap->equalfunction(maxheap->heap[index]->ele, maxheap->heap[parent(index)]->ele)==1){
		exchange(index, parent(index), maxheap);
		index = parent(index);
	}
}


status printHeap(element elem){
	if(elem == NULL) return failure;
	MaxHeap maxheap = (MaxHeap) elem;
	printf("%s:\n", maxheap->id);
	if(maxheap->size == 0 ){
		printf("No elements.\n\n");
		return success;
	}
	MaxHeap maxheap_copy  = createHeap(maxheap->freefunction,
			maxheap->copyfunction,
			maxheap->printfunction, maxheap->maxSize,
			maxheap->id,
			maxheap->equalfunction);
	if(maxheap_copy == NULL){
		return failure;
	}

	int size = maxheap->size;
	maxheap_copy->size = size;
	for(int i = 0; i <= size;i++)
		maxheap_copy->heap[i] = maxheap->heap[i];

	for(int i = 0; i < size; i++){
		printf("%d. ", i+1);
		if(maxheap_copy->printfunction(Extract(1, maxheap_copy)->ele) == failure)
			return failure;
	}
	free(maxheap_copy->heap);
	free(maxheap_copy->id);
	free(maxheap_copy);
	return success;
}

void exchange(int i, int j, MaxHeap maxheap) {
		Node tmp = maxheap->heap[i];
		maxheap->heap[i] = maxheap->heap[j];
		maxheap->heap[j] = tmp;
		maxheap->heap[i]->index = i;
		maxheap->heap[j]->index = j;
}

int parent(int index){
	return index/2;
}

Node Extract(int index, MaxHeap maxheap){
	if(index > maxheap->size || index ==0)
		return NULL;
	Node node = maxheap->heap[index];
	maxheap->heap[index] = maxheap->heap[maxheap->size];
	maxheap->heap[maxheap->size] = NULL;
	maxheap->size--;
	down_Heapify(index, maxheap);
	up_Heapify(index, maxheap);
	return node;
}

void down_Heapify(int i, MaxHeap maxheap) {
		int r = Right(i);
		int l = Left(i);
		int largest = i;
		if(l <= maxheap->size && maxheap->equalfunction(maxheap->heap[l]->ele, maxheap->heap[largest]->ele) == 1)
			largest = l;
		if(r <= maxheap->size && maxheap->equalfunction(maxheap->heap[r]->ele, maxheap->heap[largest]->ele) == 1)
			largest = r;

		if(largest != i) {
			exchange(i,  largest, maxheap);
			down_Heapify(largest, maxheap);
		}
	}

void up_Heapify(int i, MaxHeap maxheap) {
			if(parent(i) > 1)
				if(maxheap->equalfunction(maxheap->heap[parent(i)]->ele, maxheap->heap[i]->ele)!=0) {
					exchange(parent(i), i, maxheap);
					up_Heapify(parent(i), maxheap);}
			return;
		}

element PopMaxHeap(MaxHeap maxheap){
	if(maxheap->size == 0 ) return NULL;
	Node node = Extract(1, maxheap);
	if(node == NULL)
		return NULL;
	element ele = node->ele;
	free(node);
	return ele;
}

element TopMaxHeap(MaxHeap maxheap){
	if(maxheap->size < 1)
		return NULL;

	return maxheap->heap[1]->ele;
}

char* getHeapid(MaxHeap maxheap){
	if(maxheap == NULL) return NULL;
	return maxheap->id;
}

int getHeapCurrentSize(MaxHeap maxheap){
	if(maxheap == NULL) return 0;
	return maxheap->size;
}

int Left(int i ){
	return i*2;
}

int Right(int i){
	return 2*i+1;
}

status destroyHeap(element elem){
	if(elem == NULL) return failure;
	MaxHeap maxheap = (MaxHeap) elem;
	Node temp = NULL;
	while((temp = (Node) PopMaxHeap(maxheap)) != NULL)
		maxheap->freefunction(temp);
	free(maxheap->id);
	free(maxheap->heap);
	free(maxheap);
	maxheap = NULL;
	return success;
}

element returnsameHeap(element ele){
	return ele;
}

int equalHeapTopMax(element ele1, element ele2){
	MaxHeap e1 = (MaxHeap) ele1;
	MaxHeap e2 = (MaxHeap) ele2;

	return e1->equalfunction(TopMaxHeap(e1), TopMaxHeap(e2));
}

int equalHeapNames(element ele1, element ele2){
	MaxHeap maxheap = (MaxHeap) ele1;
	char* name = (char*) ele2;
	return strcmp(maxheap->id, name);
}

element CopyMaxHeap(element ele){
	MaxHeap maxheap = (MaxHeap) ele;
	MaxHeap maxheap_copy  = createHeap(maxheap->freefunction,
				maxheap->copyfunction,
				maxheap->printfunction, maxheap->maxSize,
				maxheap->id,
				maxheap->equalfunction);
	if(maxheap_copy == NULL) return NULL;

	for(int i =0; i < maxheap->size; i ++){
		maxheap_copy->heap[i] = maxheap->copyfunction(maxheap->heap[i]);
		maxheap_copy->size++;
	}
	return maxheap_copy;
}
