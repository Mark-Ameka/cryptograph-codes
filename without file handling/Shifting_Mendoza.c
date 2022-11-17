/*
	Lab Act. 7.0.0.2 - Shifting Cryptograph C codes
	Submitted by: Dhony Mark Mendoza
	Submitted to: Godwin Monserate
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SUB_MAX 30
#define STR_MAX 45

//LEFT SHIFT
char* left_shift(char orig[], int shift){
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

//RIGHT SHIFT
char* right_shift(char orig[], int shift){
	char *sub = malloc(sizeof(char)*SUB_MAX);
	char key;
	int i, j;
	
	strcpy(sub, orig);
	for(i = 0; i < shift; i++){
		key = sub[25];
		for(j = 25; j != 0; j--){
			sub[j] = sub[j-1];
		}
		sub[j] = key;
	}
	return sub;
}

//ENCRYPT
/*

	Shift by 1 at right:
	Plain Text: FLOW RIVER
	          
orig =	A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
sub  =	Z A B C D E F G H I J K L M N O P Q R S T U V W X Y
	
cipher  EKNV QHUDQ
	
*/
void encrypt(char *text, char orig[], char sub[]){
	int i, j, counter = 0;
	int space = 0;
	
	for(i = 0; text[i] != '\0'; i++){
		for(j = 0; j < 26 && text[i] != orig[j]; j++){}
		if(j < 26){
			text[i] = sub[j];
		}
	}
}

//DECRYPT
/*

	Shift by 1 at right:
	Plain Text: EKNV QHUDQ
	          
sub  =	Z A B C D E F G H I J K L M N O P Q R S T U V W X Y
orig =	A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
	
cipher  FLOW RIVER
	
*/
void decrypt(char *text, char orig[], char sub[]){
	int i, j, counter = 0;
	int space = 0;
	
	for(i = 0; i < strlen(text); i++){
		for(j = 0; j < 26 && text[i] != sub[j]; j++){}
		if(j < 26){
			text[i] = orig[j];
		}
	}
}

int main(){
	char orig[SUB_MAX] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char text[STR_MAX];
	
	char *sub;
	int shift;
	
	//Right Shift
	shift = 3;
	printf("TEST CASE 1:\n");
	printf("No. of Shifts to right: %d\n", shift);
	printf("ORIG: %s\n", orig);
	sub = right_shift(orig, shift);
	printf("SUBS: %s\n", sub);
	
	strcpy(text, "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
	printf("\nPlain Text: %s", text);
	encrypt(text, orig, sub);
	printf("\nCipher Text: %s", text);
	decrypt(text, orig, sub);
	printf("\nDecrypt Cipher: %s", text);
	
	//Left Shift
	shift = 6;
	printf("\n\nTEST CASE 2:");
	printf("\nNo. of Shifts to left: %d", shift);
	printf("\nORIG: %s", orig);
	sub = left_shift(orig, shift);
	printf("\nSUBS: %s\n", sub);
	
	strcpy(text, "A COLD DAY IN JULY");
	printf("\nPlain Text: %s", text);
	encrypt(text, orig, sub);
	printf("\nCipher Text: %s", text);
	decrypt(text, orig, sub);
	printf("\nDecrypt Cipher: %s", text);
	
//	//Right Shift
	shift = 11;
	printf("\n\nTEST CASE 3:");
	printf("\nNo. of Shifts to right: %d", shift);
	printf("\nSUBS: %s\n", sub);
	sub = left_shift(orig, shift);
	printf("\nORIG: %s", orig);
	
	strcpy(text, "VPPA JZFC PJPD APPWPO");
	printf("\nCipher Text: %s", text);
	decrypt(text, orig, sub);
	printf("\nPlain Text: %s", text);
	encrypt(text, orig, sub);
	printf("\nEncrypt Cipher: %s", text);
	
	return 0;
}
