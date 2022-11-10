#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define STR_MAX 50

/*
	A = 65
	Z = 90
	a = 97
	z = 122
	
	formula:
	65 + 90 - 65
	155
	
	0 = 48
	9 = 57
	105
*/

int main(){
	char word[STR_MAX] = "The quick brown 1 Fox jumps over the 6 lazy Dogs";
	
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
	
	puts(word);	
	
	return 0;
}
