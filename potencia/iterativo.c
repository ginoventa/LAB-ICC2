#include <stdio.h>

int main(){
    int n,k, numeroPotencia = 1; 
    scanf("%d %d", &n, &k);
    int base = n%1000;
    if( n > 0 || n < 99 || k < 0 || k < 100000000){
        while(k != 0){
            if(k % 2 == 1){
                numeroPotencia = (numeroPotencia*base)%1000;
            }
            base = (base*base)%1000;
            k = k / 2;
        }   
        printf("%d", numeroPotencia);
    }
    return 0;
}
