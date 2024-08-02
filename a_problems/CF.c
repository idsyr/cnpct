#ifdef PROBLEM_CF // cont frac representation

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define ll long long

void cfr(ll num, ll den){ ll tmp;
    while((tmp = num % den) != 0){
        printf("%lld ", num / den);
        num = den;
        den = tmp;
    }
    printf("%lld\n", num / den);
}

int main(){
    ll num, den;
    int scanf_n = scanf("%lld%lld", &num, &den);
    if(scanf_n != 2 || den == 0) {
        printf("ERROR: invalid input. \nas input thr decimal numerator and denominator != 0 are expected\n");
        abort();
    }
    cfr(num, den);
    
}

#endif
