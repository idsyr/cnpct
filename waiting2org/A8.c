// OUT OF NUMERATION Логическая память и вирутальная память 
// SIGSEV - sigmentation fault
// valgrind ./a.out
// valgrind --leak-check=full ./a.out  (-g)
// void*
// время жизни, static 


#ifdef HEAP_EOM

#include <stdio.h>
#include <stdlib.h>

const int MAXCNT = 1000;
const int ALLOCSZ = 10000;

int main(){
	int i, j; int* p;
	for(i = 0; i< MAXCNT; ++i){
		for(j = 0; j < MAXCNT; ++j){
			p = malloc(ALLOCSZ);
			if(p == NULL)
				printf("Spotted EOM on i = %d, ALLOCZ = %d\n", i, ALLOCSZ);
		}
	}
}

#endif



#ifdef STACK_EOM

#include <stdio.h>
#include <stdlib.h>

const int ALLOCSZ = 100000;
const int MAXCNT = 84;

int foo(int cnt){
	char s[ALLOCSZ];
	if(cnt > 0) {
		printf(".");
		foo(cnt - 1);
	}
	return 0;
}

int main(){
	foo(MAXCNT);
}

#endif

//project euler

