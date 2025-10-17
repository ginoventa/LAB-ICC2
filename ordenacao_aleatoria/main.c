#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void merge(int *vetor, int left, int mid, int right, int *aux){
    int i = left, j = mid + 1, k = left;
    while(i <= mid && j <= right){
        if(vetor[i]<vetor[j]){
            aux[k] = vetor[i];
            i++;
        }
        else{
            aux[k] = vetor[j];
            j++;
        }
        k = k + 1;
    }
    while(i <= mid){
        aux[k] = vetor[i];
        i++;
        k++;
    }
    while(j <= right){
        aux[k] = vetor[j];
        j++;
        k++;
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

void merge_sort(int* vetor, int n){
    int pairSize = 1;
    int *aux = (int*)malloc(n*sizeof(int));
    while(pairSize < n){
        mpass(vetor, n, pairSize, aux);
        pairSize = 2*pairSize;
        mpass(aux, n, pairSize, vetor);
        pairSize = 2*pairSize;
    }
    free(aux);
}
void quicksort_rec(int *vetor, int l, int r){
    int i = l, j = r;
    int aux, x = vetor[(l+r)/2];
    do{
        while (vetor[i] < x){
            i++;
        }
        while (vetor[j] > x){
            j--;
        }
        if(i<= j){
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++; 
            j--;
        }
    }while(i <= j);
    if(l<j){
        quicksort_rec(vetor,l,j);
    }
    if(i<r){
        quicksort_rec(vetor,i,r);
    }
}

void quick_sort(int *vetor, int n){
    quicksort_rec(vetor, 0, n-1);
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

void heap_sort(int *vetor, int tamanhoVetor){
    int aux;
    for(int L = tamanhoVetor/2 -1 ; L >= 0; L--){
        heapify(vetor, tamanhoVetor , L);
    }
    for(int R = tamanhoVetor - 1; R > 0; --R){
        aux = vetor[0];
        vetor[0] = vetor[R];
        vetor[R] = aux;
        heapify(vetor, R , 0);
    }
}

void gerar_vetor(char* tipo_vetor, int* vetor, int n, int* seed) {
    if (strcmp(tipo_vetor, "sorted") == 0) {
        for (int i = 0; i < n; i++){
            vetor[i] = i;
        }
        return;
    }
    if (strcmp(tipo_vetor, "reverse") == 0) {
        for (int i = 0; i < n; i++){
            vetor[i] = n - 1 - i;
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        vetor[i] = get_random(seed, n);
    }
}

void vetor_sort(int *vetor, int n, int sel){
    // Implementação do algoritmo de ordenação (Heap Sort, Merge Sort, Quick Sort)
    switch (sel){
        case 1:
            merge_sort(vetor, n);
            break;
        case 2:
            merge_sort(vetor, n);
            break;
        case 3:
            merge_sort(vetor, n);
            break;
    }
}

void main(){
    int n;
    scanf("%d", &n);
    char tipo_vetor[10];
    scanf("%9s ", tipo_vetor);
    int tipo_ordenacao;
    scanf("%d", &tipo_ordenacao);

    int seed = 12345; 
    int *vetor = (int*)malloc(n*sizeof(int));   
    
    gerar_vetor(tipo_vetor, vetor, n, &seed);
    vetor_sort(vetor, n, tipo_ordenacao); 

    init_crc32();
    uint32_t saida = crc32(0, vetor, n*sizeof(int));
    printf("%08X", saida);
    free(vetor);
}