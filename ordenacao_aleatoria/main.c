#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void merge(int *vetor, int left, int mid, int right, int *aux){
    int i = left, j = mid + 1, k = left;
    while(i <= mid && j <= right){
        if (vetor[i] <= vetor[j]){
            aux[k++] = vetor[i++];
        } else {
            aux[k++] = vetor[j++];
        }
    }
    while(i <= mid){
         aux[k++] = vetor[i++]; 
    }
    while(j <= right){ 
        aux[k++] = vetor[j++]; 
    }
}

void mpass(int* vetor, int n, int pairSize, int* aux){
    int i = 0;
    while(i <= n - 2*pairSize){
        merge(vetor, i, i+pairSize-1, i+2*pairSize-1, aux);
        i = i + 2*pairSize;
    }
    if(i + pairSize - 1 < n){
        merge(vetor, i, i+pairSize-1, n-1, aux);
    } else {
        for(int j = i; j < n; j++){
            aux[j] = vetor[j];
        }
    }
}

int* merge_sort(int *vetor, int n){
    if (n <= 1) return vetor;
    int *aux = (int*)malloc(n * sizeof(int));  // heap em vez de VLA
    if (!aux) return vetor;
    
    int pairSize = 1;
    while(pairSize < n){
        mpass(vetor, n, pairSize, aux);
        pairSize = 2*pairSize;
        mpass(aux, n, pairSize, vetor);
        pairSize = 2*pairSize;
    }
    free(aux);
    return vetor;
}

void quicksort_rec(int vetor[], int l, int r){
    int i = l, j = r;
    int aux, x = vetor[(l+r)/2];
    do{
        while (vetor[i] < x) i++;
        while (vetor[j] > x) j--;
        if(i <= j){
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++; j--;
        }
    }while(i <= j);
    if(l < j) quicksort_rec(vetor, l, j);
    if(i < r) quicksort_rec(vetor, i, r);
}

int* quick_sort(int *vetor, int n){
    if(n > 1) quicksort_rec(vetor, 0, n-1);
    return vetor;
}


void heapify(int *vetor, int n, int i){
    int x = vetor[i];
    int j = 2*i + 1;             
    while (j < n){
        if (j + 1 < n && vetor[j] < vetor[j + 1]) j++; 
        if (x >= vetor[j]) break;
        vetor[i] = vetor[j];
        i = j;
        j = 2*i + 1;
    }
    vetor[i] = x;
}

int* ordenacaoHeapsort(int *vetor, int tamanhoVetor){
    int w;
    for(int L = tamanhoVetor/2 -1 ; L >= 0; L--){
        heapify(vetor, tamanhoVetor , L);
    }

    for(int R = tamanhoVetor - 1; R > 0; --R){
        w = vetor[0];
        vetor[0] = vetor[R];
        vetor[R] = w;
        heapify(vetor, R , 0);
    }
    return vetor;
}
void gerar_vetor(char* tipo_vetor, int* vetor, int n, int* seed) {
    if (!vetor || n <= 0) return;
    if (tipo_vetor && strcmp(tipo_vetor, "sorted") == 0) {
        for (int i = 0; i < n; i++) vetor[i] = i;
        return;
    }
    if (tipo_vetor && strcmp(tipo_vetor, "reverse") == 0) {
        for (int i = 0; i < n; i++) vetor[i] = n - 1 - i;
            for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]); 
    }return;
    }
    for (int i = 0; i < n; i++) {
        vetor[i] = get_random(seed, n);
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", vetor[i]); 
    }
}
int main(void){
    int n = 10;
    scanf("%d", &n);
    char tipo_vetor[10];
    scanf("%9s", tipo_vetor);
    int tipo_ordenacao;
    scanf("%d", &tipo_ordenacao);

    int seed = 12345; 
    int* vetor = (int*)malloc(sizeof(int) * (n > 0 ? n : 1));
    if (!vetor) return 0;

    gerar_vetor(tipo_vetor, vetor, n, &seed);

    switch(tipo_ordenacao){
        case 1:
            vetor = merge_sort(vetor, n);
            break;
        case 2:
            vetor = quick_sort(vetor, n);
            break;
        case 3:
            vetor = quick_sort(vetor, n);
            break;
    }
    init_crc32();
    uint32_t saida = crc32(0, vetor, (size_t)n * sizeof(int));
    printf("%08X\n", saida);
    free(vetor);
    return 0;
}