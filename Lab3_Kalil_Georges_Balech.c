#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Kalil Georges Balech */
/* Turma 3 */
/* */
/* Exercício 3: Agenda Eletronica */
/* Programa compilado com CodeBlocks 17.12 */

typedef struct atividade atividade;
typedef struct heapAgenda heapAgenda;

struct atividade{
    int importancia;
    char descricao[41];
};

struct heapAgenda{
    atividade *agenda;
    int numeroAtualDeAtividades, quantidadeMaximaDeAtividades;
};

void inicializar(heapAgenda*, int);
void insert(heapAgenda*, char[], int);
void construirHeap(atividade[], int);
void peneirar(atividade[], int, int);
void trocar(atividade*, atividade*);
atividade maximum(heapAgenda);
void removeMax(heapAgenda*);
void finalizar(heapAgenda*);
bool heapVazio(heapAgenda);
bool heapCheio(heapAgenda);


// -------------------------------------------------
int main(){

    FILE *filein, *fileout;
    heapAgenda heap;
    atividade ativ;

    int i;
    char linhaPulada[71], comando[8], descricaoDaAtividade[40];

    filein = fopen("entrada3.txt", "r");
    fileout = fopen("Lab3_Kalil_Georges_Balech.txt", "w");

    for(i=0; i<5; i++)
        fgets(linhaPulada, 71, filein);

    fscanf(filein, "%d ", &i);

    inicializar(&heap, i);

    for(i=0; i<3; i++){
        fgets(linhaPulada, 71, filein);
    }

    fprintf(fileout, "Agenda Eletronica\nLab 3\nHeap\nPrioridades\nXuxu beleza\n");

    fprintf(fileout, "--------------------------------------------------\nRESPOSTAS DAS CONSULTAS\n--------------------------------------------------\n");

    strcpy(comando, "vazio");

    while(strcmp(comando, "FIM")!=0){
        fscanf(filein, "%s ", comando);
        if(strcmp(comando, "NOVA")==0){
            if(heapCheio(heap)){
                fprintf(fileout, "ERRO     Agenda cheia. Impossivel inserir\n");
            }
            else{
                fscanf(filein, "%d ", &i);
                fgets(descricaoDaAtividade, 40, filein);
                insert(&heap, descricaoDaAtividade, i);
            }
        }
        else{
            if(strcmp(comando, "PROXIMA")==0){
                if(heapVazio(heap)){
                    fprintf(fileout, "AVISO    Nao ha tarefas na agenda  :-)\n");
                }
                else{
                    ativ = maximum(heap);
                    fprintf(fileout, "%2d       %s", ativ.importancia, ativ.descricao);
                    removeMax(&heap);
                }
            }
        }
    }

    fprintf(fileout, "\n--------------------------------------------------\nFICA PARA O DIA SEGUINTE\n--------------------------------------------------\n");

    if(!heapVazio(heap)){
        while(!heapVazio(heap)){
            ativ = maximum(heap);
            fprintf(fileout, "%2d       %s", ativ.importancia, ativ.descricao);
            removeMax(&heap);
        }
    }
    else{
        fprintf(fileout, "Agenda vazia! Nao restam tarefas para o dia seguinte.");
    }

    finalizar(&heap);

    fclose(filein);
    fclose(fileout);

    printf("\n\n");
    return 0;
}

// -------------------------------------------------
void inicializar(heapAgenda *h, int a){
    (*h).quantidadeMaximaDeAtividades = a;
    (*h).agenda = (atividade *) malloc ((a+1)*sizeof(atividade));
    h->numeroAtualDeAtividades = 0;
}


// -------------------------------------------------
void insert(heapAgenda *h, char desc[], int a){
    h->numeroAtualDeAtividades ++;
    strcpy(h->agenda[h->numeroAtualDeAtividades].descricao, desc);
    h->agenda[h->numeroAtualDeAtividades].importancia = a;
    construirHeap(h->agenda, h->numeroAtualDeAtividades);
}


// -------------------------------------------------
void construirHeap(atividade agend[], int n){

    int i;

    for(i=(n/2); i>=1; i--)
        peneirar(agend, n, i);

}


// -------------------------------------------------
void peneirar(atividade agend[], int n, int i){
     int esquerda = 2*i, direita = 2*i+1, maior = i;

     if(esquerda<=n && agend[esquerda].importancia> agend[maior].importancia)
        maior = esquerda;
     if(direita<=n && agend[direita].importancia>agend[maior].importancia)
        maior = direita;
     if(maior!=i){
        trocar(&agend[i], &agend[maior]);
        peneirar(agend, n, maior);
     }
}


// -------------------------------------------------
void trocar(atividade *a, atividade *b){

    int auxint;
    char auxchar[40];

    auxint = a->importancia;
    strcpy(auxchar, a->descricao);

    a->importancia = b->importancia;
    strcpy(a->descricao, b->descricao);
    b->importancia = auxint;
    strcpy(b->descricao, auxchar);
}


// -------------------------------------------------
atividade maximum(heapAgenda h){
    atividade ativ;
    strcpy(ativ.descricao, h.agenda[1].descricao);
    ativ.importancia = h.agenda[1].importancia;

    return ativ;
}


// -------------------------------------------------
void removeMax(heapAgenda *h){

    h->agenda[1].importancia = h->agenda[h->numeroAtualDeAtividades].importancia;
    strcpy(h->agenda[1].descricao, h->agenda[h->numeroAtualDeAtividades].descricao);
    h->numeroAtualDeAtividades --;
    construirHeap(h->agenda, h->numeroAtualDeAtividades);
}


// -------------------------------------------------
void finalizar(heapAgenda *h){
    free(h->agenda);
}


// -------------------------------------------------
bool heapVazio(heapAgenda h){

    if(h.numeroAtualDeAtividades == 0)
        return true;
    else{
        return false;
    }
}


// -------------------------------------------------
bool heapCheio(heapAgenda h){

    if(h.numeroAtualDeAtividades == h.quantidadeMaximaDeAtividades)
        return true;
    else{
        return false;
    }

}


