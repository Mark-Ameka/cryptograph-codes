/*
	Lab Act 7.0.0.4 - Transpositional Cryptograph C Codes
	Submitted by: Dhony Mark Mendoza
	Submitted to: Godwin Monserate
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SUB_MAX 26
#define STR_MAX 50

//sorts the key (array of characters)
int cmpfunc (const void * a, const void * b) {
	const char* aa = (const char*)a;
	const char* bb = (const char*)b;
	return strcmp(aa, bb);
}

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

void passkey_func(char pass_key[], char key_freq[],char key[], int size_key, int size_text){
	int i, j, k = 0, count = 0;
	int size_pass = size_text/size_key;
	
	for(i = 0; i < strlen(key); i++){
		for(j = 0; j < strlen(key_freq); j++){
			if(key_freq[j] == key[i]){
				/*  i am returning an array of characters containing the looped sorted key characters.
					with this, I can use this for my decryption process.
					so basically If I have:
							Plain text: meet at three pm today at the usual location
							Key: zebras
					pass_key would return a string containing:
							AAAAAABBBBBBEEEEEERRRRRRSSSSSSZZZZZ
					Simple term, this just dividing the character from the keyword to the plain text.
				*/
				pass_key[count++] = key[i];
			}
		}
	}
}

/*
	Plain text: meet at three pm today at the usual location
	Key: zebras

	Concept View:
		Z	E	B	R	A	S
		m	e	e	t	a	t
		t	h	r	e	e	p
		m	t	o	d	a	y
		a	t	t	h	e	u
		s	u	a	l	l	o
		c	a	t	i	o	n
		
	Array View:
		A B E R S Z <= key sorted
	
		0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35    <= indices
		Z E B R A S Z E B R  A  S  Z  E  B  R  A  S  Z  E  B  R  A  S  Z  E  B  R  A  S  Z  E  B  R  A  S    <= key freq
		
		M E E T A T T H R E  E  P  M  T  O  D  A  Y  A  T  T  H  E  U  S  U  A  L  L  O  C  A  T  I  O  N    <= plain text

	OUTPUT:
		A E A E L O E R O T  A  T  E  H  T  T  U  A  T  E  D  H  L  I  T  P  Y  U  O  N  T  M  A  S  C    <= cipher text
*/
char* encrypt(char key_freq[], char key_sorted[], char text[]){
	char *cipher = malloc(sizeof(char)*STR_MAX);
	int pass = 0;
	int i, j, counter = 0;
	for(i = 0; i < strlen(key_sorted); i++){
		for(j = 0; j < strlen(key_freq); j++){
			if(key_freq[j] == key_sorted[i]){
				cipher[counter++] = text[j];
			}
		}
	}
	cipher[counter++] = '\0';
	return cipher;
}

//removes a letter after mapping the [pass_key] and [key_freq]
void remove_letter(int index, char word[]){
	for(; index < strlen(word); index++){
		word[index] = word[index+1];
	}
}

/*
	Plain text: meet at three pm today at the usual location
	Key: zebras
	
	Array View:
		0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35    <= indices
		Z E B R A S Z E B R  A  S  Z  E  B  R  A  S  Z  E  B  R  A  S  Z  E  B  R  A  S  Z  E  B  R  A  S    <= key freq
		A A A A A A B B B B  B  B  E  E  E  E  E  E  R  R  R  R  R  R  S  S  S  S  S  S  Z  Z  Z  Z  Z  Z    <= pass key
		
		A E A E L O E R O T  A  T  E  H  T  T  U  A  T  E  D  H  L  I  T  P  Y  U  O  N  M  T  M  A  S  C    <= cipher text
		
		==================================================================================================================
		
	Process:
		A A A A A A B B B B  B  B  E  E  E  E  E  E  R  R  R  R  R  R  S  S  S  S  S  S  Z  Z  Z  Z  Z    <= pass key
		
		A E A E L O E R O T  A  T  E  H  T  T  U  A  T  E  D  H  L  I  T  P  Y  U  O  N  T  M  A  S  C    <= cipher text
		
		M <= decipher recently contained
		
	Final process:
		M E E T A T T H R E  E  P  M  T  O  D  A  Y  A  T  T  H  E  U  S  U  A  L  L  O  C  A  T  I  O  N    <= decipher text
		
*/
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
	FILE *fmsg = fopen("transtext.txt", "r");
	int flag = 0;
	int i = 1;
	
	int choice = 1;
	
	char text[STR_MAX];
	char key[STR_MAX];
	char buffer[STR_MAX];
	
	char key_freq[STR_MAX];
	char key_sorted[STR_MAX];
	char pass_key[STR_MAX];
	char new_text[STR_MAX], *cipher, *decipher;
	
	if(fmsg == NULL){
		fmsg = fopen("transtext.txt", "w");
		printf("No File read. A new empty file is created.");
	} else{
		while(!feof(fmsg)){
			fgets(buffer, STR_MAX, fmsg);
			strtok(buffer, "\n");
			if(flag == 0){
				flag = 1;
				strcpy(text, buffer);
			} else if(flag == 1){
				printf("====================== [TEST CASE %d] ======================\n", i++);
				flag = 0;
				strcpy(key, buffer);
				
				strcpy(key_freq, key);
				strcpy(key_sorted, key);
				strcpy(new_text, text);
				
				printf("Plain Text: %s\n", text);
				printf("Key: %s\n\n", key);
				
				remove_spaces(new_text, key);
			
				key_frequency(key_freq, new_text);
				qsort(key_sorted, strlen(key_sorted), sizeof(char), cmpfunc);
				
				if(choice == 1){
					cipher = encrypt(key_freq, key_sorted, new_text);
					toupper_text(cipher);
					printf("Encrypt: %s\n", cipher);
				} else if(choice == 2){
					passkey_func(pass_key, key_freq, key_sorted, strlen(key), strlen(text));
					decipher = decrypt(key_freq, key, text, pass_key);
					tolower_text(decipher);
					to_original(text, decipher);
					printf("Decrypt: %s\n", decipher);
				}
			}
		}
	}
    return 0;
}
