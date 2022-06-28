#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char predio[11];
//typedef struct predio_com_correspondecia predio_com_correspondecia;
//typedef predio_com_correspondecia* ponteiro;

void imprimir_grafo(int [][150], int);
void imprimir_predios(predio[150]);

/*struct predio_com_correspondecia{
    predio nome;
    int correspondencia;
    ponteiro prox;
};*/

int main(){

    int grafo[150][150];

    // tratamento inicial dos arquivos
    FILE *filein, *fileout;

    filein = fopen("entrada6.txt", "r");
    fileout = fopen("Lab6_Kalil_Georges_Balech.txt", "w");


    // ignorando linhas iniciais da entrada e criando linhas iniciais da saida
    char pular_linha[72];

    for(int i=0; i<6; i++){
        fgets(pular_linha, 72, filein);
    }

    fprintf(fileout, "ULTIMO LAAAB\nFEH NO PAI QUE O LAB SAI\nLAB DOS GURI\n24 EH BIXO CABULOOOSO\n---------------------------------------\nOrdem de selecao pelo algoritmo\n---------------------------------------\n");

    // registrando os dados da entrada
    // os predios registrados ficam numa lista encadeada

    int custo, numero_de_predios=0, primeiro_correspondencia, segundo_correspondencia, existe;
    predio primeiro, segundo, primeiro_anterior, segundo_anterior;
    //ponteiro predios;

    predio correspondendia_predio_inteiro[150];

    for(int i=0; i<150; i++){
        strcpy(correspondendia_predio_inteiro[i], "##########");
    }

    /*predios = (predio_com_correspondecia*) malloc(sizeof(predio_com_correspondecia));
    strcpy(predios->nome, "noh lider");
    numero_de_predios++;
    predios->correspondencia = numero_de_predios;*/

    fscanf(filein, "%s ", primeiro);
    numero_de_predios++;
    /*predios->prox = (predio_com_correspondecia*) malloc(sizeof(predio_com_correspondecia));
    strcpy(predios->prox->nome, primeiro);
    numero_de_predios++;
    predios->prox->correspondencia = numero_de_predios;*/

    fscanf(filein, "%s", segundo);
    numero_de_predios++;
    /*predios->prox->prox = (predio_com_correspondecia*) malloc(sizeof(predio_com_correspondecia));
    strcpy(predios->prox->prox->nome, segundo);
    numero_de_predios++;
    predios->prox->prox->correspondencia = numero_de_predios;

    predios->prox->prox->prox = NULL;*/

    fscanf(filein, "%d ", &custo);

    strcpy(primeiro_anterior, "----------");
    strcpy(segundo_anterior, "----------");

    while(strcmp(primeiro, primeiro_anterior)!=0 || strcmp(segundo, segundo_anterior)!=0){

        strcpy(primeiro_anterior, primeiro);
        strcpy(segundo_anterior, segundo);

        // verificacao do registro previo do primeiro predio
        for(int i=0, existe=0; i<150 && existe==0 && strcmp(correspondendia_predio_inteiro[i], "##########")!=0; i++){
            if(strcmp(correspondendia_predio_inteiro[i], primeiro)==0){
                existe = 1;
                primeiro_correspondencia = i;
            }
        }
        if(existe==0){
            numero_de_predios++;
            for(int i=0; i<150; i++){
                if(strcmp(correspondendia_predio_inteiro[i], "##########")==0){
                    strcpy(correspondendia_predio_inteiro[i], primeiro);
                    primeiro_correspondencia = i;
                    break;
                }
            }
        }
        /*for(ponteiro p=predios, existe= false; p->prox!=NULL && !existe; p = p->prox){
            if(strcmp(p->prox->nome, primeiro)==0){
                existe = !existe;
                primeiro_correspondencia = p->prox->correspondencia;
            }
        }
        if(!existe){
            for(ponteiro p = predios; p->prox!=NULL; p = p->prox);
            p->prox = (predio_com_correspondecia*) malloc (sizeof(predio_com_correspondecia));
            strcpy(p->prox->nome, primeiro);
            numero_de_predios++;
            p->prox->correspondencia = numero_de_predios;
            primeiro_correspondencia = numero_de_predios;
            p->prox->prox = NULL;
        }*/

        // verificacao do registro do segundo
        for(int i=0, existe=false; i<150 && existe==0 && strcmp(correspondendia_predio_inteiro[i], "##########")!=0; i++){
            if(strcmp(correspondendia_predio_inteiro[i], segundo)==0){
                segundo_correspondencia = i;
                existe = 1;
            }
        }
        if(existe==0){
            numero_de_predios++;
            for(int i=0; i<150; i++){
                if(strcmp(correspondendia_predio_inteiro[i], "##########")==0){
                    strcpy(correspondendia_predio_inteiro[i], segundo);
                    segundo_correspondencia = i;
                    break;
                }
            }
        }
        /*for(ponteiro p=predios, existe= false; p->prox!=NULL && !existe; p = p->prox){
            if(strcmp(p->prox->nome, primeiro)==0){
                existe = !existe;
                segundo_correspondencia = p->prox->correspondencia;
            }
        }

        if(!existe){
            for(ponteiro p = predios; p->prox!=NULL; p = p->prox);
            p->prox = (predio_com_correspondecia*) malloc (sizeof(predio_com_correspondecia));
            strcpy(p->prox->nome, primeiro);
            numero_de_predios++;
            p->prox->correspondencia = numero_de_predios;
            segundo_correspondencia = numero_de_predios;
            p->prox->prox = NULL;
        }*/

        // registrando na matriz de adjacencias

        grafo[primeiro_correspondencia][segundo_correspondencia] = custo;
        grafo[segundo_correspondencia][primeiro_correspondencia] = custo;

        fscanf(filein, "%s ", primeiro);
        fscanf(filein, "%s", segundo);
        fscanf(filein, "%d ", &custo);

    }

    imprimir_grafo(grafo, numero_de_predios);
    printf("\n");
    imprimir_predios(correspondendia_predio_inteiro);

    fclose(filein);
    fclose(fileout);

    /*filein = fopen("entrada6.txt", "r");

    for(int i=0; i<6; i++){
        fgets(pular_linha, 72, filein);
    }

    // registro dos dados da entrada, encontrando um numero como correspondencia e armazenando numa matriz de adjacenia
    predio correspondendia_predio_inteiro[150];

    for(int i=0; i<150; i++){
        strcpy(correspondendia_predio_inteiro[i], "##########");
    }

    for(int primeira_correspondencia, int segunda_correspondencia, bool existe;;){
        // lendo os predios
        fscanf(filein, "%s ", primeiro);
        fscanf(filein, "%s", segundo);

        // verificando se o primeiro predio ja foi registrado e garantindo seu registro
        for(int i=0, existe=false; i<150 && !existe && strcmp(correspondendia_predio_inteiro[i], "##########")!=0; i++){
            if(strcmp(correspondendia_predio_inteiro[i], primeiro)==0){
                existe = true;
                primeira_correspondencia = i;
            }
        }
        if(!existe){
            for(int i=0; i<150; i++){
                if(strcmp(correspondendia_predio_inteiro[i], "##########")==0){
                    strcpy(correspondendia_predio_inteiro[i], primeiro);
                    primeira_correspondencia = i;
                    break;
                }
            }
        }

        // verificando se o segundo predio ja foi registrado e garantindo seu registro
        for(int i=0, existe=false; i<150 && !existe && strcmp(correspondendia_predio_inteiro[i], "##########")!=0; i++){
            if(strcmp(correspondendia_predio_inteiro[i], segundo)==0){
                segunda_correspondencia = i;
                existe = true;
            }
        }
        if(!existe){
            for(int i=0; i<150; i++){
                if(strcmp(correspondendia_predio_inteiro[i], "##########")==0){
                    strcpy(correspondendia_predio_inteiro[i], segundo);
                    segunda_correspondencia = i;
                    break;
                }
            }
        }

        // registrando na matriz de adjacencia a ligacao nao direcional


    }*/


    return 0;
}

void imprimir_grafo(int grafo[][150], int numero_de_predios){

    int i, j;

    printf("    ");

    for(i=0; i<=numero_de_predios; i++){
        printf("%3d", i);
    }

    printf("\n  ");

    for(i=0; i<3*numero_de_predios; i++){
        printf("-");
    }

    printf("\n");

    for(i=0; i<=numero_de_predios; i++){
        printf("%3d|", i);
        for(j=0; j<=numero_de_predios; j++){
            printf("%3d", grafo[i][j]);
        }
        printf("\n");
    }

}

void imprimir_predios(predio correspondencia_predio_inteiro[150]){

    for(int i=0; strcmp(correspondencia_predio_inteiro[i], "##########")!=0; i++){
        printf("%d %s\n", i, correspondencia_predio_inteiro[i]);
    }

}
