#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE *filein;

    filein = fopen("entrada_teste.txt", "r");

    char pular_linha[12];

    strcpy(pular_linha, "oi");

    for(int i=0; i<6; i++){
        fgets(pular_linha, 12, filein);
        printf("%s", pular_linha);
    }

    //printf("fim");

    return 0;
}
