#include <stdlib.h>
#include <stdio.h>
int main(){
	int* a = calloc(4, sizeof(int));
	int* b = calloc(1, sizeof(int[4]));
	int* c = calloc(4 , sizeof *b);
	for(int i = 0; i<4; ++i){
		printf("%d", &a[i]);
	}
	free(a);
	free(b);
	free(c);
}
//--->one contiguous block
