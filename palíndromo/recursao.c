#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*
    Função: modificadorDeString
    Objetivo: Usa a string original inserida pelo usuário e filtra, deixando apenas caracteres alfanuméricos. 
    Além disso, também transforma todos os caracteres alfabéticos maiúsculos para minúsculos, a fim de facilitar 
    a comparação posteriormente. 
*/
char *modificadorDeString(char *frase, char* minuscula){
    int tam = strlen(frase);
    int k = 0;
    for(int j = 0; j < tam; j++){
        if(isalnum(frase[j]) != 0){
            minuscula[k++] = tolower(frase[j]);
        }
    }
    minuscula[k] = '\0';
    return minuscula;     
}
/*
    Função: palindromo_recursivo
    Objetivo: Função que, de maneira recursiva, verifica se uma frase é palíndroma. Faz comparação entre caracteres de maneira
    simétrica na frase.
*/
int palindromo_recursivo(char *frase, int inicio, int fim){
    if(inicio >= fim) return 1;
    if(frase[inicio] != frase[fim]) return 0;
    return palindromo_recursivo(frase, inicio + 1, fim - 1);
}

/*
    Função: verificadorDePalindromo
    Objetivo: Após chamar a função modificadorDeString, começa a comparar a string a fim de verificar se ela é um palíndromo
    ou não. Chama verificador a função palindromo_recursivo, que irá verificar se a frase é, de fato um palíndromo . A partir 
    do momento que identifica padrão que foge do padrão de um palíndromo, encerra a iteração. Após análise completa, retorna 
    se a função é, ou não, um palíndromo. 
*/
void verificadorDePalindromo(char *frase, char *minuscula){
    minuscula = modificadorDeString(frase, minuscula);
    int tam = strlen(minuscula);
    if(palindromo_recursivo(minuscula, 0, tam -1 )){
        printf("Sim\n");
    }else{
        printf("Não\n");
    }
}
int main(){
    char *minuscula = calloc(100,sizeof(char));
    char *frase = calloc(100,sizeof(char));
    while(fgets(frase,100,stdin)){
        if(strlen(frase)>0){
            verificadorDePalindromo(frase, minuscula);
        }else{
            printf("Não\n");
        }
    }
    free(minuscula);
    free(frase);
    return 0;
}
