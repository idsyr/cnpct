#ifdef PROBLEM_FS // factorial num system

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ll long long

void fs_algo_with_printf(ll num){
    ll pnum = 1;
    ll pval = 0;
    int i = 2;

    for(; num/pnum != 0; ++i){
        pnum *= i;
    } --i;
    pnum = pnum / i--;

    for(; i>0; --i){
        pval = num/pnum;
        num -= pval*pnum;
        pnum /= i;
        printf("%lld.", pval);
    }
}

int main(){
    ll num;
    int scanf_n = scanf("%lld", &num);
    if(scanf_n != 1){
        printf("ERROR: invalid input\n");
        abort();
    }
    fs_algo_with_printf(num);
}

#endif

