#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

void ordenacaoBubblesort(char *vetor, int tamanhoVetor, int *comp, int *trocas)
{
    for (int i = 0; i < tamanhoVetor - 1; i++)
    {
        for (int j = 0; j < tamanhoVetor - 1 - i; j++)
        {
            (*comp)++;
            if (vetor[j] > vetor[j + 1])
            {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*trocas)++;
                trocou = 1;
            }
        }
    }
}
int contador_palavras(char *str)
{
    int nome = 0, i = 0;
    while (str[i] != '-' && str[i] != '\0')
    {
        if (isalpha(str[i]))
        {
            nome++;
        }
        i++;
    }
    return nome;
}
void imprimir(int tamanho, char *tamanho_nomes, int *comparacoes, int *trocas)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d%s", tamanho_nomes[i], (i < tamanho - 1) ? ", " : "");
    }
    printf("]\n");
    printf("Comparações: %d, Trocas: %d", *comparacoes, *trocas);
}

int main()
{
    int nu = 0, ne = 0;
    char USP[75000], EXTERNA[75000];
    char str[120];

    while (fgets(str, 120, stdin))
    {
        int numero = contador_palavras(str);
        if (tolower(str[strlen(str) - 2]) == 'p' || tolower(str[strlen(str) - 1]) == 'p')
        {
            USP[nu] = numero;
            nu++;
        }
        else
        {
            EXTERNA[ne] = numero;
            ne++;
        }
    }
    int comp = 0, troca = 0;
    ordenacaoBubblesort(USP, nu, &comp, &troca);
    printf("USP - [");
    imprimir(nu, USP, &comp, &troca);
    printf("\n\n");
    comp = 0, troca = 0;
    printf("Externa - [");
    ordenacaoBubblesort(EXTERNA, ne, &comp, &troca);
    imprimir(ne, EXTERNA, &comp, &troca);
    return 0;
}

// Etapas: Pegar nomes --> contar caracteres --> salvar quantidade em um vetor
