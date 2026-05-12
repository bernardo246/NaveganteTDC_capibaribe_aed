/* fila.h - Fila de trechos do rio (Dev 1) */

#ifndef FILA_H
#define FILA_H

typedef struct No {
    void *dado;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int tamanho;
} Fila;

Fila *fila_criar(void);
void  fila_destruir(Fila *f);
int   fila_enfileirar(Fila *f, void *dado);
void *fila_desenfileirar(Fila *f);
int   fila_mover_no_para_inicio(Fila *f, void *dado);
int   fila_vazia(const Fila *f);
int   fila_tamanho(const Fila *f);

#endif /* FILA_H */
