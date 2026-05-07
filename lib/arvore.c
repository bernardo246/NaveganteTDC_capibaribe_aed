/* arvore.c - Implementacao da BST de itens coletaveis (Dev 2) */

#include <stdlib.h>
#include "arvore.h"
#include "tipos.h"

Arvore *arvore_criar(void) {
    Arvore *a = (Arvore *)malloc(sizeof(Arvore));
    if (!a) return NULL;
    a->raiz = NULL;
    return a;
}

static void destruir_no(NoBST *no) {
    if (!no) return;
    destruir_no(no->esq);
    destruir_no(no->dir);
    free(no);
}

void arvore_destruir(Arvore *a) {
    destruir_no(a->raiz);
    free(a);
}

static NoBST *inserir_no(NoBST *no, int chave, void *dado) {
    if (!no) {
        NoBST *novo = (NoBST *)malloc(sizeof(NoBST));
        if (!novo) return NULL;
        novo->chave = chave;
        novo->dado  = dado;
        novo->esq   = novo->dir = NULL;
        return novo;
    }
    if (chave < no->chave)
        no->esq = inserir_no(no->esq, chave, dado);
    else if (chave > no->chave)
        no->dir = inserir_no(no->dir, chave, dado);
    else
        no->dado = dado; /* atualiza dado se chave ja existe */
    return no;
}

int arvore_inserir(Arvore *a, int chave, void *dado) {
    a->raiz = inserir_no(a->raiz, chave, dado);
    return a->raiz != NULL;
}

static NoBST *buscar_no(NoBST *no, int chave) {
    if (!no || no->chave == chave) return no;
    if (chave < no->chave) return buscar_no(no->esq, chave);
    return buscar_no(no->dir, chave);
}

void *arvore_buscar(const Arvore *a, int chave) {
    NoBST *no = buscar_no(a->raiz, chave);
    return no ? no->dado : NULL;
}

static NoBST *minimo(NoBST *no) {
    while (no->esq) no = no->esq;
    return no;
}

static NoBST *remover_no(NoBST *no, int chave) {
    if (!no) return NULL;
    if (chave < no->chave) {
        no->esq = remover_no(no->esq, chave);
    } else if (chave > no->chave) {
        no->dir = remover_no(no->dir, chave);
    } else {
        if (!no->esq) { NoBST *d = no->dir; free(no); return d; }
        if (!no->dir) { NoBST *e = no->esq; free(no); return e; }
        NoBST *suc = minimo(no->dir);
        no->chave  = suc->chave;
        no->dado   = suc->dado;
        no->dir    = remover_no(no->dir, suc->chave);
    }
    return no;
}

int arvore_remover(Arvore *a, int chave) {
    if (!arvore_buscar(a, chave)) return 0;
    a->raiz = remover_no(a->raiz, chave);
    return 1;
}

int item_cadastrar(Arvore *a, Item *item) {
    return arvore_inserir(a, item->id, item);
}

int item_coletar(Arvore *a, int id) {
    Item *item = (Item *)arvore_buscar(a, id);
    if (!item){ 
        return 0; 
    }         
    int valor = item->valor;
    arvore_remover(a, id);
    return valor;                 
}