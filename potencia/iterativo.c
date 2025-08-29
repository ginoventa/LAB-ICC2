#include <stdio.h>
#include <math.h> 

void main(){
    int n,k, numeroPotencia = 1; //Números da potência: n^k 
    scanf("%d %d", &n, &k);
    if( n > 0 || n < 99 || k < 0 || k < pow(10,9)){
        while(k != 0){
            numeroPotencia = (numeroPotencia*n)%1000; 
            k--; 
        }   
        printf("%d", numeroPotencia);
    }
    return;
}
/*
Desenvolvimento: 
    Precisamos multiplicar um número por ele mesmo, pelo número de vezes definido em k. 

    Problema 1: Ele está apenas respondendo 1, o que significa que o passo iterativo não está rodando; 
    Solução 1: As condições do if sempre eram falsas. Troquei elas e agora temos um resultado diferente de 1. 

    Problema 2: Ele não imprime o valor correto; 
    Solução 2: Impressão estava enxertada com outra. Apaguei o printf 

    Problema 3: Saída entrega uma potência acima. 
    Solução 3: Ajustar condição de para do if. 

    Problema 3: Resposta não está formatada do jeito esperada, apenas 3 números. 
    Solução 3: Pegar o resto por %1000 a cada iteração, para que apenas 3 números estejam ali ao final.

    Otimização 1: Diminuir o número de varíaveis. Deletei uma variável para, pelo menos, ocupar menos espaço. (tirei o contador i que estava no while)

*/