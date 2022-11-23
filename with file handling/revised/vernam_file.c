/*
	Lab Activity 7.0.0.5 - Vernam Cryptograph C Codes
	Submitted by: Dhony Mark Mendoza
	Submitted to: Godwin Monserate
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#define ALPHA 30
#define STR_MAX 50

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
void remove_spaces(char new_text[], char key[]){
	int i, j, counter = 0;
	
	for(i = 0; i < strlen(new_text); i++){
		if(isspace(new_text[i])){
			for(j = i; j < strlen(new_text); j++){
				new_text[j] = new_text[j+1];
			}
		}
	}
	new_text[j++] = '\0';
}

//used for repeating keywords to map with the plain text
//random key
void key_frequency(char key[], char orig[], char cipher[], int index, int *counter, int *k_counter){
	bool ret_val = false;
	int i, rand_key, holder;
	
	while(ret_val == false){
		rand_key = (rand()%25)+1;
		holder = index^rand_key;
		if(holder < 26){
			key[(*k_counter)++] = orig[rand_key];
			cipher[(*counter)++] = orig[holder];
			ret_val = true;
		}
	}
}

char* encrypt(char orig[], char key[], char text[]){
	char* cipher = malloc(sizeof(char)*STR_MAX);
	int i, j, counter = 0, k_counter = 0;

	for(i = 0; i < strlen(text); i++){
		for(j = 0; j < strlen(orig) && orig[j] != text[i]; j++){}
		if(j < strlen(orig)){
			key_frequency(key, orig, cipher, j, &counter, &k_counter);
		}
	}
	cipher[counter++] = '\0';
	key[k_counter++] = '\0';
	return cipher;
}

char* decrypt(char orig[], char key[], char text[]){
	char* decipher = malloc(sizeof(char)*STR_MAX);
	int i, j, counter = 0;
	int t, k;
	
	for(i = 0; i < strlen(text); i++){
		for(j = 0; j < strlen(orig); j++){
			if(text[i] == orig[j]){
				t = j;
			}
			if(key[i] == orig[j]){
				k = j;
			}
		}
		decipher[counter++] = orig[t^k];
	}
	decipher[counter++] = '\0';
	
	return decipher;
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
	
}

int main(){
	FILE *fmsg = fopen("vernamtext.txt", "r");
	
	char orig[ALPHA] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i = 1;
	
	int choice = 1;
	
	srand(time(NULL));
	
	char text[STR_MAX], buffer[STR_MAX];
	char key[STR_MAX];
	char *cipher, *decipher;
	
	if(fmsg == NULL){
		fmsg = fopen("vernamtext.txt", "w");
		printf("No File read. A new empty file is created.");
	} else{
		while(!feof(fmsg)){
			printf("====================== [TEST CASE %d] ======================\n", i++);
			fgets(buffer, STR_MAX, fmsg);
			strtok(buffer, "\n");
			strcpy(text, buffer);
//			strcpy(key, "NXGTBJPPDPLIIBWBW");
			
			printf("Plain text: %s\n", text);

			if(choice == 1){
				toupper_text(text);
				remove_spaces(text, key);
				cipher = encrypt(orig, key, text);
				printf("Generated OTP: %s\n\n", key);
				printf("Cipher text: %s\n", cipher);
			} else if(choice == 2){
				decipher = decrypt(orig, key, text);
				to_original(buffer, decipher);
				tolower_text(decipher);
				printf("Decipher text: %s\n\n", decipher);
			}
		}
	}
	
	return 0;
}
