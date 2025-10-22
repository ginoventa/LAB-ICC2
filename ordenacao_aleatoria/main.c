/*
Alunos: Chrystian Paniago Nantes (15635906) e Giovanna Nascimento Noventa (15637210)
Disciplina: Laboratório de Introdução à Ciência da Computação II (SCC0220)
Atividade: Tiro no Escuro (Entregável 5)
*/

#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Parâmetros do American Flag Sort
//
// RADIX_BITS = 10: processa 10 bits por vez (2^10 = 1024 buckets)
//   - tradicional byte-wise radix sort
//
// RADIX = 1024: número de buckets em cada passagem
//   - arrays count[], start[], end[], pos[] têm tamanho 1024
//
// RADIX_MASK = 0x3FF: máscara para pegar os 10 bits
//   - (valor >> shift) & RADIX_MASK extrai 1 byte

#define RADIX_BITS 10
#define RADIX (1u << RADIX_BITS)      // 1024
#define RADIX_MASK (RADIX - 1u)        // 0x3FF

// American flag sort (uma variação do radix sort no local)
static void afs_sort(int *a, int n, int shift){
    if(n <= 1 || shift < 0) return;

    int count[RADIX] = {0}; // Inicializa contadores dos buckets com zero
    // Histograma do grupo de dígitos atual
    for(int i = 0; i < n; i++){ // para cada elemento do array 
        int d = (a[i] >> shift) & RADIX_MASK; // extrai o dígito atual
        count[d]++; // incrementa o contador do bucket correspondente
    }

    // Calcula posições iniciais dos buckets
    int start[RADIX];
    start[0] = 0;
    for(int b = 1; b < RADIX; b++){ // comecando do bucket 1 até o RADIX-1
        start[b] = start[b - 1] + count[b - 1]; // posição inicial do bucket b = posição inicial do bucket anterior + tamanho do bucket anterior
    }
    // Fins dos buckets e posições de escrita atual
    int end[RADIX];
    int pos[RADIX];
    for(int b = 0; b < RADIX; b++){ // ajusta para todos os buckets
        end[b] = start[b] + count[b];
        pos[b] = start[b];
    }

    // Permuta elementos nos buckets corretos usando ciclos
    for(int b = 0; b < RADIX; b++){
        while(pos[b] < end[b]){ // enquanto não preencheu o bucket b
            int i = pos[b]; 
            int d = (a[i] >> shift) & RADIX_MASK; // dígito do elemento na posição i
            if(d == b){ // já está no bucket correto
                pos[b]++;
            } else { // troca com o elemento que está na posição correta do bucket d
                int t = pos[d];
                int tmp = a[t];
                a[t] = a[i];
                a[i] = tmp;
                pos[d]++;
            }
        }
    }

    // Recursão nos buckets para o próximo grupo de dígitos
    // Se houver mais dígitos a serem processados
    int next_shift = shift - RADIX_BITS; 
    if(next_shift >= 0){
        for(int b = 0; b < RADIX; b++){
            int sz = end[b] - start[b]; // sz = tamanho do bucket b
            if(sz > 1){
                afs_sort(a + start[b], sz, next_shift);
            }
        }
    }
}

void radix_sort(int *vetor, int n){
    // Encontra o máximo valor para saber por onde começar
    int max = 0;
    for(int i = 0; i < n; i++){
        if(vetor[i] > max) max = vetor[i];
    }
    if(max == 0) return;
    
    // Calcula em qual posição de bits começar
    // Exemplo: max = ~20 bits
    // Com RADIX_BITS=11, começamos em shift=11 (depois fazemos shift-=11)
    int shift = 0;
    while((max >> shift) > 0) shift += RADIX_BITS;
    shift -= RADIX_BITS; // volta para o último shift válido
    
    afs_sort(vetor, n, shift);
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


void shell_sort(int *vetor, int n){
    for(int gap = n / 2; gap > 0; gap /= 2){
        for(int i = gap; i < n; i++){
            int temp = vetor[i];
            int j;
            for(j = i; j >= gap && vetor[j - gap] > temp; j -= gap){
                vetor[j] = vetor[j - gap];
            }
            vetor[j] = temp;
        }
    }
}

void gerar_vetor(char* tipo_vetor, int* vetor, int n, int* seed) {
    if (strcmp(tipo_vetor, "sorted") == 0) {
        for (int i = 1; i <= n; i++){
            vetor[i-1] = i;
        }
        return;
    }
    if (strcmp(tipo_vetor, "reverse") == 0) {
        for (int i = 1; i <= n; i++){
            vetor[i-1] = n + 1 - i; // 100 + 1 - 1 = 100, 100 + 1 - 2= 
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        vetor[i] = get_random(seed, n);
    }
}

void vetor_sort(int *vetor, int n, int sel){
    // Implementação do algoritmo de ordenação (Heap Sort, Shell Sort, Quick Sort)
    switch (sel){
        case 1:
            radix_sort(vetor,n);
            break;
        case 2:
            shell_sort(vetor, n);
            break;
        case 3:
            quick_sort(vetor, n);   
            break;
    }
}

void main(){
    int n;
    scanf("%d", &n);
    char tipo_vetor[10];
    scanf("%9s", tipo_vetor); //sorted, random, reverse
    int tipo_ordenacao;
    scanf("%d", &tipo_ordenacao);

    int *vetor = (int*)malloc(n*sizeof(int));   
    
    int seed = 12345; 
    gerar_vetor(tipo_vetor, vetor, n, &seed);
    vetor_sort(vetor, n, tipo_ordenacao); 

    init_crc32();
    uint32_t saida = crc32(0, vetor, n*sizeof(int));
    printf("%08X", saida);
    free(vetor);
}