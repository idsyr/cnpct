#ifdef PROBLEM_EE // ext euclid 

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define ll long long

typedef struct {
    ll gcd;
    ll u;
    ll v;
} ee_algo_t;
    
ee_algo_t ee_algo(ll a, ll b){
    ll tmp, q_k,
       u_k   = 0, 
       u_km2 = 1, 
       u_km1 = 0,
       orgnl_a = a,
       orgnl_b = b;
    ee_algo_t ee_algo_res;
   
    if(a > b) swap(&a, &b);
    while((tmp = (a%b)) != 0){
        q_k = a / b;
        a = b;
        b = tmp;

        u_k = u_km2 - (q_k * u_km1);
        u_km2 = u_km1;
        u_km1 = u_k; 
    }
    
    ee_algo_res.gcd = (b<0)? -b : b;
    ee_algo_res.u = (b<0)? -u_k : u_k;
    ee_algo_res.v = 
       (ee_algo_res.gcd - orgnl_a * ee_algo_res.u) / orgnl_b;

    return ee_algo_res;
}

int main(){
    ll x, y;
    int scanf_n = scanf("%lld%lld", &x, &y);
    ee_algo_t ee_algo_res;

    if(scanf_n != 2){
        printf("ERROR: invalid input.\n");
        abort();
    }
    
    ee_algo_res = ee_algo(x, y);

    printf("%lld %lld %lld\n", 
           ee_algo_res.u,
           ee_algo_res.v,
           ee_algo_res.gcd);
}

#endif

