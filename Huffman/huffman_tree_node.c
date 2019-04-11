#include <stdio.h> 
#include <stdlib.h>
#include "huffman_tree_node.h"

HuffmanTreeNode *merge(HuffmanTreeNode *node1, HuffmanTreeNode *node2) {
	HuffmanTreeNode *newNode = malloc(sizeof(HuffmanTreeNode));
	
	newNode->left = node1;
	newNode->right = node2;

	newNode->weight = (node1->weight + node2->weight);
	
	for(int i=0; i!=17; i++) {
		newNode->value[i] = node1->value[i] | node2->value[i];
	}
	
	return newNode;
}

HuffmanTreeNode *pop(PriorityQueueNode **passedQueue) {
	HuffmanTreeNode *oldQueueValue = (*passedQueue)->value;
	PriorityQueueNode *oldQueueHead = *passedQueue;
	*passedQueue = (*passedQueue)->next;
	free(oldQueueHead);
	oldQueueHead = NULL;
	return oldQueueValue;		
}

HuffmanTreeNode *buildLeaf(unsigned char asciiValue, int occurences) {

	HuffmanTreeNode *newNode = malloc(sizeof(HuffmanTreeNode));
	
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->weight = occurences;
	
	newNode->value[(asciiValue / 8)] = 1 << (asciiValue % 8);
	
	return newNode;	
}

void add(PriorityQueueNode **passedQueue, HuffmanTreeNode *htNode){
	
	PriorityQueueNode *pq = malloc(sizeof(PriorityQueueNode));
	pq->value = htNode;
	pq->next = NULL;
	
	PriorityQueueNode *start = (*passedQueue);
	
	if((*passedQueue) == NULL) {
		*passedQueue = pq;
	}else if((*passedQueue)->value->weight >= htNode->weight) {
		pq->next = *passedQueue;
		(*passedQueue) = pq;
	} else {
		
		while((start->next != NULL) && (start->next->value->weight) < (htNode->weight)) {
			start = start->next;
		}

		pq->next = start->next;
		start->next = pq;	
	}
	
}