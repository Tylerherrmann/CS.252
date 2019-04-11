#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "huffman_tree_node.h"

int main(int argc, char **argv) {

	if(argc != 4) {
		printf("Usage: %s is provided, filepath to a character count file, a filepath to the input huffman encoded file, and a filepath to store the resulting text file is required.\n", argv[0]);
		return -1;
	} else {
		
		FILE *fileReadCC = fopen(argv[1], "rb");
		FILE *fileReadHuff = fopen(argv[2], "rb");
		FILE *fileWrite = fopen(argv[3], "w");
		
		int readBinary[128];
		PriorityQueueNode *pq = NULL;
		

		for(int i=0; i<128; i++){
			fread(&readBinary[i],sizeof(int),1,fileReadCC);
			add(&pq, buildLeaf(i, readBinary[i]));	
		}
		
		// Adding our "EoF" to the PQ
		add(&pq, buildLeaf(128, 1));
		
		for(int i=0; i<128; i++){
			HuffmanTreeNode *temp1 = pop(&pq);
			HuffmanTreeNode *temp2 = pop(&pq);
			add(&pq, merge(temp1, temp2));
		}
		
		HuffmanTreeNode *root = pop(&pq);
		int bitCounter = 0;
		int arrayValue;
		int asciiValue;
		unsigned char bitBuffer[8] = {0};
		unsigned char byteBuffer[1] = {0};
		HuffmanTreeNode *tempRoot = root;
		fread(byteBuffer, 1,1,fileReadHuff);
		

		for (int i=0; i<sizeof(byteBuffer)*8; i++) {
			bitBuffer[i] = ((1 << (i % 8)) & (byteBuffer[i/8])) >> (i % 8);
		}
		
		while(asciiValue != 128 || arrayValue != 16) {
			
			while(tempRoot->left != NULL && tempRoot->right != NULL) {
				
				if(bitBuffer[bitCounter] == 0) {
					bitCounter++;
					tempRoot = tempRoot->left;
					if(bitCounter == 8) {
						fread(byteBuffer, 1,1,fileReadHuff);
						for (int i=0; i<sizeof(byteBuffer)*8; i++) {
							bitBuffer[i] = ((1 << (i % 8)) & (byteBuffer[i/8])) >> (i % 8);
						}
						bitCounter = 0;
					}
				} else {
					bitCounter++;
					tempRoot = tempRoot->right;
					if(bitCounter == 8) {
						fread(byteBuffer, 1,1,fileReadHuff);
						for (int i=0; i<sizeof(byteBuffer)*8; i++) {
							bitBuffer[i] = ((1 << (i % 8)) & (byteBuffer[i/8])) >> (i % 8);
						}
						bitCounter = 0;
					}
				}
			
			}
		
			// Write to text file here and check eof flag, don't forget to reset root
			// Iterate through root value[i] until != 0
			
			for(int i=0; i!=17; i++) {
				if(tempRoot->value[i] != 0) {
					arrayValue = i;
				}
			}
				
			if(tempRoot->value[arrayValue] == 1){
				asciiValue = (arrayValue * 8);
			} else if(tempRoot->value[arrayValue] == 2) {
				asciiValue = ((arrayValue * 8) + 1);
			} else if(tempRoot->value[arrayValue] == 4) {
				asciiValue = ((arrayValue * 8) + 2);
			} else if(tempRoot->value[arrayValue] == 8) {
				asciiValue = ((arrayValue * 8) + 3);
			} else if(tempRoot->value[arrayValue] == 16) {
				asciiValue = ((arrayValue * 8) + 4);
			} else if(tempRoot->value[arrayValue] == 32) {
				asciiValue = ((arrayValue * 8) + 5);
			} else if(tempRoot->value[arrayValue] == 64) {
				asciiValue = ((arrayValue * 8) + 6);
			} else {
				asciiValue = ((arrayValue * 8) + 7);
			}

			if(arrayValue == 16 || asciiValue == 128) {
				printf("We got here!");
				goto done;
			}
			
			char c = asciiValue;
			fputc(c, fileWrite);

			tempRoot = root;
	
		}
		
		done:
		fclose(fileReadCC);
		fclose(fileReadHuff);
		fclose(fileWrite);
		return 0;
	}
	
}