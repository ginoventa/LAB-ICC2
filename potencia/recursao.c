#include <stdio.h>
#include <math.h> 

/*
Nesse caso, a ideia das operações e "dividir para conquistar". Então, dividiremos a potencia 
em duas partes iguais até atingir o fundo desse processo.*/


int potencia(int n, int k){
    if(k == 1) return n; 
    if(k % 2 == 0){
        int metade = potencia(n, k/2);
        return (metade*metade)%1000;
    }else{
        return (n*potencia(n,k-1))%1000; 
    }
}
int main(){
    int n,k; //Números da potência: n^k 
    int numeroPotencia = 1; //Resultado final 
    scanf("%d %d", &n, &k);
    if( n > 0 || n < 99 || k < 0 || k < pow(10,9)){
        if(k == 0){
            printf("%d", n);
        }else{
            printf("%d",potencia(n, k)); 
        }
    }
    return 0;
}