#include <stdio.h> 
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void ordenacao(int *tamanho_nomes, int tamanho, int *comparacoes, int *trocas){
    int inicio = 0, fim = tamanho - 1;
    *trocas = 0;
    *comparacoes = 0;
    bool troca = true;
    while(troca){
        troca = false;
        for(int n = inicio; n < fim; n++ ){
            (*comparacoes)++;
            if (tamanho_nomes[n] > tamanho_nomes[n + 1]) {
                int aux = tamanho_nomes[n];
                tamanho_nomes[n] = tamanho_nomes[n+1];
                tamanho_nomes[n+1] = aux;
                troca = true;
                (*trocas)++;
            }
        }
        fim--;
        if (!troca) break;
        troca = false;
        for (int n = fim; n > inicio; n--) {
            (*comparacoes)++;
            if (tamanho_nomes[n] < tamanho_nomes[n - 1]) {
                int aux = tamanho_nomes[n];
                tamanho_nomes[n] = tamanho_nomes[n - 1];
                tamanho_nomes[n - 1] = aux;
                troca = true;
                (*trocas)++;
            }
        }
        inicio++;
    }
}

int contador_palavras(char *str){
    int nome = 0, i = 0; 
    while(str[i] != '-' && str[i] != '\0'){
        if(isalpha(str[i])){
            nome++; 
        }
        i++; 
    }
    return nome;
}   
void imprimir(const char* grupo, int tamanho, int* tamanho_nomes, int comparacoes, int trocas){
    printf("%s - [", grupo);
    for(int i = 0; i < tamanho; i++) {
        printf("%d%s", tamanho_nomes[i], (i < tamanho-1) ? ", " : "");
    }
    printf("]\n");
    printf("Comparações: %d, Trocas: %d\n\n", comparacoes, trocas);
}

int main(){
    int nu = 0, ne = 0;  
    int USP[200], EXTERNA[200]; 
    char str[200]; 

    while(fgets(str,200,stdin)){
        int numero = contador_palavras(str);
        if(str[strlen(str)-2]=='p' || str[strlen(str)-2]=='P'){
            USP[nu] = numero; 
            nu++; 
        }else{
            EXTERNA[ne] = numero; 
            ne++; 
        }
    }
    int comp_usp = 0, troc_usp = 0;
    int comp_ext = 0, troc_ext = 0;
    ordenacao(USP, nu, &comp_usp, &troc_usp);
    imprimir("USP", nu, USP, comp_usp, troc_usp);
    ordenacao(EXTERNA, ne, &comp_ext, &troc_ext);
    imprimir("Externa", ne, EXTERNA, comp_ext, troc_ext);
    return 0; 
}


// Etapas: Pegar nomes --> contar caracteres --> salvar quantidade em um vetor
