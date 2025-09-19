#include <stdio.h> 
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


void shakesort(int *vetor, int tamanho, int *comparacoes, int *trocas) {
    *comparacoes = 0;
    *trocas = 0;
    int inicio = 0, fim = tamanho - 1;
    while (inicio < fim) {
        int trocou = 0;
        for (int i = inicio; i < fim; i++) {
            (*comparacoes)++;
            if (vetor[i] > vetor[i + 1]) {
                int aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
                (*trocas)++;
                trocou = 1;
            }
        }
        fim--;
        for (int i = fim; i > inicio; i--) {
            (*comparacoes)++;
            if (vetor[i] < vetor[i - 1]) {
                int aux = vetor[i];
                vetor[i] = vetor[i - 1];
                vetor[i - 1] = aux;
                (*trocas)++;
                trocou = 1;
            }
        }
        inicio++;
    }
}


int contador_palavras(const char *str) {
    int nome = 0;
    for (int i = 0; str[i] != '-' && str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            nome++;
        }
    }
    return nome;
}
void imprimir(const char* grupo, int tamanho, int* tamanho_nomes, int comparacoes, int trocas){
    printf("%s - [", grupo);
    for(int i = 0; i < tamanho; i++) {
        printf("%d%s", tamanho_nomes[i], (i < tamanho-1) ? ", " : "");
    }
    printf("]\n");
    printf("Comparações: %d, Trocas: %d\n", comparacoes, trocas);
}

int main() {
    int USP[75001], EXTERNA[75001];
    int nu = 0, ne = 0;
    char str[150];

    while (fgets(str, sizeof(str), stdin)) {
        int len = (int)strlen(str);
        if (len > 0 && str[len - 1] == '\n') str[len - 1] = '\0';
        int numero = contador_palavras(str);
        int last = len - 2;
        while (last >= 0 && (str[last] == ' ' || str[last] == '\t')) last--;
        if (last >= 0 && (str[last] == 'p' || str[last] == 'P')) {
            USP[nu++] = numero;
        } else {
            EXTERNA[ne++] = numero;
        }
    }
    int comp_usp = 0, troc_usp = 0;
    int comp_ext = 0, troc_ext = 0;
    shakesort(USP, nu, &comp_usp, &troc_usp);
    imprimir("USP", nu, USP, comp_usp, troc_usp);
    printf("\n");
    shakesort(EXTERNA, ne, &comp_ext, &troc_ext);
    imprimir("Externa", ne, EXTERNA, comp_ext, troc_ext);
    return 0;
}


// Etapas: Pegar nomes --> contar caracteres --> salvar quantidade em um vetor
