#ifdef PROBLEM_RPS // russian peasant spow

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ull unsigned long long

ull rpm_algo(int num, ull mul, int mod){
    ull res = 1;
    for(;mul > 0;){
        ull qstp = num;
        ull i = 1;
        for(; mul / i != 0; i*=2){
            res = (res * qstp) % mod;
            qstp = (qstp * qstp) % mod;
            mul -= i;
        }
    }
    return res;
}

ull rps_algo(int num, int sup, int mod){
    ull res;
    ull mul = num;
    for(int i = 1; i < sup; ++i){
        mul = rpm_algo(num, mul, 2147483640);
    }
    if(sup == 1) mul = 1;
    res = rpm_algo(num, mul, mod);
    return res;
}

int main(){
    int num, sup, mod;
    ull res;
    int scanf_n = scanf("%d%d%d",
                        &num, &sup, &mod);
    if(scanf_n != 3){
        printf("ERROR: invalid input");
        abort();
    }

    res = rps_algo(num, sup, mod);
    printf("%llu\n", res);
}

#endif
