#ifdef PROBLEM_FM // fib mod 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int fm_algo(int num, int mod){
    int res = 0;
    int fm1 = 0;
    int fm2 = 1;
    
    while(num--){
        res = (fm1 + fm2) % mod;
        fm2 = fm1;
        fm1 = res;
    }
    return res;
}

int main(){
    int num, mod;
    int scanf_n = scanf("%d%d", &num, &mod);
    if(scanf_n != 2){
        pritnf("ERROR: invalid input\n");
        abort();
    }
    printf("%d\n", fm_algo(num, mod));
}

#endif

