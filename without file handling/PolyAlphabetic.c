#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUB_MAX 26
#define STR_MAX 40

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

void encrypt(char orig[], char key[], char new_text[]){
	int i, counter = 0;
	for(i = 0; i != strlen(new_text); i++){
		new_text[counter++] = orig[(new_text[i]+key[i])%26];
	}
}

void decrypt(char orig[], char key[], char new_text[]){
	int i, counter = 0;
	for(i = 0; i != strlen(new_text); i++){
		new_text[counter++] = orig[(new_text[i]-key[i]+26)%26];
	}
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
    char orig[SUB_MAX] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char text[STR_MAX];
    char key[STR_MAX];
    
	char *new_text;
	
	printf("======================= [TEST CASE 1] =======================:\n");
	printf("ENCRYPTION:\n");
	strcpy(text, "we are discovered save yourself");
	strcpy(key, "deceptive");
	printf("Plain Text: %s\n", text);
	printf("Key: %s\n", key);
	toupper_text(text);
	toupper_text(key);
	new_text = remove_spaces(text, key);
	key_frequency(key, new_text);
	encrypt(orig, key, new_text);
	printf("Cipher Text = %s\n\n", new_text);
	
	printf("DECRYPTION:\n");
	printf("Cipher Text: %s\n", new_text);
	decrypt(orig, key, new_text);
	to_original(text, new_text);
	tolower_text(new_text);
	printf("Plain Text: %s", new_text);
	
	printf("\n\n======================= [TEST CASE 2] =======================:\n");
	printf("ENCRYPTION:\n");
	strcpy(text, "mountain out of a molehill");
	strcpy(key, "peeled");
	printf("Plain Text: %s\n", text);
	printf("Key: %s\n", key);
	toupper_text(text);
	toupper_text(key);
	new_text = remove_spaces(text, key);
	key_frequency(key, new_text);
	encrypt(orig, key, new_text);
	printf("Cipher Text = %s\n\n", new_text);
	
	printf("DECRYPTION:\n");
	printf("Cipher Text: %s\n", new_text);
	decrypt(orig, key, new_text);
	to_original(text, new_text);
	tolower_text(new_text);
	printf("Plain Text: %s", new_text);
	
	printf("\n\n======================= [TEST CASE 3] =======================:\n");
	printf("ENCRYPTION:\n");
	strcpy(text, "birds of a feather flock together");
	strcpy(key, "surgery");
	printf("Plain Text: %s\n", text);
	printf("Key: %s\n", key);
	toupper_text(text);
	toupper_text(key);
	new_text = remove_spaces(text, key);
	key_frequency(key, new_text);
	encrypt(orig, key, new_text);
	printf("Cipher Text = %s\n\n", new_text);
	
	printf("DECRYPTION:\n");
	printf("Cipher Text: %s\n", new_text);
	decrypt(orig, key, new_text);
	to_original(text, new_text);
	tolower_text(new_text);
	printf("Plain Text: %s", new_text);
	
    return 0;
}
