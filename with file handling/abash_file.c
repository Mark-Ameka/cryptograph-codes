/*
	Lab Act. 7.0.0.1 - Abash Cryptograph C codes
	Submitted by: Dhony Mark Mendoza
	Submitted to: Godwin Monserate
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STR_MAX 50

/*
	A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
	Z Y X W V U T S R Q P O N M L K J I H G F E D C B A
	
	0 1 2 3 4 5 6 7 8 9
	9 8 7 6 5 4 3 2 1 0
	
	A = 65	=>	Z = 90
	a = 97	=>	z = 122
	0 = 48	=>	9 = 57
	
	lower case = 219
	upper case = 155
	digit case = 105
	
	formula [ASCII]:
	[FIRST LETTER] + [LAST LETTER] = SUM
	SUM - [LETTER] = [REVERSED LETTER]
	
	Example [UPPERCASE]:
	65 + 90 = 155
	155 - 88[X] = C
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

void writeFile(FILE *fcipher, char word[]){
	fcipher = fopen("ciphertext.txt", "a");

	if(fcipher == NULL){
		return;
	} else{
		fputs(word, fcipher);
		fputc('\n', fcipher);
	}
	fclose(fcipher);
}

void readFile(FILE *fmsg, char word[]){
	fmsg = fopen("plaintext.txt", "r");
	FILE *fcipher = fopen("ciphertext.txt", "w");
	int i = 1;
	
	if(fmsg == NULL){
		strcpy(word, "No content");
	} else{
		printf("ALPHABET: ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
		while(!feof(fmsg)){
			fgets(word, STR_MAX, fmsg);
			strtok(word, "\n");
			printf("\nTEST CASE %d:\n", i++);
			printf("Plain Text: %s\n", word);
			abash(word);
			printf("Cipher Text: %s\n", word);
			writeFile(fcipher, word);
		}
	}
	fclose(fmsg);
}

int main(){
	char word[STR_MAX];
	FILE *fmsg = fopen("plaintext.txt", "r");
	
	if(fmsg == NULL){
		fmsg = fopen("plaintext.txt", "w");
		printf("No file read. A new file just created.");
	} else{
		readFile(fmsg, word);
	}
	return 0;
}
