	#include <stdio.h>
	#include <stdlib.h>

	int g_code_1;
	int g_code_2;

	int check(){return g_code_1 == g_code_2;}

	int main(){
		int code, res;
		printf("Enter code: ");
		res = scanf("%d", &code);
		if(!res) abort();
		g_code_1 = code;
		g_code_2 = code + 1;
		if(!check()) abort();
		printf("Victory\n");
	}	
