#ifdef PROBLEM_NS // number systems

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define ll long long
#define converted_num_n 32

void fill_arr_i32(int* arr, int val, int sz){
    for(int i = 0; i<sz; ++i){
        arr[i] = val;
    }
}

void convert_ns(ll num, ll ns, int* converted_num){ 
    for(int i = 0; num != 0; ++i){
        converted_num[i] = num%ns;
        num  = num/ns;
    }
}

int main(){
    ll num, ns;
    int converted_num[converted_num_n];
    int scanf_n = scanf("%lld%lld", &num, &ns);
    if(scanf_n != 2 || num < 1 || ns < 1 || ns > 11){
        printf("ERROR: invalid input\n expected _num < 1 and 1<_ns<11.");
        abort();
    }

    fill_arr_i32(converted_num, -1, converted_num_n);
    convert_ns(num, ns, converted_num);
    for(int i = converted_num_n-1; i>-1; --i){
        if(converted_num[i]!=-1) printf("%d", converted_num[i]);
    }
    printf("\n");
}

#endif

