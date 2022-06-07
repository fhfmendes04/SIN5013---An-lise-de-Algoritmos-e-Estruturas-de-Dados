#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0
typedef int BOOL;
typedef int TIPOCHAVE;

typedef struct aux {
TIPOCHAVE chave;
/* Dados armazenados vão aqui */
struct aux *esq, *dir;
} NO;

typedef NO* PONT;


PONT inicializa() {
    return(NULL);
}

PONT adiciona(PONT raiz, PONT no){
    if (raiz == NULL) return(no);
    if (no->chave < raiz->chave)
        raiz->esq = adiciona(raiz->esq,no);
    else
        raiz->dir = adiciona(raiz->dir, no);
    /*ignora chave igual*/
    return(raiz);
}

PONT criaNovoNo(TIPOCHAVE ch) {
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    return(novoNo);
}

PONT contem(TIPOCHAVE ch, PONT raiz) {
    if (raiz == NULL) return(NULL);
    if (raiz->chave == ch) return(raiz);
    if(raiz->chave > ch)
        return (contem(ch, raiz->esq));
    else
        return (contem(ch, raiz->dir));
}

int numeroNos(PONT raiz) {
    if (!raiz) return 0;
    return (numeroNos(raiz->esq)
            + 1
            + numeroNos(raiz->dir));
}

void exibirArvore(PONT raiz){
    if (raiz != NULL) {
        printf("%i", raiz->chave);
        printf("(");
        exibirArvore(raiz->esq);
        exibirArvore(raiz->dir);
        printf(")");
    }
}

PONT buscaNo(PONT raiz, TIPOCHAVE ch, PONT *pai){
    PONT atual = raiz;
    *pai = NULL;
    while (atual) {
        if(atual->chave == ch) return(atual);
        *pai = atual;
        if(ch < atual->chave) 
            atual = atual->esq;
        else 
            atual = atual->dir;
    }
    return(NULL);
}

PONT removeNo(PONT raiz, TIPOCHAVE ch){
    PONT pai, no, p, q;
    no = buscaNo(raiz,ch,&pai);
    if (no==NULL) return(raiz);
    if (!no->esq || !no->dir) {
        if(!no->esq)
            q = no->dir;
        else
            q = no->esq;
    }
    else {
        p = no;
        q = no->esq;
        while(q->dir){
            p = q;
            q = q->dir;
        }
        if (p != no) {
            p->dir = q->esq;
            q->esq = no->esq;
        }
        q->dir = no->dir;
    }
    if (!pai){
        free(no);
        return(q);
    }
    if (ch < pai->chave)
        pai->esq = q;
    else
        pai->dir = q;
    free(no);
    return(raiz);
}

int main() {
    PONT r = inicializa();

/* criação da árvore */
    PONT no = criaNovoNo(15);
    r = adiciona(r, no);

    no = criaNovoNo(23);
    r = adiciona(r, no);

    no = criaNovoNo(8);
    r = adiciona(r, no);

    no = criaNovoNo(2);
    r = adiciona(r, no);

    no = criaNovoNo(12);
    r = adiciona(r, no);

    no = criaNovoNo(20);
    r = adiciona(r, no);

    no = criaNovoNo(30);
    r = adiciona(r, no);
/*******************************/

/*PONT p = contem(8,r);*/


printf("%d\n", numeroNos(r));

printf("\n----------\n");

exibirArvore(r);

printf("\n----------\n");

removeNo(r, 30);

exibirArvore(r);


}