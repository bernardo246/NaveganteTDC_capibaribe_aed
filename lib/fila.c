/* fila.c - Implementacao da fila de trechos do rio (Dev 1) */

#include <stdlib.h>
#include "fila.h"

Fila *fila_criar(void) {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if (!f) return NULL;
    f->inicio  = NULL;
    f->fim     = NULL;
    f->tamanho = 0;
    return f;
}

void fila_destruir(Fila *f) {
    while (!fila_vazia(f))
        fila_desenfileirar(f);
    free(f);
}

int fila_enfileirar(Fila *f, void *dado) {
    No *no = (No *)malloc(sizeof(No));
    if (!no) return 0;
    no->dado     = dado;
    no->proximo  = NULL;
    if (f->fim)
        f->fim->proximo = no;
    else
        f->inicio = no;
    f->fim = no;
    f->tamanho++;
    return 1;
}

void *fila_desenfileirar(Fila *f) {
    if (fila_vazia(f)) return NULL;
    No   *no   = f->inicio;
    void *dado = no->dado;
    f->inicio  = no->proximo;
    if (!f->inicio) f->fim = NULL;
    free(no);
    f->tamanho--;
    return dado;
}

int fila_vazia(const Fila *f) {
    return f->tamanho == 0;
}

int fila_tamanho(const Fila *f) {
    return f->tamanho;
}
