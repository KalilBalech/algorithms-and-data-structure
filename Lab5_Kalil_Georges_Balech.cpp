#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Kalil Georges Balech */
/* Turma 3 */
/* */
/* Exercício 5: PERT */
/* Programa compilado com CodeBlocks 17.12 */

#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2

int correspondencia(char);
char correspondencia_inversa(int);
void imprimir_grafo(int[][54]);
void imprimir_descricoes(char[][31]);
void profundidade_ciclo(int[][54]);
void visitaP_ciclo(int[][54], int, int[]);
void profundidade_ordem_topologica(int[][54]);
void visitaP_ordem_topologica(int[][54], int, int[]);
int coluna_ordem_topologica_organizada(int[][54], int);
int vertice_existente(int[][54], int);

int ciclico=0, ordem_topologica[54], caminho_ciclico[54], int_global=0;

int main(){

    //INICIALIZAÇÃO DAS VARIÁVEIS
    FILE *filein, *fileout;
    filein = fopen("entrada5.txt", "r");
    fileout = fopen("Lab5_Kalil_Georges_Balech.txt", "w");

    int grafo[54][54], int_tarefa, int_tarefa_precedente, i, j, duracao, booleana, numero_de_vertices, ordem_topologica_organizada[3][54], /*cursor_ordem_topologica_organizada=1,*/ maior_tempo, tempo_critico, caminho_critico[54]={0}, vertice_critico, numero_de_vertices_criticos, indice_lider_caminho_ciclico;
    char descricoes[54][31], pular_linha[62], tarefa, descricao[31], tarefa_precedente;

    //DESCONSIDERA AS LINHAS INICIAIS DA ENTRADA
    for(i=0; i<7; i++){
        fgets(pular_linha, 62, filein);
    }

    for(i=0;i<54;i++){
        for(j=0; j<54; j++){
            grafo[i][j]=-1;
        }
        ordem_topologica_organizada[0][i]=-1;
    }

    //ESCREVE AS LINHAS INICIAIS NO ARQUIVO DE SAÍDA

    fprintf(fileout, "Laboratório 5: PERT\nKalil Georges Balech\nSCOOBY-DOO, CADE VOCE, MEU FIIIILHO?\nIABADABADÚÚÚÚÚÚÚÚ\nLAB 5 DIFICIL CABULOOOOSO\n------------------------------------------------------------\n");

    //LEITURA DOS VÉRTICES DO GRAFO E CONSTRUÇÃO DA MATRIZ DE ADJACÊNCIAS
    fscanf(filein, " %c ", &tarefa);

    while(tarefa != '-'){

        int_tarefa = correspondencia(tarefa);

        fgets(descricao, 31, filein);
        strcpy(descricoes[int_tarefa], descricao);

        fscanf(filein, " %d", &duracao);
        fscanf(filein, " %c", &tarefa_precedente);

        while(tarefa_precedente != '\n'){
            if(tarefa_precedente == '.'){
                grafo[0][int_tarefa] = duracao;
            }
            else{
                if(tarefa_precedente != ','){
                    int_tarefa_precedente = correspondencia(tarefa_precedente);
                    grafo[int_tarefa_precedente][int_tarefa] = duracao;
                }
            }
            fscanf(filein, "%c", &tarefa_precedente);
        }
        fscanf(filein, " %c ", &tarefa);
    }
    //CRIA UM RALO ÚNICO PARA O GRAFO EM VÉRTICE 53

    for(i=0, booleana=0; i<54; i++, booleana=0){
        for(j=0; j<54 && booleana==0;j++){
            if(grafo[i][j]!=-1){
                // LINHA I APONTA PARA ALGUEM
                booleana=1;
            }
        }
        if(booleana==0){
            //Ele não aponta para ninguém
            for(j=0; j<54; j++){
                if(grafo[j][i]!=-1){
                    booleana=1;
                }
            }
            if(booleana==1){
                //tem alguem apontando para ele
                grafo[i][53]=0;
            }
        }
    }

    grafo[53][53]=-1;

    // VERIFICAÇÃO DA EXISTÊCIA DE CICLOS
    profundidade_ciclo(grafo);

    // CASO NÃO HAJA CICLOS

    // ORDENAÇÃO TOPOLÓGICA DO GRAFO
    if(ciclico==0){
        profundidade_ordem_topologica(grafo);
        fprintf(fileout, "\n");

        for(i=0;i<54; i++){
            if(ordem_topologica[i]==0){
                numero_de_vertices = 54-i; // numero de vertices, contando com o vertice ralo e o vertice fonte
                ordem_topologica_organizada[0][0]=0;
                ordem_topologica_organizada[0][numero_de_vertices-1]=53;
                fprintf(fileout, "UMA ORDENACAO TOPOLOGICA:\n\n");
                for(j=i+1;j<53; j++){
                    fprintf(fileout, "%c ", correspondencia_inversa(ordem_topologica[j]));
                    ordem_topologica_organizada[0][j-i]=ordem_topologica[j];
                }
                fprintf(fileout, "\n\n------------------------------------------------------------");
                break;
            }
        }

        // INÍCIO DO CÁLCULO DO CAMINHO CRÍTICO E DO TEMPO MÍNIMO

        // VERIFICAÇÃO E REGISTRO DE DURAÇÃO DOS VÉRTICES FONTES DO GRAFO

        for(i=0; i<54; i++){
            ordem_topologica_organizada[1][i]=-1;
        }

        for(i=0; i<54; i++){
            if(grafo[0][i]!=-1){
                //cursor_ordem_topologica_organizada++;
                duracao=grafo[0][i];
                for(j=0; j<=numero_de_vertices; j++){
                    if(ordem_topologica_organizada[0][j]==i){
                        ordem_topologica_organizada[1][j]=0;
                        ordem_topologica_organizada[2][j]=duracao;
                    }
                }
            }
        }

        // TRATAMENTO SEQUENCIAL DOS PRÓXIMOS VÉRTICES, SEGUINDO A ORDEM TOPOLÓGICA

        //descobrir os 'i' que ainda nao foram preenchidos na matriz organizada
        for(i=0; i<numero_de_vertices; i++){
            if(ordem_topologica_organizada[1][i]==-1){
                int_tarefa = ordem_topologica_organizada[0][i]; // o cara da coluna i
                duracao=0;
                maior_tempo=0;
                tempo_critico=0;
                //descobrir os caras que mandam flecha p int_tarefa
                for(j=0; j<54; j++){
                    if(grafo[j][int_tarefa]!=-1){
                        duracao = grafo[j][int_tarefa];
                        maior_tempo = duracao + ordem_topologica_organizada[2][coluna_ordem_topologica_organizada(ordem_topologica_organizada, j)];
                        // se ele gera um caminho tempo critico maior, ele eh guardado
                        if(maior_tempo>tempo_critico){
                            tarefa_precedente = j;
                            tempo_critico = maior_tempo;
                        }
                    }
                }
                ordem_topologica_organizada[1][i]=tarefa_precedente;
                ordem_topologica_organizada[2][i]=tempo_critico;
            }
        }

        vertice_critico=ordem_topologica_organizada[1][numero_de_vertices-1];
        numero_de_vertices_criticos=0;

        while(vertice_critico!=0){

            numero_de_vertices_criticos++;
            caminho_critico[numero_de_vertices_criticos-1]=vertice_critico;

            i=coluna_ordem_topologica_organizada(ordem_topologica_organizada, vertice_critico);

            vertice_critico=ordem_topologica_organizada[1][i];

        }

        // ESCRITA NO ARQUIVO DE SAÍDA

        fprintf(fileout, "\n\nCAMINHO CRITICO:\n\nTAREFA        DESCRICAO           DURACAO\n\n");

        for(i=numero_de_vertices_criticos-1; i>=0; i--){

            vertice_critico = caminho_critico[i];

            j=0;

            duracao = grafo[j][vertice_critico];

            while(duracao==-1){
                j++;
                duracao=grafo[j][vertice_critico];
            }
            fprintf(fileout, "  %c   %-30s%3d\n", correspondencia_inversa(vertice_critico), descricoes[vertice_critico], duracao);
        }

        fprintf(fileout, "%39s\nTEMPO MINIMO PARA O PROJETO:%11d semanas", "----", ordem_topologica_organizada[2][numero_de_vertices-1]);

    }
    else{
        // CASO HAJA CICLOS
        //PARA DESCOBRIR O PRIMEIRO ELEMENTO DO CAMINHO CICLICO
        booleana = 1;

        for(i=0; i<53 && booleana==1; i++){
            for(j=i+1; j<54 && booleana==1; j++){
                if(caminho_ciclico[j]==-1){
                    break;
                }
                if(caminho_ciclico[i]==caminho_ciclico[j]){
                    indice_lider_caminho_ciclico=i;
                    booleana=0;
                }
            }
        }

        fprintf(fileout, "\nATENCAO! CAMINHO CICLICO EXISTENTE: %d ", caminho_ciclico[indice_lider_caminho_ciclico]);
        // printa os valores numericos do caminho ciclico entre dois numeros que se repetem no vetor
        for(i=indice_lider_caminho_ciclico+1; i<54; i++){
            if(caminho_ciclico[i]!=caminho_ciclico[indice_lider_caminho_ciclico]){
                fprintf(fileout, "%d ", caminho_ciclico[i]);
            }
            else{
                break;
            }
        }

        fprintf(fileout, "\n\n------------------------------------------------------------");

        fprintf(fileout, "\n\nIMPOSSIVEL BUSCAR O CAMINHO CRITICO!");

    }

    //TRATAMENTO FINAL DOS ARQUIVOS

    fclose(filein);
    fclose(fileout);

    return 0;
}
// FORNECE O INDICE DA COLUNA DA MATRIZ QUE ABRANGE A ORDEM TOPOLOGICA ORGANIZADA
int coluna_ordem_topologica_organizada(int ordem_topologica_organizada[][54], int u){

    int i;

    for(i=0; i<54; i++){
        if(ordem_topologica_organizada[0][i]==u){
            return i;
        }
    }

}
// REALIZA UMA BUSCA EM PROFUNDIDADE PARA VERIFICACAO DE EXISTENCIA DE CICLOS NO GRAFO
void profundidade_ciclo(int grafo[][54]){

    int cor[54];
    int u, j;

    for(u=0; u<54; u++){
        cor[u]=BRANCO;
        caminho_ciclico[u]=-1;
    }

    for(u=0; u<54 && ciclico==0; u++){
        // SÓ VISITA OS VERTICES QUE ESTAO NO GRAFO E QUE SAO BRANCOS
        if(vertice_existente(grafo, u) && cor[u]==BRANCO){
            if(ciclico==0){
                caminho_ciclico[int_global]=u;
                int_global++;

                visitaP_ciclo(grafo, u, cor);
            }
            else{
                break;
            }
        }
    }

}
// FUNCAO AUXILIAR PARA A BUSCA DE CICLOS NO GRAFO
void visitaP_ciclo(int grafo[][54], int u, int cor[54]){

    int i, j;

    cor[u]=AMARELO;

    for(i=0; i<54 && ciclico==0; i++){
        if(grafo[u][i]!=-1){
            if(cor[i]==AMARELO){
                caminho_ciclico[int_global]=i;
                int_global++;

                ciclico = 1;
                break;
            }
            else{
                if(cor[i]==BRANCO){
                    caminho_ciclico[int_global]=i;
                    int_global++;

                    visitaP_ciclo(grafo, i, cor);
                }
            }
        }
    }
    if(ciclico==0){
        cor[u] = VERMELHO;
        int_global--;
        caminho_ciclico[int_global]=-1;
    }
}
// REALIZA UMA BUSCA EM PROFUNDIDADE PARA A FORMAÇÃO DA ORDEM TOPOLÓGICA
void profundidade_ordem_topologica(int grafo[][54]){

    int cor[54];
    int u;

    for(u=0; u<54; u++){
        cor[u]=BRANCO;
        ordem_topologica[u]=-1;
    }

    for(u=0; u<54; u++){
        if(cor[u]==BRANCO){
            visitaP_ordem_topologica(grafo, u, cor);
        }
    }

}
// FUNCAO AUXILIAR PARA A FORMAÇÃO DA ORDEM TOPOLÓGICA
void visitaP_ordem_topologica(int grafo[][54], int u, int cor[54]){

    int i;

    cor[u]=AMARELO;

    for(i=0; i<54; i++){
        if(grafo[u][i]!=-1){
            if(cor[i]==BRANCO){
                visitaP_ordem_topologica(grafo, i, cor);
            }
        }
    }

    cor[u] = VERMELHO;

    for(i=53; i>=0; i--){
        if(ordem_topologica[i]==-1){
            ordem_topologica[i]=u;
            break;
        }
    }

}
// REALIZA A CORRESPONDENCIA ENTRE UMA LETRA E UM NUMERO, SEGUINDO A TABELA ASCII
int correspondencia(char a){

    int i=a;

    if(i<=90){
        return i-64;
    }
    else{
        return i-70;
    }

}
// REALIZA A CORRESPONDENCIA ENTRE UM NUMERO E UMA LETRA, SEGUINDO A TABELA ASCII
char correspondencia_inversa(int i){

    char a;

    if(i<=26){
        a = i + 64;
        return a;
    }
    else{
        a = i + 70;
        return a;
    }

}
// VERIFICA SE UM VERTICE EH EXISTENTE OU NAO
int vertice_existente(int grafo[][54], int i){

    //VERIFICAR SE ELE RECEBE SETA DE ALGUEM

    int j, recebe=0, manda=0;

    for(j=0; j<54; j++){
        if(grafo[j][i]!=-1){
            recebe = 1;
            break;
        }
    }
    if(recebe==0){
        // VERIFICAR SE MANDA SETA PRA ALGUEM
        for(j=0; j<54; j++){
            if(grafo[i][j]!=-1){
                manda = 1;
                break;
            }
        }
        if(manda==0){
            return 0;
        }
        else{
            return 1;
        }
    }
    else{
        return 1;
    }
}

// IMPRIME A MATRIZ DE ADJACENCIAS DO GRAFO
void imprimir_grafo(int grafo[][54]){

    int i, j;

    printf("   ");

    for(i=0; i<54; i++){
        printf("%3d", i);
    }

    printf("\n  ");

    for(i=0; i<163; i++){
        printf("-");
    }

    printf("\n");

    for(i=0; i<54; i++){
        printf("%2d|", i);
        for(j=0; j<54; j++){
            printf("%3d", grafo[i][j]);
        }
        printf("\n");
    }

}
// IMPRIME O VETOR DE DESCRICOES DA ATIVIDADE
void imprimir_descricoes(char descricoes[][31]){

    int i;

    for(i=1; i<52; i++){
        printf("\n%s", descricoes[i]);
    }
}
