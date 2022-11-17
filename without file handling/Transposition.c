#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SUB_MAX 26
#define STR_MAX 50

int cmpfunc (const void * a, const void * b) {
	const char* aa = (const char*)a;
	const char* bb = (const char*)b;
	return strcmp(aa, bb);
}

void toupper_text(char text[]){
	int i;
	for(i = 0; i < strlen(text); i++){
		text[i] = toupper(text[i]);
	}
}

void tolower_text(char text[]){
	int i;
	for(i = 0; i < strlen(text); i++){
		text[i] = tolower(text[i]);
	}
}

void remove_spaces(char text[], char key[]){
	int i, j, counter = 0;
	
	if(strlen(key) != strlen(text)){
    	for(i = 0; i < strlen(text); i++){
    		if(isspace(text[i])){
    			for(j = i; j < strlen(text); j++){
    				text[j] = text[j+1];
				}
			}
		}
	}
}

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

char* encrypt(char key_freq[], char key_sorted[], char text[], char pass_key[]){
	char *cipher = malloc(sizeof(char)*STR_MAX);
	int pass = 0;
	int i, j, counter = 0;
	for(i = 0; i < strlen(key_sorted); i++){
		for(j = 0; j < strlen(key_freq); j++){
			if(key_freq[j] == key_sorted[i]){
				pass_key[pass++] = key_sorted[i];
				cipher[counter++] = text[j];
			}
		}
	}
	return cipher;
}

void remove_letter(int index, char word[]){
	for(; index < strlen(word); index++){
		word[index] = word[index+1];
	}
}

char* decrypt(char key_freq[], char key[], char cipher[], char pass_key[]){
	char *decipher = malloc(sizeof(char)*STR_MAX);
	int i, j, l, counter = 0;
	for(i = 0; i < strlen(key_freq); i++){
		for(j = 0; j < strlen(pass_key) && pass_key[j] != key_freq[i]; j++){}
		if(j < strlen(pass_key)){
			decipher[counter++] = cipher[j];
			remove_letter(j, cipher);
			remove_letter(j, pass_key);
		}
	}
	return decipher;        
}

void to_original(char text[], char new_text[]){
	int i, j;
	for(i = 0; i < strlen(text); i++){
		if(isspace(text[i])){
			for(j = strlen(new_text); j != i; j--){
				new_text[j] = new_text[j-1];
			}
			new_text[i] = ' ';
		}
	}
}

int main(){
	char text[STR_MAX];
	char key[STR_MAX];
	
	char key_freq[STR_MAX];
	char key_sorted[STR_MAX];
	char pass_key[STR_MAX];
	char new_text[STR_MAX], *cipher, *decipher;
	
	printf("====================== [TEST CASE 1] ======================\n");
	strcpy(text, "meet at three pm today at the usual location");
	strcpy(key, "zebras");
	strcpy(key_freq, key);
	strcpy(key_sorted, key);
	strcpy(new_text, text);
	
	printf("Plain Text: %s\n", text);
	printf("Key: %s\n\n", key);
	
	remove_spaces(new_text, key);

	key_frequency(key_freq, new_text);
	qsort(key_sorted, strlen(key_sorted), sizeof(char), cmpfunc);
	
	cipher = encrypt(key_freq, key_sorted, new_text, pass_key);
	toupper_text(cipher);
	printf("Encrypt: %s\n", cipher);

	decipher = decrypt(key_freq, key, cipher, pass_key);
	tolower_text(decipher);
	to_original(text, decipher);
	printf("Decrypt: %s\n\n", decipher);
	
	printf("====================== [TEST CASE 2] ======================\n");
	strcpy(text, "we are discovered save yourself");
	strcpy(key, "413895");
	strcpy(key_freq, key);
	strcpy(key_sorted, key);
	strcpy(new_text, text);
	
	printf("Plain Text: %s\n", text);
	printf("Key: %s\n\n", key);
	
	remove_spaces(new_text, key);

	key_frequency(key_freq, new_text);
	qsort(key_sorted, strlen(key_sorted), sizeof(char), cmpfunc);
	
	cipher = encrypt(key_freq, key_sorted, new_text, pass_key);
	toupper_text(cipher);
	printf("Encrypt: %s\n", cipher);

	decipher = decrypt(key_freq, key, cipher, pass_key);
	tolower_text(decipher);
	to_original(text, decipher);
	printf("Decrypt: %s\n\n", decipher);
	
	printf("====================== [TEST CASE 3] ======================\n");
	strcpy(text, "A Few Sandwiches Short of a Picnic");
	strcpy(key, "nj7w1t");
	strcpy(key_freq, key);
	strcpy(key_sorted, key);
	strcpy(new_text, text);
	
	printf("Plain Text: %s\n", text);
	printf("Key: %s\n\n", key);
	
	remove_spaces(new_text, key);

	key_frequency(key_freq, new_text);
	qsort(key_sorted, strlen(key_sorted), sizeof(char), cmpfunc);
	
	cipher = encrypt(key_freq, key_sorted, new_text, pass_key);
	toupper_text(cipher);
	printf("Encrypt: %s\n", cipher);

	decipher = decrypt(key_freq, key, cipher, pass_key);
	tolower_text(decipher);
	to_original(text, decipher);
	printf("Decrypt: %s\n\n", decipher);

    return 0;
}
