#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SUB_MAX 30
#define STR_MAX 45

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

void encrypt(char *text, char orig[], char sub[]){
	int i, j, counter = 0;
	int space = 0;
	
	for(i = 0; text[i] != '\0'; i++){
		for(j = 0; j != 25 && text[i] != orig[j]; j++){}
		if(j != 25){
			text[i] = sub[j];
		}
	}
}

void dencrypt(char *text, char orig[], char sub[]){
	int i, j, counter = 0;
	int space = 0;
	
	for(i = 0; text[i] != '\0'; i++){
		for(j = 0; j != 25 && text[i] != sub[j]; j++){}
		if(j != 25){
			text[i] = orig[j];
		}
	}
}

int main(){
	char orig[SUB_MAX] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char text[STR_MAX];
	
	char *sub;
	int shift = 4;
	
	//Right Shift
	printf("TEST CASE 1:\n");
	printf("ORIG: %s\n", orig);
	printf("No. of Shifts to right: %d\n", shift);
	sub = right_shift(orig, shift);
	printf("SUBS: %s\n", sub);
	
	strcpy(text, "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");
	printf("\nPlain Text: %s", text);
	encrypt(text, orig, sub);
	printf("\nCipher Text: %s", text);
	
	//Left Shift
	shift = 6;
	printf("\n\nTEST CASE 2:");
	printf("\nORIG: %s", orig);
	printf("\nNo. of Shifts to left: %d", shift);
	sub = left_shift(orig, shift);
	printf("\nSUBS: %s\n", sub);
	
	strcpy(text, "A COLD DAY IN JULY");
	printf("\nPlain Text: %s", text);
	encrypt(text, orig, sub);
	printf("\nCipher Text: %s", text);
	
	//Right Shift
	shift = 11;
	printf("\n\nTEST CASE 3:");
	printf("\nORIG: %s", orig);
	printf("\nNo. of Shifts to right: %d", shift);
	sub = left_shift(orig, shift);
	printf("\nSUBS: %s\n", sub);
	
	strcpy(text, "VPPA JZFC PJPD APPWPO");
	printf("\nCipher Text: %s", text);
	dencrypt(text, orig, sub);
	printf("\nPlain Text: %s", text);
	
	return 0;
}
