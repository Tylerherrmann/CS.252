#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "huffman_tree_node.h"

int main(int argc, char **argv) {

	if(argc != 4) {
		printf("Usage: %s is provided, filepath to a character count file, a filepath to the input text file, and a filepath to store the resulting encoded file is required.\n", argv[0]);
		return -1;
	} else {
		
		FILE *fileReadCC = fopen(argv[1], "rb");
		FILE *fileReadTxt = fopen(argv[2], "rw");
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
		
		//printf("Test: %u", root->left->right->left->right->right->right->left->left->right->right->left->left->right->right->right->right->left->right->value[16]);
		
		unsigned char value[17] = {0};
		int bitCounter = 0;
		unsigned char bitBuffer[8];
		HuffmanTreeNode *tempRoot = root;
		int byte;

				
		// Sooooooo what we need to do is pull a character out from the text file.. Traverse the tree until we hit a leaf node
		// and as we traverse the tree everytime we add 8 bits our buffer we shit this out into our alice.huf file.		
		
		while(!feof(fileReadTxt)) {
			int asciiValue = fgetc(fileReadTxt);
			value[(asciiValue / 8)] = 1 << (asciiValue % 8);
			
			while(tempRoot->left != NULL && tempRoot->right != NULL) {
			
				if(((tempRoot->left->value[(asciiValue / 8)]) & (value[(asciiValue / 8)])) == (value[(asciiValue / 8)])) {
					bitBuffer[bitCounter] = 0;
					bitCounter++;
					tempRoot = tempRoot->left;
					if(bitCounter == 8) {
						
						if(bitBuffer[0] == 1) {
							byte += 1;
						} 
						
						if(bitBuffer[1] == 1) {
							byte += 2;
						} 

						if(bitBuffer[2] == 1) {
							byte += 4;
						} 
												
						if(bitBuffer[3] == 1) {
							byte += 8;
						}

						if(bitBuffer[4] == 1) {
							byte += 16;
						} 
						
						if(bitBuffer[5] == 1) {
							byte += 32;
						} 						
 						
						if(bitBuffer[6] == 1) {
							byte += 64;
						} 						
						
						if(bitBuffer[7] == 1) {
							byte += 128;
						} 				
						
						fwrite(&byte, 1, 1, fileWrite);
						byte = 0;
						bitCounter = 0;
					}

				} else if(((tempRoot->right->value[(asciiValue / 8)]) & (value[(asciiValue / 8)])) == (value[(asciiValue / 8)])) {
					bitBuffer[bitCounter] = 1;
					bitCounter++;
					tempRoot = tempRoot->right;
					if(bitCounter == 8) {
						if(bitBuffer[0] == 1) {
							byte += 1;
						} 
						
						if(bitBuffer[1] == 1) {
							byte += 2;
						} 

						if(bitBuffer[2] == 1) {
							byte += 4;
						} 
												
						if(bitBuffer[3] == 1) {
							byte += 8;
						}

						if(bitBuffer[4] == 1) {
							byte += 16;
						} 
						
						if(bitBuffer[5] == 1) {
							byte += 32;
						} 						
 						
						if(bitBuffer[6] == 1) {
							byte += 64;
						} 						
						
						if(bitBuffer[7] == 1) {
							byte += 128;
						} 				
						
						fwrite(&byte, 1, 1, fileWrite);			
						byte = 0;						
						bitCounter = 0;
					}
				}
			}

			tempRoot = root;
			memset(&value, 0, sizeof(value));
		}
		
		tempRoot = root;
		int eofValue = 128;
		value[(eofValue / 8)] = 1 << (eofValue % 8);
			
		while(tempRoot->left != NULL && tempRoot->right != NULL) {
			
			if(((tempRoot->left->value[(eofValue / 8)]) & (value[(eofValue / 8)])) == (value[(eofValue / 8)])) {
				bitBuffer[bitCounter] = 0;
				bitCounter++;
				tempRoot = tempRoot->left;
				if(bitCounter == 8) {
					
					if(bitBuffer[0] == 1) {
						byte += 1;
					} 
					
					if(bitBuffer[1] == 1) {
						byte += 2;
					} 

					if(bitBuffer[2] == 1) {
						byte += 4;
					} 
												
					if(bitBuffer[3] == 1) {
						byte += 8;
					}

					if(bitBuffer[4] == 1) {
						byte += 16;
					} 
						
					if(bitBuffer[5] == 1) {
						byte += 32;
					} 						
 						
					if(bitBuffer[6] == 1) {
						byte += 64;
					} 						
						
					if(bitBuffer[7] == 1) {
						byte += 128;
					} 				
					fwrite(&byte, 1, 1, fileWrite);
					byte = 0;
					bitCounter = 0;
				}

			} else if(((tempRoot->right->value[(eofValue / 8)]) & (value[(eofValue / 8)])) == (value[(eofValue / 8)])) {
				bitBuffer[bitCounter] = 1;
				bitCounter++;
				tempRoot = tempRoot->right;
				if(bitCounter == 8) {
					if(bitBuffer[0] == 1) {
						byte += 1;
					} 
					
					if(bitBuffer[1] == 1) {
						byte += 2;
					} 

					if(bitBuffer[2] == 1) {
						byte += 4;
					} 
												
					if(bitBuffer[3] == 1) {
						byte += 8;
					}

					if(bitBuffer[4] == 1) {
						byte += 16;
					} 
					
					if(bitBuffer[5] == 1) {
						byte += 32;
					} 						
 						
					if(bitBuffer[6] == 1) {
						byte += 64;
					} 						
						
					if(bitBuffer[7] == 1) {
						byte += 128;
					} 				
					
					fwrite(&byte, 1, 1, fileWrite);			
					byte = 0;						
					bitCounter = 0;
				}
			}
		}
			
		// Clear out any remaining bits in the buffer and write them to the .huf file
		fwrite(&byte, 1, 1, fileWrite);

		fclose(fileReadCC);
		fclose(fileReadTxt);
		fclose(fileWrite);
		return 0;
	}
	
}