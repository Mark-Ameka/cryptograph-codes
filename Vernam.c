#include <stdio.h>
#include <string.h>
#define SUB_MAX 26
#define STR_MAX 30

int main(){
    char orig[SUB_MAX] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char key[STR_MAX] = "RANCHOBABA";
    char text[STR_MAX] = "RAMSWARUPK";
    char cipher[STR_MAX];
    
    int i, j;
    int k = 0, t = 0;
    int count = 0;
    
    for(i = 0; i != strlen(text); i++){
    	for(j = 0; j != 25; j++){
			if(orig[j] == text[i]){
				t = j;
			}
    		if(orig[j] == key[i]){
    			k = j;
			}
		}
		if((t^k) > 26){
			cipher[count++] = orig[(t^k)-26];
		} else{
			cipher[count++] = orig[(t^k)];
		}
	}
	
	printf("%s", cipher);
    
    return 0;
}
