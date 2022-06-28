#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Kalil Georges Balech */
/* Turma 3 */
/* */
/* Exercício 4: Ordenação */
/* Programa compilado com CodeBlocks 17.12 */

typedef char nome[52];
typedef nome* lista;

int contador=0;

int compara(nome, nome);
void merge_sort(lista, lista, int, int);
void merge_(lista, lista, int, int);
int encontrar_indice_pivo(int, int);
int particao(lista, int, int, nome);
void quick_sort(lista, int, int);

int main(){

    int i, p, quantidade_de_nomes, trocou;
    clock_t inicio, fim;
    float delta_t;
    lista lista_de_nomes, lista_auxiliar;
    nome nome_auxiliar;

// INICIALIZA OS ARQUIVOS
    FILE *filein, *fileout_bubble, *fileout_merge, *fileout_quick;

    filein = fopen("entrada4.txt", "r");
    fileout_bubble = fopen("Lab4_Kalil_Georges_Balech_bubble.txt", "w");

// LÊ A QUANTIDADE DE NOMES NA LISTA
    fscanf(filein, "%d ", &quantidade_de_nomes);

// ALOCA MEMÓRIA NOS VETORES E COLOCA OS NOMES NO VETOR lista_de_nomes
    lista_de_nomes = (nome*) malloc(quantidade_de_nomes*sizeof(nome));
    lista_auxiliar = (nome*) malloc(quantidade_de_nomes*sizeof(nome));

    for(i=0; i<quantidade_de_nomes; i++){
        fgets(lista_de_nomes[i], 52, filein);
    }

// INICIA A CONTAGEM DO RELÓGIO
    inicio = clock();

// ALGORITMO BUBBLE-SORT
    trocou=1;

    for(p=quantidade_de_nomes-2; p>=0 && trocou==1; p--){
        trocou=0;
        for(i=0; i<=p; i++){
            if(compara(lista_de_nomes[i], lista_de_nomes[i+1])>0){
                strcpy(nome_auxiliar, lista_de_nomes[i]);
                strcpy(lista_de_nomes[i], lista_de_nomes[i+1]);
                strcpy(lista_de_nomes[i+1], nome_auxiliar);
                trocou=1;
            }
        }
    }

// PARA O RELÓGIO
    fim = clock();
    delta_t = (fim-inicio)/(float) CLOCKS_PER_SEC;

// IMPRIME O ARQUIVO DE SAÍDA REFERENTE AO BUBBLE-SORT
    fprintf(fileout_bubble, "Algoritmo: Bubble-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\nTempo de execução: %.3f segundos\n\n-------------------------------------\n",quantidade_de_nomes, contador, delta_t);
    for(i=0; i<quantidade_de_nomes; i++){
        fprintf(fileout_bubble, "%s", lista_de_nomes[i]);
    }

// REALIZA O TRATAMENTO CORRETO DOS ARQUIVOS E DE ALGUNS DADOS
    fclose(filein);
    fclose(fileout_bubble);
    filein = fopen("entrada4.txt", "r");
    fileout_merge = fopen("Lab4_Kalil_Georges_Balech_merge.txt", "w");
    contador=0;

// LÊ A QUANTIDADE DE NOMES NA LISTA
    fscanf(filein, "%d ", &quantidade_de_nomes);

// COLOCA OS NOMES NO VETOR lista_de_nomes
    for(i=0; i<quantidade_de_nomes; i++){
        fgets(lista_de_nomes[i], 52, filein);
    }

// INICIA A CONTAGEM DO RELÓGIO
    inicio = clock();

// ALGORITMO MERGE-SORT
    merge_sort(lista_de_nomes, lista_auxiliar, 0, quantidade_de_nomes-1);

// PARA O RELÓGIO
    fim = clock();
    delta_t = (fim-inicio)/(float) CLOCKS_PER_SEC;

// IMPRIME O ARQUIVO DE SAÍDA REFERENTE AO MERGE-SORT
    fprintf(fileout_merge, "Algoritmo: Merge-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\nTempo de execução: %.3f segundos\n\n-------------------------------------\n",quantidade_de_nomes, contador, delta_t);
    for(i=0; i<quantidade_de_nomes; i++){
        fprintf(fileout_merge, "%s", lista_de_nomes[i]);
    }

// REALIZA O TRATAMENTO CORRETO DOS ARQUIVOS E DE ALGUNS DADOS
    fclose(filein);
    fclose(fileout_merge);
    free(lista_auxiliar);
    filein = fopen("entrada4.txt", "r");
    fileout_quick = fopen("Lab4_Kalil_Georges_Balech_quick.txt", "w");
    contador=0;

// LÊ A QUANTIDADE DE NOMES NA LISTA
    fscanf(filein, "%d ", &quantidade_de_nomes);

// COLOCA OS NOMES NO VETOR lista_de_nomes
    for(i=0; i<quantidade_de_nomes; i++){
        fgets(lista_de_nomes[i], 52, filein);
    }

// INICIA A CONTAGEM DO RELÓGIO
    inicio = clock();

// ALGORITMO QUICK-SORT
    quick_sort(lista_de_nomes, 0, quantidade_de_nomes-1);

// PARA O RELÓGIO
    fim = clock();
    delta_t = (fim-inicio)/(float) CLOCKS_PER_SEC;

// IMPRIME O ARQUIVO DE SAÍDA REFERENTE AO QUICK-SORT
    fprintf(fileout_quick, "Algoritmo: Quick-Sort\n\nTamanho da entrada: %d\nComparações feitas: %d\nTempo de execução: %.3f segundos\n\n-------------------------------------\n",quantidade_de_nomes, contador, delta_t);
    for(i=0; i<quantidade_de_nomes; i++){
        fprintf(fileout_quick, "%s", lista_de_nomes[i]);
    }

// REALIZA O TRATAMENTO CORRETO DOS ARQUIVOS E DE ALGUNS DADOS
    fclose(filein);
    fclose(fileout_quick);
    free(lista_de_nomes);

    return 0;
}

// -------------------------------------------------
int compara(nome a, nome b){

    contador++;
    return strcmp(a, b);
}

// -------------------------------------------------
void merge_sort(lista lista_de_nomes, lista lista_auxiliar, int i, int f){
    if(i<f){
        int m = (i+f)/2;
        merge_sort(lista_de_nomes, lista_auxiliar, i, m);
        merge_sort(lista_de_nomes, lista_auxiliar, m+1, f);
        merge_(lista_de_nomes, lista_auxiliar, i, f);
    }
}

// -------------------------------------------------
void merge_(lista lista_de_nomes, lista lista_auxiliar, int i, int f){
    int m=(i+f)/2, j;
    int iaux=i, ip1=i;
    int ip2=m+1;

    while(ip1<=m && ip2<=f){
        if(compara(lista_de_nomes[ip1], lista_de_nomes[ip2])<0){
            strcpy(lista_auxiliar[iaux], lista_de_nomes[ip1]);
            iaux++;
            ip1++;
        }
        else{
            strcpy(lista_auxiliar[iaux], lista_de_nomes[ip2]);
            iaux++;
            ip2++;
        }
    }
    while(ip1<=m){
        strcpy(lista_auxiliar[iaux], lista_de_nomes[ip1]);
        iaux++;
        ip1++;
    }
    while(ip2<=f){
        strcpy(lista_auxiliar[iaux], lista_de_nomes[ip2]);
        iaux++;
        ip2++;
    }
    for(j=i; j<=f; j++){
        strcpy(lista_de_nomes[j], lista_auxiliar[j]);
    }

}

// -------------------------------------------------
int encontrar_indice_pivo(int minimo, int maximo){
    return (minimo+maximo)/2;
}

// -------------------------------------------------
int particao(lista lista_de_nomes, int esquerda, int direita, nome pivo){

    nome nome_auxiliar;

    while(contador != -1){
        while(compara(lista_de_nomes[esquerda], pivo)<0){
            esquerda++;
        }
        while(compara(lista_de_nomes[direita], pivo)>0){
            direita--;
        }
        if(direita<=esquerda){
            break;
        }

        strcpy(nome_auxiliar,lista_de_nomes[esquerda]);
        strcpy(lista_de_nomes[esquerda], lista_de_nomes[direita]);
        strcpy(lista_de_nomes[direita], nome_auxiliar);
        esquerda++;
        direita--;
    }

    return direita;
}

// -------------------------------------------------
void quick_sort(lista lista_de_nomes, int minimo, int maximo){
    if(minimo>=maximo){
        return;
    }

    nome pivo;
    strcpy(pivo, lista_de_nomes[encontrar_indice_pivo(minimo, maximo)]);
    int p = particao(lista_de_nomes, minimo, maximo, pivo);
    quick_sort(lista_de_nomes, minimo, p);
    quick_sort(lista_de_nomes, p+1, maximo);
}
