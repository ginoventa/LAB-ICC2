//Nome: Christyan Paniago Nantes — Nº USP: 15635906
//Nome: Giovanna Nascimento Noventa — Nº USP: 15637210
#include <stdio.h>
#include <string.h>
#include <stdbool.h>    

typedef enum{
    amarelo,
    azul,
    branco,
    preto,
    rosa,
    verde,
    vermelho
} cores;

typedef struct brinquedo{
    cores cor;
    float comprimento;
    float nota;
    int pos_original;
} brinquedo;

cores string_to_cor(char *cor_str){
    if (strcmp(cor_str, "amarelo") == 0) return amarelo;
    if (strcmp(cor_str, "azul") == 0) return azul;
    if (strcmp(cor_str, "branco") == 0) return branco;
    if (strcmp(cor_str, "preto") == 0) return preto;
    if (strcmp(cor_str, "rosa") == 0) return rosa;
    if (strcmp(cor_str, "verde") == 0) return verde;
    if (strcmp(cor_str, "vermelho") == 0) return vermelho;
    return -1; // valor inválido
}

bool compara_brinquedos(brinquedo a, brinquedo b){ // verifica se a deve vir antes de b
    if (a.cor != b.cor) return a.cor < b.cor;
    if (a.comprimento != b.comprimento) return a.comprimento < b.comprimento;
    if (a.nota != b.nota) return a.nota > b.nota;
    return a.pos_original < b.pos_original;
}

void bubble_sort(brinquedo *brinquedos, int n){
    for(int i = 0;i<n-1;i++){
        for (int j = 0;j<n-i-1;j++){
            if(!compara_brinquedos(brinquedos[j], brinquedos[j+1])){
                brinquedo temp = brinquedos[j];
                brinquedos[j] = brinquedos[j+1];
                brinquedos[j+1] = temp;
            }
        }
    }
}

void insertion_sort(brinquedo *a, int n){
    brinquedo b;
    int j = 0;
    for(int i = 1; i < n; i++){
        b = a[i];
        j = i;
        while(j > 0 && compara_brinquedos(b,a[j-1])){
            a[j] = a[j-1];
            j = j - 1;
        }
        a[j] = b;
    }
}

void merge(brinquedo *brinquedos, int left, int mid, int right, brinquedo *aux){
    int i = left, j = mid + 1, k = left;
    
    while(i <= mid && j <= right){
        if(compara_brinquedos(brinquedos[i], brinquedos[j])){
            aux[k] = brinquedos[i];
            i++;
        }
        else{
            aux[k] = brinquedos[j];
            j++;
        }
        k = k + 1;
    }
    while(i <= mid){
        aux[k] = brinquedos[i];
        i++;
        k++;
    }

    while(j <= right){
        aux[k] = brinquedos[j];
        j++;
        k++;
    }
}

void mpass(brinquedo* brinquedos, int n, int pairSize, brinquedo* aux){
    int i = 0;
    while(i <= n - 2*pairSize){
        merge(brinquedos, i, i+pairSize-1, i+2*pairSize-1, aux);
        i = i + 2*pairSize;
    }
    if(i + pairSize - 1 < n){
        merge(brinquedos, i, i+pairSize-1, n-1, aux);
    }
    else{
        for(int j = i; j < n; j++){
            aux[j] = brinquedos[j];
        }
    }
}
void merge_sort(brinquedo *brinquedos, int n){
    int pairSize = 1;
    brinquedo aux[n]; 
    while( pairSize < n ){
        mpass(brinquedos, n, pairSize, aux);
        pairSize = 2*pairSize;
        mpass(aux, n, pairSize, brinquedos);
        pairSize = 2*pairSize;
    }
}

void qsort(brinquedo vetor[], int l, int r){
    int i,j;
    brinquedo aux, x;
    i = l;
    j = r;
    x = vetor[(l+r)/2];
    do{
        while(compara_brinquedos(vetor[i], x)){
            i++;
        }
        while(compara_brinquedos(x, vetor[j])){
            j--;
        }
        if(i<=j){
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    }while(i<=j);
    if(l<j){
        qsort(vetor,l,j);
    }
    if(i<r){
        qsort(vetor,i,r);
    }
}

void quick_sort(brinquedo *brinquedos, int n){
        qsort(brinquedos,0,n-1);
}

void brinquedos_sort(brinquedo *brinquedos, int n, int sel){
    // Implementação do algoritmo de ordenação (Bubble Sort, Insertion Sort, Merge Sort, Quick Sort)
    switch (sel){
        case 1:
            // Bubble Sort
            bubble_sort(brinquedos, n);
            break;
        case 2:
            // Insertion Sort
            insertion_sort(brinquedos, n);
            break;
        case 3:
            // Merge Sort
            merge_sort(brinquedos, n);
            break;
        case 4:
            // Quick Sort
            quick_sort(brinquedos, n);
            break;
        default:
             break;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    brinquedo brinquedos[n];
    for (int i = 0; i < n; i++){
        char cor_str[20]; // buffer temporário para a string da cor
        scanf("%s %f %f", cor_str, &brinquedos[i].comprimento, &brinquedos[i].nota);
        brinquedos[i].cor = string_to_cor(cor_str);
        brinquedos[i].pos_original = i;
    }
    int sel;
    scanf("%d", &sel);
    brinquedos_sort(brinquedos, n, sel);

    for(int i = 0; i < n; i++){
       // printf("%d: %d %.2f %.2f\n", brinquedos[i].pos_original, brinquedos[i].cor, brinquedos[i].comprimento, brinquedos[i].nota);
        printf("%d;", brinquedos[i].pos_original);
    }
    return 0;
}