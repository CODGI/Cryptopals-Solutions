#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const char binaryDigits[] = "0000000100100011010001010110011110001001101010111100110111101111";

const double letterFrequency[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.03872, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09256, 0.02758, 0.00978, 0.05370, 0.00150, 0.03978, 0.00074};

int main(int argc, char* argv[]) {
	char* fileName = argv[1];
	FILE* fp;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(fileName,"r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	double minScore=10;
	char* encryptedLine = (char*) malloc(61);
	char* decryptedLine = (char*) malloc(61);
	char key=0;
	while((read = getline(&line,&len,fp)) != -1) {
		unsigned char* message = line;
		int messageLength = strlen(message);
		message[messageLength] = '\0';
		messageLength--;
		for(int i=0;i<messageLength;i++) {
			if(!((message[i]>47 && message[i] <58)||(message[i]>96&&(message[i]<103)))) {
				puts("allowed characters: 0-9, a-f.");
				return 0;
			}
		}
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
		int numberOfBytesInMessage = messageLength/2;
		char messageInAscii[numberOfBytesInMessage];
		for(int i=0;i<numberOfBytesInMessage;i++) {
			char* byte = (char*) malloc(9);
			strncpy(byte,messageBin+8*i,8);
			byte[8] = '\0';
			char* pEnd;
			char c = strtol(byte,&pEnd,2);
			strncpy(messageInAscii+i,&c,1);
			free(byte);
		}
		messageInAscii[numberOfBytesInMessage] = '\0';
		char* decryptedMessage = (char*) malloc(numberOfBytesInMessage+1);
		for(int i=0;i<128;i++) {
			char* deciphered = (char*) malloc(numberOfBytesInMessage+1);
			int letterFrequencies[26];
			for(int i=0;i<26;i++){
				letterFrequencies[i] = 0;
			}
			for(int j=0;j<numberOfBytesInMessage;j++) {
				int c = (int) messageInAscii[j];
				int newC = c^i;
				deciphered[j] =(char) newC ;
				if(newC>96 && newC<123){
					letterFrequencies[newC-97]++;
				}
			}
			double score = 0;
			for(int k=0;k<26;k++){
				score += fabs((((double) letterFrequencies[k])/numberOfBytesInMessage)-letterFrequency[k]);
			}
			if(score<minScore) {
				key = i;
				minScore = score;
				strncpy(encryptedLine,line,numberOfBytesInMessage);
				strncpy(decryptedLine,deciphered,numberOfBytesInMessage);
				encryptedLine[numberOfBytesInMessage] = '\0';
				decryptedLine[numberOfBytesInMessage] = '\0';
			}
			free(deciphered);
		}

	}

	printf("Line:\n%s\n decrypts with key\n%c\nto\n%s.",encryptedLine,key,decryptedLine);

	fclose(fp);
	if(line)
		free(line);
}
