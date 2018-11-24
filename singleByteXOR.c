#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char binaryDigits[] = "0000000100100011010001010110011110001001101010111100110111101111";

int main(){
	unsigned char message[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	int messageLength = strlen(message);
	unsigned char messageBin[4*messageLength];
	for(int i=0;i<messageLength;i++) {
		if(message[i]>47 && message[i]<58){
			int shift = 4*(message[i]-48);
			strncpy(messageBin+4*i,binaryDigits+shift,4);
		}
		else if(message[i]>96 && message[i]<103) {
			int shift = 4*(message[i]-97+10);
			strncpy(messageBin+4*i,binaryDigits+shift,4);
		}
	}
	unsigned int scores[128];
	for(int i=0;i<128;i++) {
		scores[i] = 0;
	}
	int numberOfBytesInMessage = messageLength/2;
	char messageInAscii[numberOfBytesInMessage];
	for(int i=0;i<numberOfBytesInMessage;i++) {
		char* byte = (char*) malloc(9);
		strncpy(byte,messageBin+8*i,8);
		byte[8] = '\0';
		char* pEnd;
		char c = strtol(byte,&pEnd,2);
		scores[(int) c] ++;
		strncpy(messageInAscii+i,&c,1);
		free(byte);
	}
	messageInAscii[numberOfBytesInMessage] = '\0';
	for(int i=0;i<128;i++) {
		char* deciphered = (char*) malloc(numberOfBytesInMessage+1);
		for(int j=0;j<numberOfBytesInMessage;j++) {
			int c = (int) messageInAscii[j];
			int newC = c^i;
			deciphered[j] =(char) newC ;
		}
		deciphered[numberOfBytesInMessage] = '\0';
		printf("%c : %s\n",i,deciphered);
		free(deciphered);
	}
}

