#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Kalil Georges Balech */
/* Turma 3 */
/* */
/* Exercício 6: Fibra Ótica */
/* Programa compilado com CodeBlocks 17.12 */

typedef char predio[11];

void imprimir_grafo(int [][150], int);
void imprimir_predios(predio[150]);
void imprimir_subconjunto(predio[150], int);
int correspondencia(predio);
bool pertence_a_v(int);

predio correspondendia_predio_inteiro[150],  subconjunto_v[150];

int main(){

    int grafo[150][150]={0}, arvore_geradora_minima[150][150]={0}, processo_arvore_geradora_minima[4][150], ordem_crescente_de_custo[3][150];

    int aux, tempo=0, custo, custo_total=0, numero_de_predios=0, primeiro_correspondencia, segundo_correspondencia, existe_bool, i, j, k, menor_ligacao, proximo_vertice, vertice_anterior;
    predio primeiro, segundo, primeiro_anterior, segundo_anterior, correspondendia_predio_inteiro[150], subconjunto_u[150];
    char pular_linha[72];
    bool trocou;

    // tratamento inicial dos arquivos
    FILE *filein, *fileout;

    filein = fopen("entrada6.txt", "r");
    fileout = fopen("Lab6_Kalil_Georges_Balech.txt", "w");


    // ignorando linhas iniciais da entrada e criando linhas iniciais da saida

    for(i=0; i<6; i++){
        fgets(pular_linha, 72, filein);
    }

    fprintf(fileout, "ULTIMO LAAAB\nFEH NO PAI QUE O LAB SAI\nLAB DOS GURI\n24 EH BIXO CABULOOOSO\n---------------------------------------\nOrdem de selecao pelo algoritmo\n---------------------------------------\n");

    // registrando os dados da entrada

    for(i=0; i<150; i++){
        strcpy(correspondendia_predio_inteiro[i], "##########");
    }

    fscanf(filein, "%s ", primeiro);
    //numero_de_predios++;

    fscanf(filein, "%s ", segundo);
    //numero_de_predios++;

    fscanf(filein, "%d ", &custo);

    strcpy(primeiro_anterior, "##########");
    strcpy(segundo_anterior, "##########");

    while(strcmp(primeiro, primeiro_anterior)!=0 || strcmp(segundo, segundo_anterior)!=0){

        strcpy(primeiro_anterior, primeiro);
        strcpy(segundo_anterior, segundo);

        // verificacao do registro previo do primeiro predio
        for(i=0, existe_bool=0; i<150 && existe_bool==0 && strcmp(correspondendia_predio_inteiro[i], "##########")!=0; i++){
            if(strcmp(correspondendia_predio_inteiro[i], primeiro)==0){
                existe_bool = 1;
                primeiro_correspondencia = i;
            }
        }
        if(existe_bool==0){
            numero_de_predios++;
            for(i=0; i<150; i++){
                if(strcmp(correspondendia_predio_inteiro[i], "##########")==0){
                    strcpy(correspondendia_predio_inteiro[i], primeiro);
                    primeiro_correspondencia = i;
                    break;
                }
            }
        }

        // verificacao do registro do segundo
        for(i=0, existe_bool=0; i<150 && existe_bool==0 && strcmp(correspondendia_predio_inteiro[i], "##########")!=0; i++){
            if(strcmp(correspondendia_predio_inteiro[i], segundo)==0){
                segundo_correspondencia = i;
                existe_bool = 1;
            }
        }
        if(existe_bool==0){
            numero_de_predios++;
            for(i=0; i<150; i++){
                if(strcmp(correspondendia_predio_inteiro[i], "##########")==0){
                    strcpy(correspondendia_predio_inteiro[i], segundo);
                    segundo_correspondencia = i;
                    break;
                }
            }
        }

        // registrando na matriz de adjacencias

        grafo[primeiro_correspondencia][segundo_correspondencia] = custo;
        grafo[segundo_correspondencia][primeiro_correspondencia] = custo;

        fscanf(filein, "%s ", primeiro);
        fscanf(filein, "%s", segundo);
        fscanf(filein, "%d ", &custo);

    }

    //printf("numero de predios: %d\n", numero_de_predios);

    for(i=0; i<numero_de_predios; i++){
        processo_arvore_geradora_minima[0][i]=i;
    }
    for(i=numero_de_predios; i<150; i++){
        processo_arvore_geradora_minima[0][i]=-1;
    }
    for(i=0; i<150; i++){
        processo_arvore_geradora_minima[1][i]=-1;
        processo_arvore_geradora_minima[2][i]=-1;
        processo_arvore_geradora_minima[3][i]=-1;
    }

    // tratamento inicial dos subconjuntos

    for(i=0; i<150; i++){
        strcpy(subconjunto_u[i], "##########");
        strcpy(subconjunto_v[i], "##########");
    }

    strcpy(subconjunto_u[0], correspondendia_predio_inteiro[0]);

    for(i=1; strcmp(correspondendia_predio_inteiro[i], "##########")!=0; i++)
        strcpy(subconjunto_v[i], correspondendia_predio_inteiro[i]);

    /*printf("Subconjunto u inicial\n");
    imprimir_subconjunto(subconjunto_u, numero_de_predios);
    printf("Subconjuto v inicial\n");
    imprimir_subconjunto(subconjunto_v, numero_de_predios);*/


    // DESCOBRIDO A ARVORE GERADORA MINIMA

    // numero de transferencias do subconjunto v para o u
    for(i=0; i<numero_de_predios-1; i++){

        //printf("TRANSFERENCIA DE U PARA V NUMERO: %d\n", i+1);
        menor_ligacao = 1000;
        //printf("menor ligacao atualizada para %d\n", menor_ligacao);

        // analises dos vertices que pertencem ao conjunto u
        for(j=0; j<numero_de_predios; j++){

            // ver se j eh um cara valido                    // ESCOLHIDO UM CARA EM U
            if(strcmp(subconjunto_u[j], "##########")!=0){

                //printf("ANALISANDO %d\n", j);

                //int int_predio_u=correspondencia(subconjunto_u[j]);
                // verificacao de para onde os vertices de u apontam
                for(k=0; k<numero_de_predios ; k++){
                    if(grafo[j][k]!=0 && pertence_a_v(k) && grafo[j][k]<menor_ligacao){ // verificando se aponta para um cara de v que tem ligacao menor

                        //printf("MENOR PARA  %d\n", k);

                        menor_ligacao=grafo[j][k];
                        vertice_anterior = j;
                        proximo_vertice = k;

                        //printf("menor ligacao atualizada: vai de %d para %d com custo de %d\n", j, k, menor_ligacao);
                    }
                }
            }
        }

        arvore_geradora_minima[vertice_anterior][proximo_vertice]=menor_ligacao;
        arvore_geradora_minima[proximo_vertice][vertice_anterior]=menor_ligacao;
        //printf("arvore geradora minima atualizada para:\n");
        //imprimir_grafo(arvore_geradora_minima, numero_de_predios);


        processo_arvore_geradora_minima[1][tempo]=vertice_anterior;
        processo_arvore_geradora_minima[2][tempo]=proximo_vertice;
        processo_arvore_geradora_minima[3][tempo]=menor_ligacao;
        tempo++;
        custo_total = custo_total + menor_ligacao;


        strcpy(subconjunto_u[proximo_vertice], correspondendia_predio_inteiro[proximo_vertice]);
        strcpy(subconjunto_v[proximo_vertice], "##########");
        //printf("Subconjunto u atualizado para\n");
        //imprimir_subconjunto(subconjunto_u, numero_de_predios);
        //printf("Subconjuto v atualizado para\n");
        //imprimir_subconjunto(subconjunto_v, numero_de_predios);
    }


    //printf("%d\n", numero_de_predios);
    /*printf("matriz processo arv ger min:\n");
    for(i=0; i<4; i++){
        for(j=0; j<numero_de_predios; j++){
            printf("%3d", processo_arvore_geradora_minima[i][j]);
        }
        printf("\n");
    }*/
    //printf("\n");
    //imprimir_predios(correspondendia_predio_inteiro);

    for(i=0; i<numero_de_predios-1; i++){
        primeiro_correspondencia = processo_arvore_geradora_minima[1][i];
        segundo_correspondencia = processo_arvore_geradora_minima[2][i];
        custo = processo_arvore_geradora_minima[3][i];
        fprintf(fileout, "%-11s%-13s%d\n", correspondendia_predio_inteiro[primeiro_correspondencia], correspondendia_predio_inteiro[segundo_correspondencia], custo);
    }
    fprintf(fileout, "\nCusto total: %d\n", custo_total);
    fprintf(fileout, "\n---------------------------------------\nOrdem crescente de custos\n---------------------------------------\n");

    trocou = true;

    for(i=numero_de_predios-3; i>=0 && trocou; i--){
        trocou = false;
        for(j=0; j<=i; j++){
            if(processo_arvore_geradora_minima[3][j]>processo_arvore_geradora_minima[3][j+1]){
                aux = processo_arvore_geradora_minima[3][j];
                processo_arvore_geradora_minima[3][j]=processo_arvore_geradora_minima[3][j+1];
                processo_arvore_geradora_minima[3][j+1]=aux;

                aux = processo_arvore_geradora_minima[2][j];
                processo_arvore_geradora_minima[2][j]=processo_arvore_geradora_minima[2][j+1];
                processo_arvore_geradora_minima[2][j+1]=aux;

                aux = processo_arvore_geradora_minima[1][j];
                processo_arvore_geradora_minima[1][j]=processo_arvore_geradora_minima[1][j+1];
                processo_arvore_geradora_minima[1][j+1]=aux;

                trocou=true;
            }
        }
    }

    /*printf("matriz processo arv ger min:\n");
    for(i=0; i<4; i++){
        for(j=0; j<numero_de_predios; j++){
            printf("%3d", processo_arvore_geradora_minima[i][j]);
        }
        printf("\n");
    }*/

    for(i=0; i<numero_de_predios-1; i++){
        primeiro_correspondencia = processo_arvore_geradora_minima[1][i];
        segundo_correspondencia = processo_arvore_geradora_minima[2][i];
        custo = processo_arvore_geradora_minima[3][i];
        fprintf(fileout, "%-11s%-13s%d\n", correspondendia_predio_inteiro[primeiro_correspondencia], correspondendia_predio_inteiro[segundo_correspondencia], custo);
    }



    fclose(filein);
    fclose(fileout);


    return 0;
}

void imprimir_grafo(int grafo[][150], int numero_de_predios){

    int i, j;

    printf("    ");

    for(i=0; i<numero_de_predios; i++){
        printf("%3d", i);
    }

    printf("\n  ");

    for(i=0; i<3*numero_de_predios; i++){
        printf("-");
    }

    printf("\n");

    for(i=0; i<numero_de_predios; i++){
        printf("%3d|", i);
        for(j=0; j<numero_de_predios; j++){
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

void imprimir_subconjunto(predio subconjunto[150], int numero_de_predios){

    int i;

    for(i=0; i<numero_de_predios; i++){
        printf("%d  %s\n", i, subconjunto[i]);
    }

}

int correspondencia(predio nome){
    int i;

    for(i=0;i<150; i++){
        if(strcmp(correspondendia_predio_inteiro[i], nome)==0){
            return i;
        }
    }
}


bool pertence_a_v(int k){

    if(strcmp(subconjunto_v[k], "##########")!=0){
        return true;
    }
    else{
        return false;
    }

}


