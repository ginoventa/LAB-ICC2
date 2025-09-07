#include <stdio.h>

// Exponenciação rápida modular
int mod_pow(int base, int exp, int mod) {
    int resultado = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            resultado = (resultado * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return resultado;
}

// Combina duas congruências usando CRT: x ≡ a (mod m), x ≡ b (mod n)
int crt(int a, int m, int b, int n) {
    for (int x = a; x < m * n; x += m) {
        if (x % n == b)
            return x;
    }
    return -1; // nunca deve acontecer
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    if (n <= 0 || n > 99 || k <= 0 || k > 1000000000) return 0;

    // Mod 8
    int r1;
    if (n % 2 == 0) {
        // potências pares de número par mod 8
        r1 = 0;
    } else {
        r1 = mod_pow(n, k, 8);
    }

    // Mod 125
    int r2;
    if (n % 5 == 0) {
        r2 = 0;
    } else {
        int exp = k % 100; // φ(125) = 100
        if (exp == 0) exp = 100;
        r2 = mod_pow(n, exp, 125);
    }

    // Combina usando CRT
    int resultado = crt(r1, 8, r2, 125);
    printf("%d\n", resultado);

    return 0;
}
