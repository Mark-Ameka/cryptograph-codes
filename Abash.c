#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STR_MAX 50

/*
	A = 65	||	a = 97
	Z = 90	||	z = 122
	
	formula:
	65 + 90 - 65
	155
	
	0 = 48
	9 = 57
	105
*/

void abash(char *word){
	int i, key = 0;
	
	for(i = 0; word[i] != '\0'; i++){
		if(!isspace(word[i])){
			if(islower(word[i])){
				key = 219;
				key -= word[i];
			} else if(isupper(word[i])){
				key = 155;
				key -= word[i];
			} else if(isdigit(word[i])){
				key = 105;
				key -= word[i];
			}
			word[i] = key;
		}
	}
}

int main(){
	char *word = malloc(sizeof(char)*STR_MAX);
	
	printf("ALPHABET: ABCDEFGHIJKLMNOPQRSTUVWXYZ\n\n");
	
	printf("TEST CASE 1:\n");
	strcpy(word, "The quick brown 1 Fox jumps over the 6 lazy Dogs");
	printf("Plain Text: %s\n", word);
	abash(word);
	printf("Cipher Text: %s", word);
	
	printf("\n\nTEST CASE 2:\n");
	strcpy(word, "Flee at once");
	printf("Plain Text: %s\n", word);
	abash(word);
	printf("Cipher Text: %s", word);
	
	printf("\n\nTEST CASE 3:\n");
	strcpy(word, "yvuliv gsvb zoo vhxzkv");
	printf("Cipher Text: %s\n", word);
	abash(word);
	printf("Plain Text: %s", word);
	
	return 0;
}
