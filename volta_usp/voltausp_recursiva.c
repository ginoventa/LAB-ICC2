#include <stdio.h> 
#include <ctype.h>
#include <string.h>

int contador_palavras(char *str){
    int nome = 0, i = 0; 
    while(str[i] != '-' && str[i] != '\0'){
        if(isalpha(str[i])){
            nome++; 
        }
        i++; 
    }
    return nome;
}   
void imprimir(int nu, int ne, int* USP, int* EXTERNA){
    printf("USP - [");
    for(int i = 0; i < nu; i++) {
        printf("%d%s", USP[i], (i < nu-1) ? ", " : "");
    }
    printf("]\nExterna - [");
    for(int i = 0; i < ne; i++) {
        printf("%d%s", EXTERNA[i], (i < ne-1) ? ", " : "");
    }
    printf("]\n");
}

int main(){
    int nu = 0, ne = 0;  
    int USP[50], EXTERNA[50]; 
    char str[50]; 

    while(fgets(str,50,stdin)){
        int numero = contador_palavras(str);
        if(str[strlen(str)-2]=='p' || str[strlen(str)-2]=='P'){
            USP[nu] = numero; 
            nu++; 
        }else{
            EXTERNA[ne] = numero; 
            ne++; 
        }
    }
    imprimir(nu, ne, USP, EXTERNA);
    return 0; 
}
