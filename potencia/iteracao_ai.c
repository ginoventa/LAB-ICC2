#include <stdio.h>

int potencia_mod(int n, int k) {
    int resultado = 1;
    int base = n % 1000;

    while (k > 0) {
        if (k % 2 == 1) {             // se k é ímpar
            resultado = (resultado * base) % 1000;
        }
        base = (base * base) % 1000;  // eleva ao quadrado
        k /= 2;
    }
    return resultado;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int r = potencia_mod(n, k);

    // imprime sem zeros à esquerda
    printf("%d\n", r);

    return 0;
}
