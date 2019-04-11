#ifndef HUFFMANTREENODE_H_
#define HUFFMANTREENODE_H_

typedef struct HuffmanTreeNode {
	
	int weight;
	unsigned char value[17];
	struct HuffmanTreeNode *left;
	struct HuffmanTreeNode *right;
	
} HuffmanTreeNode;

typedef struct PriorityQueueNode {

	struct PriorityQueueNode *next;
	struct HuffmanTreeNode *value;
	
} PriorityQueueNode;

HuffmanTreeNode *pop(PriorityQueueNode **passedQueue);
HuffmanTreeNode *merge(HuffmanTreeNode *node1, HuffmanTreeNode *node2);
HuffmanTreeNode *buildLeaf(unsigned char character, int occurences);
void add(PriorityQueueNode **passedQueue, HuffmanTreeNode *htNode);

#endif