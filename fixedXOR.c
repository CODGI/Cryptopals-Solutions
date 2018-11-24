#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char BinaryDigits[] = "0000000100100011010001010110011110001001101010111100110111101111";
const char hexValues[] = "0123456789abcdef";

int main(int argc, char* argv[]) {
	unsigned char* hex1 = argv[1];
	unsigned char* hex2 = argv[2];
	int length1 = strlen(hex1);
	int length2 = strlen(hex2);
	unsigned char resultHex[length1];	
	if(length1 != length2) {
		printf("Values have to have the same length!");
		return 0;
	}
	for(int i=0;i<length1;i++) {
		if(!((hex1[i]>47 && hex1[i]<58)||(hex1[i]>96 && hex1[i]<103))) {
			puts("Allowed characters: 0-9, a-f");
			return 0;
		}
		if(!((hex2[i]>47 && hex2[i]<58)||(hex2[i]>96 && hex2[i]<103))) {
			puts("Allowed characters: 0-9, a-f");
			return 0;
		}

	}
	printf("%s\n%s\n",hex1,hex2);
	unsigned char bin1[4*length1];
	unsigned char bin2[4*length2];
	for(int i=0; i<length1;i++) {
		if(hex1[i]>47 && hex1[i]<58){
			int shift = 4*(hex1[i]-48);
			strncpy(bin1+4*i,BinaryDigits+shift,4);
		}
		else if(hex1[i]>96 && hex1[i]<103) {
			int shift = 4*(hex1[i]-97+10);
			strncpy(bin1+4*i,BinaryDigits+shift,4);
		}
		if(hex2[i]>47 && hex2[i]<58){
			int shift = 4*(hex2[i]-48);
			strncpy(bin2+4*i,BinaryDigits+shift,4);
		}
		else if(hex2[i]>96 && hex2[i]<103) {
			int shift = 4*(hex2[i]-97+10);
			strncpy(bin2+4*i,BinaryDigits+shift,4);
		}
	}
	int newLength = 4*length1;
	unsigned char result[newLength];
	for(int i=0;i<newLength;i++) {
		if(bin1[i] == bin2[i]) {
			result[i] = '0';
		}
		else {
			result[i] = '1';
		}
	}
	for(int i=0;i<length1;i++) {
		char* indexForHex = (char*) malloc(5);
		strncpy(indexForHex,result+4*i,4);
		indexForHex[4] = '\0';
		char* pEnd;
		int indexForHex_int = strtol(indexForHex,&pEnd,2);
		strncpy(resultHex+i,hexValues+indexForHex_int,1);
		free(indexForHex);	
	}
	resultHex[length1] = '\0';
	printf("%s\n",resultHex);

}
