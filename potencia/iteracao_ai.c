#include <stdio.h>

int main() {
    int n, k;
    int resultado = 1;

    scanf("%d %d", &n, &k);

    if (n > 0 && n <= 99 && k >= 0 && k <= 1000000000) {
        for (int i = 0; i < k; i++) {
            resultado = (resultado * n) % 1000; // mantém só os últimos 3 dígitos
        }
        printf("%d\n", resultado);
    }

    return 0;
}
