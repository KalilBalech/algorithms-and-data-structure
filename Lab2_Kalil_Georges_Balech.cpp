#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Kalil Georges Balech */
/* Turma 3 */
/* */
/* Exercício 2: Índice de livro */
/* Programa compilado com CodeBlocks 17.12 */

typedef struct secao secao;
typedef secao *ponteiro;

FILE *filein, *fileout;
int foiParaOPai = 0, quantosIrmaos=0, indices[5]={0,0,0,0,0}, posicao=-1, livroCriado=0;

struct secao{
    char nomeSecao[21];
    ponteiro pai, idir, fesq;
};

void inicializarArquivos();
void criarRaiz(ponteiro*, char[21]);
ponteiro encontrar(char[21], ponteiro);
void inserirSub(char[21], ponteiro*);
void inserirSeguinte(char[21], ponteiro*);
void imprimirArvore(ponteiro);
void remover(ponteiro*, ponteiro*);
void transferirSub(ponteiro *, ponteiro *);
void transferirSeguinte(ponteiro *, ponteiro *);
void finalizarArquivos();

// -------------------------------------------------
int main(){

    int numeroDaLista=0;
    ponteiro raiz, p, q;
    raiz = (secao *) malloc (sizeof(secao));
    char comando[11], nome[21], inserirComo[11], inserirOnde[21], qualRemover[21], transferirComo[11], transferirOnde[21];

    inicializarArquivos();

    while(strcmp(comando, "FIM")!= 0){
        fscanf(filein, "%s", comando);
;
        if(strcmp(comando, "TITULO")==0){
            fscanf(filein, "%s", nome);
            if(livroCriado==1){
                p = (secao *) malloc (sizeof(secao));
                strcpy(p->nomeSecao, nome);
                p->idir = NULL;
                p->pai = NULL;
                p->fesq = raiz;
                raiz = p;
            }
            else{
                criarRaiz(&raiz, nome);
            }
        }
        else{;
            if(strcmp(comando, "INSERIR")==0){
                fscanf(filein, "%s %s", nome, inserirComo);
                if(strcmp(inserirComo, "SUB")==0){
                    fscanf(filein, "%s", inserirOnde);
                    if(livroCriado==0){
                        fprintf(fileout, "ERRO: nao encontrado item %s\n--------------------------------------------------\n", inserirOnde);
                    }
                    else{
                        p = encontrar(inserirOnde, raiz);
                        if(p==NULL){
                            fprintf(fileout, "ERRO: nao encontrado item %s\n--------------------------------------------------\n", inserirOnde);
                        }
                        else{
                            inserirSub(nome, &p);
                        }
                    }
                }
                else{;
                    if(strcmp(inserirComo, "SEGUINTE_A")==0){
                        fscanf(filein, "%s", inserirOnde);
                        if(livroCriado==0){
                            fprintf(fileout, "ERRO: nao encontrado item %s\n--------------------------------------------------\n", inserirOnde);
                        }
                        else{
                            if(strcmp(inserirOnde, raiz->nomeSecao)==0){
                                fprintf(fileout, "ERRO: operacao invalida\n--------------------------------------------------\n");
                            }
                            else{
                                p = encontrar(inserirOnde, raiz);
                                if(p==NULL){
                                    fprintf(fileout, "ERRO: nao encontrado item %s\n--------------------------------------------------\n", inserirOnde);
                                }
                                else{
                                    inserirSeguinte(nome, &p);;
                                }
                            }
                        }
                    }
                }
            }
            else{
                if(strcmp(comando, "LISTA")==0){
                    if(livroCriado==0){
                        fprintf(fileout, "ERRO: comando inadequado\n--------------------------------------------------\n");
                    }
                    else{
                        numeroDaLista++;
                        fprintf(fileout, "LISTA %d\n\n", numeroDaLista);
                        imprimirArvore(raiz);
                    }
                }
                else{
                    if(strcmp(comando, "REMOVER")==0){
                        fscanf(filein, "%s", qualRemover);
                        if(livroCriado==0){
                            fprintf(fileout, "ERRO: nao en;contrado item %s\n--------------------------------------------------\n", qualRemover);
                        }
                        else{
                            p = encontrar(qualRemover, raiz);
                            if(p==NULL){
                                fprintf(fileout, "ERRO: nao encontrado item %s\n--------------------------------------------------\n", qualRemover);
                            }
                            else{
                                if(strcmp(qualRemover, raiz->nomeSecao)==0){
                                    remover(&p, &p);
                                    raiz = (secao *) malloc (sizeof(secao));
                                    livroCriado = 0;
                                }
                                else{
                                    remover(&p, &p);
                                }
                            }
                        }
                    }
                    else{;
                        if(strcmp(comando, "TRANSFERIR")==0){
                           fscanf(filein, "%s %s", nome, transferirComo);
                            if(livroCriado==0){
                                fprintf(fileout, "ERRO: nao encontrado item %s\n--------------------------------------------------\n", nome);
                            }
                            else{
                                q = encontrar(nome, raiz);
                                if(q==NULL){
                                    fprintf(fileout, "ERRO: nao encontrado item %s\n--------------------------------------------------\n", nome);
                                }
                                else{
                                    if(strcmp(transferirComo, "SUB")==0){
                                        fscanf(filein, "%s", transferirOnde);
                                        p = encontrar(transferirOnde, raiz);
                                        if(p==NULL){
                                            fprintf(fileout, "ERRO: nao encontrado item %s\n--------------------------------------------------\n", inserirOnde);
                                        }
                                        else{
                                            transferirSub(&q, &p);
                                        }
                                    }
                                    else{
                                        if(strcmp(transferirComo, "SEGUINTE_A")==0){
                                            fscanf(filein, "%s", transferirOnde);
                                            if(strcmp(transferirOnde, raiz->nomeSecao)==0){
                                                fprintf(fileout, "ERRO: operacao invalida\n--------------------------------------------------\n");
                                            }
                                            else{
                                                p = encontrar(transferirOnde, raiz);
                                                if(p==NULL){
                                                    fprintf(fileout, "ERRO: nao encontrado item %s\n--------------------------------------------------\n", inserirOnde);
                                                }
                                                else{
                                                    transferirSeguinte(&q, &p);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    finalizarArquivos();
}


//inicializa os arquivos e faz o tratamento correto das primeiras linhas
void inicializarArquivos(){

    int i;
    char linhaInicial[71];

    filein = fopen("entrada2.txt", "r");
    fileout = fopen("Lab2_Kalil_Georges_Balech.txt", "w");

    for(i=0; i<4; i++){
        fgets(linhaInicial, 71, filein);
    }

    fprintf(fileout, "    Agredeco a Deus, a minha familia e\naos demais colaboradores.\n    Muito Obrigado!\n--------------------------------------------------\n");

}

// -------------------------------------------------
// Cria a raiz da arvore
void criarRaiz(ponteiro *A, char nome[]){
    if(livroCriado==0){
        strcpy((*A)->nomeSecao, nome);
        (*A)->fesq = NULL;
        (*A)->idir = NULL;
        (*A)->pai = NULL;
        livroCriado=1;
    }
    else{
        ponteiro q;
        q = (secao *) malloc (sizeof(secao));
        strcpy(q->nomeSecao, nome);
        q->fesq = *A;
        q->idir = NULL;
        q->pai = NULL;
        *A = q;
    }
}

// -------------------------------------------------
// Devolve um ponteiro para o nó procurado
ponteiro encontrar(char nome[], ponteiro raiz){

    ponteiro p;
    p = raiz;

    if(foiParaOPai == 0){
        if(strcmp(nome, p->nomeSecao)==0){
            return p;
        }
        else{
            if(p->fesq != NULL){
                p = p->fesq;
                encontrar(nome, p);
            }
            else{
                if(p->idir != NULL){
                    p = p->idir;
                    encontrar(nome, p);
                }
                else{
                    if(p->pai != NULL){
                        p = p->pai;
                        foiParaOPai = 1;
                        encontrar(nome, p);
                    }
                }
            }
        }
    }
    else{
        if(p->idir != NULL){
            p = p->idir;
            foiParaOPai = 0;
            encontrar(nome, p);
        }
        else{
            if(p->pai != NULL){
                p = p->pai;
                encontrar(nome, p);
            }
            else{
                foiParaOPai = 0;
                return NULL;
            }
        }
    }
}

// -------------------------------------------------
// Insere um nó novo como filho esquerdo de um já existente
void inserirSub(char nome[], ponteiro *p){

    ponteiro q;
    q = (*p)->fesq;

    (*p)->fesq = (secao *) malloc (sizeof(secao));
    strcpy((*p)->fesq->nomeSecao, nome);
    (*p)->fesq->pai = *p;
    (*p)->fesq->idir = q;
    (*p)->fesq->fesq = NULL;

}

// -------------------------------------------------
// Insere um nó novo como irmão direito de um já existente
void inserirSeguinte(char nome[], ponteiro *p){

    ponteiro q;
    q = (*p)->idir;

    (*p)->idir = (secao *) malloc (sizeof(secao));
    strcpy((*p)->idir->nomeSecao, nome);
    (*p)->idir->pai = (*p)->pai;
    (*p)->idir->idir = q;
    (*p)->idir->fesq = NULL;

}

// -------------------------------------------------
// imprime a árvore
void imprimirArvore(ponteiro raiz){

    ponteiro p;
    p = raiz;
    int i;

    if(foiParaOPai == 0){
        switch(posicao){
            case -1:
                fprintf(fileout, "      %s\n", p->nomeSecao);
                break;
            default:
                for(i=0; i<=posicao; i++){
                    fprintf(fileout, "%d.", indices[i]);
                }
                fprintf(fileout, "      %s\n", p->nomeSecao);


        }

        if(p->fesq != NULL){
            p = p->fesq;
            posicao++;
            indices[posicao]++;
            imprimirArvore(p);
        }
        else{
            if(p->idir != NULL){
                p = p->idir;
                indices[posicao]++;
                imprimirArvore(p);
            }
            else{
                if(p->pai != NULL){
                    p = p->pai;
                    indices[posicao]=0;
                    posicao--;
                    foiParaOPai = 1;
                    imprimirArvore(p);
                }
            }
        }
    }
    else{
        if(p->idir != NULL){
            p = p->idir;
            indices[posicao]++;
            foiParaOPai = 0;
            imprimirArvore(p);
        }
        else{
            if(p->pai != NULL){
                p = p->pai;
                indices[posicao]=0;
                posicao--;
                imprimirArvore(p);
            }
            else{
                foiParaOPai = 0;
                posicao = -1;
                fprintf(fileout, "--------------------------------------------------\n");
                for(i=0;i<5;i++){
                    indices[i]=0;
                }
            }
        }
    }


}

// -------------------------------------------------
// Remove um nó da árvore e seus dependentes
void remover(ponteiro *p, ponteiro *raiz){
    ponteiro q;
    // para entrar aqui, deve ser o primeiro ponteiro da subarvore a ser excluido
    if((*p)==(*raiz)){
        // precisamos rearranjar os ponteiros vizinhos
        // aqui é caso nao seja a raiz principal
        if((*p)->pai != NULL){
            q = (*p)->pai;
            if(q->fesq == (*p)){
                q->fesq = (*p)->idir;
                (*p)->idir = NULL;
                (*p)->pai =NULL;
            }
            else{
                for(q = q->fesq; q->idir != (*p); q = q->idir);
                q->idir = (*p)->idir;
                (*p)->idir = NULL;
                (*p)->pai =NULL;
            }
            if((*p)->fesq == NULL){
                free(*p);
            }
            else{
                remover(&((*p)->fesq), &(*raiz));
                free(*p);
            }
        }
    // aqui, nao precisa rearranjar os ponteiros viziznhos
    // aqui é caso desejemos excluir toda a raiz
        else{
            if((*p)->fesq != NULL){
                remover(&((*p)->fesq), &(*raiz));
            }
            if((*p)->idir != NULL){
                remover(&((*p)->idir), &(*raiz));
            }
            free(*p);
        }
    }
    // aqui é para remover um nó nao raz da sub-arvore
    else{
        if((*p)->fesq != NULL){
            remover(&((*p)->fesq), &(*raiz));
        }
        if((*p)->idir != NULL){
            remover(&((*p)->idir), &(*raiz));
        }
        free(*p);
    }
    *p = NULL;
}

// -------------------------------------------------
//transfere um trecho da árvore como filho de outro nó
void transferirSub(ponteiro *oque, ponteiro *onde){
    ponteiro q;
    q = (*oque)->pai;
    if(q->fesq == *oque){
        q->fesq = (*oque)->idir;
        (*oque)->idir = NULL;
        (*oque)->pai = NULL;
    }
    else{
        for(q = q->fesq; q->idir != (*oque); q = q->idir);
        q->idir = (*oque)->idir;
        (*oque)->idir = NULL;
        (*oque)->pai = NULL;
    }
    q = (*onde)->fesq;
    (*onde)->fesq = (*oque);
    (*oque)->idir = q;
    (*oque)->pai = (*onde);
}

// -------------------------------------------------
// transfere um trecho da árvore como irmão de outro nó
void transferirSeguinte(ponteiro *oque, ponteiro *onde){
    ponteiro q;
    q = (*oque)->pai;
    if(q->fesq == *oque){
        q->fesq = (*oque)->idir;
        (*oque)->idir = NULL;
        (*oque)->pai = NULL;
    }
    else{
        for(q = q->fesq; q->idir != (*oque); q = q->idir);
        q->idir = (*oque)->idir;
        (*oque)->idir = NULL;
        (*oque)->pai = NULL;
    }
    q = (*onde)->idir;
    (*onde)->idir = *oque;
    (*oque)->idir = q;
    (*oque)->pai = (*onde)->pai;
}


//fecha os arquivos abertos
void finalizarArquivos(){

    fclose(filein);
    fclose(fileout);

}
