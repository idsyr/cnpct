//1.1 Алгоритм Евклида

#ifdef  A1_E1

#include <stdio.h> // include - preprocessor
#include <math.h>

int main() {       // entry point
    printf("A1_E1:SQRT\n");
    
    double d = 42;
    printf("sqrt(d):\t%f\n", sqrt(d));
    
}

// gcc A1.c -o A1_E1 -lm -D A1_E1
// optional: -lc (musl?)
#endif



#ifdef  A1_E2

// FORALL   [src, dev!=0] 
// EXIST    [quo, rem] 
// PROPERTY (src == quo*dev+rem && rem<dev)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void read_input(int *src_p, int *dev_p){
    printf("input _src and _dev:\n"); 
    int input_n = scanf("%d%d", src_p, dev_p); 

    if(input_n != 2 || *dev_p == 0){
        printf("ERROR: input invalid, expect any a and b != 0\n");
        abort();
    }
}

int main(){
    printf("A1_E2:QUOREM\n");
    
    int src, dev, quo, rem;
    
    read_input(&src, &dev);
    assert(dev != 0);
    
    quo = src / dev; rem = src % dev;
    printf("_quo=%d\n_rem=%d\n", quo, rem);
    
}

//assert doesnt work in release, only for debuging purposes
//gcc A1.c -o A1_E2 -DA1_E2
#endif



#ifdef  A1_E3

// PROPERTY   a/b
// THEN EXIST c FOR b=a*c

// PROPERTY   a=gcd(x,y)
// THEN EXIST n FOR a=max{n | (n/x) && (n/y)}  

// PROPERTY x=y*quo+rem
// PROPERTY k=gcd(x,y)
// THEN     rem%k=0
// THEN     gcd(x,y)=gcd(y,rem)

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void read_input(int* a, int* b){
    printf("input _a and _b:\n");
    int scanf_n = scanf("%d%d", a, b);
    if(scanf_n < 2 || *a == 0 || *b == 0){
        printf("ERROR: input invalid\n_a and _b must be decimal\n");
        abort();
    }
}

int iabs(int x) {return (x<0) ? -x : x;}

int eu_mod(int x, int y){
    int res;
    res = x%y; 
    if(res<0) res+=iabs(y);
    return res;
}

int gcd(int a, int b){ int tmp;
    while((tmp = eu_mod(a, b)) != 0){
        a = b;
        b = tmp;
    }
    return b;
}

int main(){
    printf("A1_E2:GCD\n");

    int a, b;
    read_input(&a, &b);
    assert(a != 0);
    assert(b != 0);
    
    printf("GCD:\t%d\n", gcd(a, b));
}

#endif

