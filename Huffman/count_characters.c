#include <stdio.h> 

int main(int argc, char **argv){ 

	int c;
	int nonAsciiFound = 0;
	int charArray[128] = {0};
	int n = 1;
	
	if(argc != 3) {
		printf("Usage: %s is provided, input text file location and write file location required\n", argv[0]);
		return -1;
	} else {
		FILE *fileRead = fopen(argv[1], "r");
		FILE *countWrite = fopen(argv[2], "wb");
		while(!feof(fileRead)) {
			c = fgetc(fileRead);
			if(c >= 0 && c <= 127) {
				charArray[c]++;
			} else if(c!= -1) {
				nonAsciiFound = 1;
			}
		}
	
		for(int i = 0; i!=128; i++) {
			fwrite(&charArray[i],sizeof(int),1,countWrite);
		}
	
		if(nonAsciiFound) {
			printf("Non-Ascii characters found in input text file\n");
		}
	
		fclose(fileRead);
		fclose(countWrite);
	
		return 0;	
		
	}
}