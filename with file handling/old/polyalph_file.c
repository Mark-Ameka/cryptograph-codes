/*
	Lab Act. 7.0.0.3 - PolyAlphabetic Cryptograph C codes
	Submitted by: Dhony Mark Mendoza
	Submitted to: Godwin Monserate
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUB_MAX 26
#define STR_MAX 40

//converts text to upper
void toupper_text(char text[]){
	int i;
	for(i = 0; i < strlen(text); i++){
		text[i] = toupper(text[i]);
	}
}

//converts text to lower
void tolower_text(char text[]){
	int i;
	for(i = 0; i < strlen(text); i++){
		text[i] = tolower(text[i]);
	}
}

//remove spaces from the text
char* remove_spaces(char text[], char key[]){
	char *new_text = malloc(sizeof(char)*STR_MAX);
	int i, counter = 0;
	
	if(strlen(key) != strlen(text)){
    	for(i = 0; i < strlen(text); i++){
    		if(!isspace(text[i])){
    			new_text[counter] = text[i];
    			counter++;
			}
		}
	}
	new_text[counter++] = '\0';
	return new_text;
}

//used for repeating keywords to map with the plain text
void key_frequency(char key[], char new_text[]){
	int i, counter = 0;
    if(strlen(key) != strlen(new_text)){
	    for(i = strlen(key); i < strlen(new_text); i++){
			if(counter == strlen(key)){
				counter = 0;
			}
	    	key[i] = key[counter];
	    	counter++;
		}
	}
}

/*
	Plain text: we are discovered save yourself
	keyword: deceptive
	
	Legend:
		C = cipher text
		P = plain text
		K = keyword
	Formula: C[i] = (P[i] + K[i]) mod 26
	
		25 8 2 21 19 22 16 13 6 17 25 6 21 19 22 0 21 25 7 2 16 24  6 11 12  6 9	<= alphabet order
		D  E C  E  P  T  I  V E  D  E C  E  P  T I  V  E D E  C  E  P  T  I  V E	<= keyword

		W  E A  R E D I  S C  O  V E  R E D  S A  V E  Y  O  U  R  S E  L F			<= plain text
		22 4 0 17 4 3 8 18 2 14 21 4 17 4 3 18 0 21 4 24 14 20 17 18 4 11 5			<= alphabet order
		
	Example:
		D = 68
		W = 87
		68 + 87 = 155 (155 is exceeding 26 so we modulo it by 26)
		155 % 26 = 25
		
		now in alphabetical order, 25 is Z so the cipher text should be the character 'Z'
		orig[25] = Z
*/
void encrypt(char orig[], char key[], char new_text[]){
	int i, counter = 0;
	for(i = 0; i != strlen(new_text); i++){
		new_text[counter++] = orig[(new_text[i]+key[i])%26];
	}
}

/*
	Plain text: we are discovered save yourself
	keyword: deceptive
	
	Legend:
		C = cipher text
		P = plain text
		K = keyword
	Formula: C[i] = (P[i] - K[i] + 26) mod 26
	
		25 8 2 21 19 22 16 13 6 17 25 6 21 19 22 0 21 25 7 2 16 24  6 11 12  6 9	<= alphabet order
		D  E C  E  P  T  I  V E  D  E C  E  P  T I  V  E D E  C  E  P  T  I  V E	<= keyword

		Z  I C  V  T  W  Q  N G  R Z  G  V T  W  A  V Z  H C  Q  Y  G  L  M  G J	<= cipher text		
		3  4 2  4 15 19  8 21 4  3 4  2  4 15 19 8 21 4  3 4  2  4 15 19  8 21 4	<= alphabet order
	
	Example:
		Z = 90
		D = 68
		90 - 68 = 22 
			note: we added 26 after subtracting this is because sometime we are getting negative difference.
			example:
				-22 + 26 = 4
				4 % 26 = 4
				4 in alphabet is E so we are getting character 'E';
		
		now in alphabetical order, 22 is W so the decipher text should be the character 'W'
		orig[22] = W
*/
void decrypt(char orig[], char key[], char new_text[]){
	int i, counter = 0;
	for(i = 0; i != strlen(new_text); i++){
		new_text[counter++] = orig[(new_text[i]-key[i]+26)%26];
	}
}

//puts back the spaces from [text] to the [new_text]
void to_original(char text[], char new_text[]){
	int i, j;
	int flag = strlen(text);

	for(i = 0; i < strlen(text); i++){
		if(isspace(text[i])){
			for(j = flag; j != i; j--){
				new_text[j] = new_text[j-1];
			}
			new_text[i] = ' ';
		}
	}
	
	new_text[flag] = '\0';
}

//writes encrypted text to the file
void writeFile(char new_text[]){
	FILE *fcipher = fopen("polycipher.txt", "a+");
	
	if(fcipher == NULL){
		printf("\nCannot create and append file.\n");
		return;
	} else{
		fputs(new_text, fcipher);
		fputc('\n', fcipher);
	}
	fclose(fcipher);
}

int main(){
	FILE *fmsg = fopen("polytext.txt", "r");
	int flag = 0;
	int i = 1;
	
    char orig[SUB_MAX] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char text[STR_MAX];
    char key[STR_MAX];
    char buffer[STR_MAX];
    
	char *new_text;
	
	if(fmsg == NULL){
		fmsg = fopen("polytext.txt", "w");
		printf("No File read. A new empty file is created.");
	} else{
		while(!feof(fmsg)){
			fgets(buffer, STR_MAX, fmsg);
			strtok(buffer, "\n");
			if(flag == 0){
				flag = 1;
				strcpy(text, buffer);
			} else if(flag == 1){
				flag = 0;
				strcpy(key, buffer);
				printf("======================= [TEST CASE %d] =======================:\n", i++);
				printf("ENCRYPTION:\n");
				printf("Plain Text: %s\n", text);
				printf("Key: %s\n", key);
				toupper_text(text);
				toupper_text(key);
				new_text = remove_spaces(text, key);
				key_frequency(key, new_text);
				encrypt(orig, key, new_text);
				printf("Cipher Text = %s\n\n", new_text);
				
				writeFile(new_text);
				printf("DECRYPTION:\n");
				printf("Cipher Text: %s\n", new_text);
				decrypt(orig, key, new_text);
				to_original(text, new_text);
				tolower_text(new_text);
				printf("Plain Text: %s\n\n", new_text);
			}
		}
	}
    return 0;
}
