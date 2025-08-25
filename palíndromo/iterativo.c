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
    Função: verificadorDePalindromo
    Objetivo: Após chamar a função modificadorDeString, começa a comparar a string a fim de verificar se ela é um palíndromo
    ou não. A partir do momento que identifica padrão que foge do padrão de um palíndromo, encerra a iteração. Após análise
    completa, retorna se a função é, ou não, um palíndromo. 
*/
void verificadorDePalindromo(char *frase, char *minuscula){
    minuscula = modificadorDeString(frase, minuscula);
    int tam = strlen(minuscula);
    int contador = 0;   

    for(int i = 0; i < tam/2; i++){
        if(minuscula[i] != minuscula[tam-i-1]){
            printf("Não\n");
            return;
        }
    }
    printf("Sim\n");

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
