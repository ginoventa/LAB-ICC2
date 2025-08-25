#include <stdio.h>
#include <ctype.h>
#include <string.h>

int eh_palindromo(const char *str) {
    int i = 0, j = strlen(str) - 1;

    while (i < j) {
        while (i < j && !isalnum(str[i])) i++;
        while (i < j && !isalnum(str[j])) j--;

        if (tolower(str[i]) != tolower(str[j]))
            return 0;

        i++;
        j--;
    }
    return 1;
}

int main() {
    char linha[1000];
    while (fgets(linha, sizeof(linha), stdin)) {
        linha[strcspn(linha, "\n")] = '\0'; // remove '\n'
        printf("%s\n", eh_palindromo(linha) ? "Sim" : "Não");
    }
    return 0;
}
