#ifdef PROBLEM_PP // pisano period

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ull unsigned long long

typedef struct {
    int fibm;
    int pp_len;
} pp_algo_t;

pp_algo_t pp_algo(ull num, ull mod){
    pp_algo_t res;
    int len = 1;
    int fib_pos = 0;
    int fm2 = 0;
    int fm1 = 1;
    int tmp;

    if(mod == 0) res.pp_len = 0;
    else {
        for(; ; ++len){
            tmp = (fm1 + fm2) % mod;
            fm2 = fm1;
            fm1 = tmp;
            if(fm1 == 1 && fm2 == 0) break;
        }
        fm2 = 0;
        fm1 = 1;
        res.pp_len = len;
    }
    
    fib_pos = num%len;
    if(fib_pos == 0) res.fibm = 0;
    else {
        while(--fib_pos){
            tmp = (fm1 + fm2) % mod;
            fm2 = fm1;
            fm1 = tmp;
        }
        res.fibm = fm1;
    }

    return res;
}

int main(){
    ull num, mod;
    pp_algo_t pp_algo_res;
    int scanf_n = scanf("%llu%llu", &num, &mod);
    if(scanf_n != 2){
        printf("ERROR: invalid input\n");
        abort();
    }
    pp_algo_res = pp_algo(num, mod);
    printf("%d %d\n", pp_algo_res.fibm, pp_algo_res.pp_len);
}

#endif
