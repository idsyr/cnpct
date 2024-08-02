#ifdef PROBLEM_RL // recursion to loop

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int iabs(int x){return (x < 0) ? -x : x;}

int eu_mod(int x, int y){
    int res;
    assert(y!=0);
    res = x%y;
    if(res<0) res+= iabs(y);
    return res;
}

long long gcd(long long x, long long y){ long long tmp;
    while((tmp = eu_mod(x,y))!= 0){
        x = y;
        y = tmp;}
    return y;
}

int main(){
    long long x = 0, y = 0, g;
    long long res;

    res = scanf("%lld%lld", &x, &y);
    assert(res == 2);
    g = gcd(x, y);
    printf("%lld\n", g);
}

#endif
