#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUB_MAX 26
#define STR_MAX 26

char* ret_sub(char orig[], int shift){
	char *sub = malloc(sizeof(char)*SUB_MAX);
	char key;
	int i, j;
	
	strcpy(sub, orig);
	for(i = 0; i < shift; i++){
		key = sub[0];
		for(j = 0; j != 25; j++){
			sub[j] = sub[j+1];
		}
		sub[j] = key;
	}
	return sub;
}

void shift_encrypt(char *string, char orig[], char sub[]){
	int i, j = 0;
	
	for(i = 0; orig[i] != '\0'; i++){
		if(string[j] == orig[i]){
			string[j] = sub[i];
			j++;
			i = 0;
		}
	}
}

int main(){
	char orig[SUB_MAX] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char string[STR_MAX] = "HELLO";
	
	char *sub;
	int shift = 3;
	
	printf("ORIG: %s\n", orig);
	printf("No. of Shifts: %d\n", shift);
	
	sub = ret_sub(orig, shift);
	printf("SUBS: %s\n", sub);
	
	printf("\nPlain Text: %s", string);
	shift_encrypt(string, orig, sub);
	printf("\nEncrypted: %s", string);
	
	return 0;
}
