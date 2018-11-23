#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char BinaryDigits[] = "0000000100100011010001010110011110001001101010111100110111101111";
const char base64Digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char *argv[]) {
	unsigned char* hex = argv[1];
	int lengthOfInput = strlen(argv[1]);
	printf("%s, %d",hex,lengthOfInput);
	if((lengthOfInput*4)%6 != 0) {
		puts("Wrong size!");
		return 0;
	}

	for(int i=0;i<lengthOfInput;i++) {
		if(!((hex[i]>47 && hex[i] <58)||(hex[i]>96&&(hex[i]<103)))) {
			puts("allowed characters: 0-9, a-f.");
			return 0;
		}
	}

	unsigned char binary[4*lengthOfInput];
	unsigned char base64[sizeof(binary)/6];
	printf("%s\n",hex);
	for(int i=0;i<lengthOfInput;i++) {
		if(hex[i]>47 && hex[i]<58) {
			int shift = 4*(hex[i]-48);
			strncpy(binary+4*i,BinaryDigits+shift,4);
		}
		else if(hex[i]>96 && hex[i]<103) {	
			int shift = 4*(hex[i]-97+10);
			strncpy(binary+4*i,BinaryDigits+shift,4);
		}
	}
	int numberOfbase64digits = sizeof(binary)/6;
	for(int i=0;i<sizeof(base64);i++) {
		char* indexForBase64_char = (char*) malloc (7);
		strncpy(indexForBase64_char,binary+6*i,6);
		indexForBase64_char[6] = '\0';
		char* pEnd;
		int indexForBase64_int = strtol(indexForBase64_char,&pEnd,2);
		strncpy(base64+i,base64Digits+indexForBase64_int,1);
		free(indexForBase64_char);
	}	
	base64[sizeof(base64)] = '\0';
	printf("%s\n",base64);
}
