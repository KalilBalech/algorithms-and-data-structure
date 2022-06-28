#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Sempre devemos dar free() num elemento que é excluido da lista
//devemos criar os metodos de manipulação de TAD para a realização desse lab, logo rever aula com esses metodos
//não esquecer do fclose
//revisar manipulação read and write de arquivos
//escrever cabeçalho no topo do arquivo .cpp

/* Kalil Georges Balech */
/* Turma 3 */
/* */
/* Exercício 1: Torre de Controle */
/* Programa compilado com CodeBlocks 17.12 */
/*
typedef struct noh noh;
typedef struct lista lista;
typedef noh *posicao;

struct noh{
    char voo[5];
    char cidade[31];
    noh *prox;
};
/*
struct lista{
    noh *inicio;
    noh *fim;
};

//FILE *fileout, *filein;
/*
void inicializarArquivos(void);
//lista criarLista();
void inserir(char *, char *, lista*);                       // TALVEZ AQUI TAMBEM
void urgencia(char *, lista*, lista*);
void removerERegistrar(lista*);
void imprimirLista(lista*);
void encerrarArquivos(void);
*/
int main(){
    printf("teste");
    /*
    char mensagem[15], cidade[31], voo[5];
    lista *listaPrincipal, *listaUrgencia;

    listaPrincipal = (lista *) malloc (sizeof(lista));
    listaPrincipal->inicio = (noh *) malloc (sizeof(noh));
    listaPrincipal->fim = listaPrincipal->inicio;
    listaPrincipal->fim->prox = NULL;

    listaUrgencia = (lista *) malloc (sizeof(lista));
    listaUrgencia->inicio = (noh *) malloc (sizeof(noh));
    listaUrgencia->fim = listaUrgencia->inicio;
    listaUrgencia->fim->prox = NULL;


    inicializarArquivos();
    /*if(filein == NULL){
        printf("O arquivo nao pode ser aberto");
        system("pause");
        return 0;
    }
    strcpy(mensagem, "vazio");

    while(strcmp(mensagem, "FIM") != 0){
        fscanf(filein, "%s %s", mensagem, voo);

        fgets(cidade, 20, filein);

        if(strcmp(mensagem, "pede_pouso")==0){
            inserir(voo, cidade, &listaPrincipal);
        }
        if(strcmp(mensagem, "pista_liberada")==0){
            if(listaUrgencia.inicio==listaUrgencia.fim){
                if(listaPrincipal.inicio==listaPrincipal.fim){
                    fprintf(fileout, "nenhum aviao pousando\n");
                }
                else{
                    removerERegistrar(&listaPrincipal);
                }
            }
            else{
                removerERegistrar(&listaUrgencia);
            }
        }
        if(strcmp(mensagem, "URGENCIA")==0){
            urgencia(voo, &listaPrincipal, &listaUrgencia);
        }
        if(strcmp(mensagem, "FIM")==0){
            fprintf(fileout, "\nLISTA URGENCIA\n\n");
            imprimirLista(listaUrgencia);
            fprintf(fileout, "\nLISTA PRINCIPAL\n\n");
            imprimirLista(listaPrincipal);
        }
    }

    encerrarArquivos();
    printf("\n\n");
    //system("pause");
    */
    return 0;
}

//inicializa os arquivos e realiza os tratamentos corretos de suas primeiras linhas
/*
void inicializarArquivos(){
    printf("oi");
    int i;
    char linhaInicial[71];
    filein = fopen("entrada1.txt", "r");
    fileout = fopen("Lab1_Kalil_Georges_Balech.txt", "w");
    fprintf(fileout, "Aeroporto internacional do DCTA\nSenhores passageiros, nao usem o cinto de seguranca\nOBS: o piloto eh bom\n=========================================\nFLIGHT  FROM\n\n");
    for(i=1; i<=8; i++){
        fgets(linhaInicial, 71, filein);
        //printf("%s", linhaInicial);
    }
}

/*lista criarLista(){

    lista *A;
    A = (lista *) malloc (sizeof(lista));
    A->inicio = (noh *) malloc (sizeof(noh));
    A->fim = A->inicio;
    A->fim->prox = NULL;
    return A;
}

void inserir(char x[], char local[], lista *L){              //O ERRO ESTÁ AQUI
    posicao q;

    L->fim->prox = (noh*) malloc (sizeof(noh));
    strcpy(L->fim->prox->voo, x);
    strcpy(L->fim->prox->cidade, local);
    L->fim->prox->prox = NULL;
    L->fim = L->fim->prox;
}

void urgencia(char x[], lista *A, lista *B){
    posicao q, r, s;
    for(q = A->inicio; q->prox->voo != x; q = q->prox);
    r = q->prox;
    if(r->prox!= NULL){
        q->prox = r->prox;
    }
    else{
        q->prox = NULL;
    }
    s = B->fim;
    s->prox = r;
    r->prox = NULL;
}
// nao esquecer do free
void removerERegistrar(lista *A){
    posicao q;
    if(A->inicio->prox == A->fim){
        q = A->fim;
        fprintf(fileout, "%d    %s\n", q->voo, q->cidade);
        A->inicio->prox = NULL;
        free(q);
        A->fim = A->inicio;
    }
    else{
        q = A->inicio->prox;
        fprintf(fileout, "%d    %s\n", q->voo, q->cidade);
        A->inicio->prox = q->prox;
        free(q);
    }
}

void imprimirLista(lista *A){
    posicao p;
    if(A->inicio==A->fim){
        fprintf(fileout, "Vazia\n");
    }
    else{
        for(p=A->inicio; p->prox!=NULL; p = p->prox){
            fprintf(fileout, "%4d    %s\n", p->prox->voo, p->prox->cidade);
        }
    }
}

//encerra os arquivos
void encerrarArquivos(){
    fclose(fileout);
    fclose(filein);
}
*/
