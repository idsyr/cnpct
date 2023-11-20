#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[]){
	int jagged_row0[] = {1,2,3};
	int jagged_row1[] = {4,5};
	int* jagged_array0[] = {jagged_row0, jagged_row1};
	printf("%d\n", jagged_array0[0][1]);
	int** vla0 = jagged_array0;
	printf("%d\n", vla0[0][1]);

	int* jagged_array1[2];
	jagged_array1[0] = malloc(4 *sizeof(int));
	jagged_array1[1] = calloc(4, sizeof(int));
	printf("%d\n", jagged_array1[1][0]);
	int** vla1 = jagged_array1;
	printf("%d\n", vla1[0][1]);
}
