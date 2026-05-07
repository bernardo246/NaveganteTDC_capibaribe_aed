/* arvore.h - BST de itens coletaveis (Dev 2) */

#ifndef ARVORE_H
#define ARVORE_H

#include "entidades.h" 

typedef struct NoBST {
    int         chave;
    void       *dado;
    struct NoBST *esq;
    struct NoBST *dir;
} NoBST;

typedef struct {
    NoBST *raiz;
} Arvore;

Arvore *arvore_criar(void);
void    arvore_destruir(Arvore *a);
int     arvore_inserir(Arvore *a, int chave, void *dado);
void   *arvore_buscar(const Arvore *a, int chave);
int     arvore_remover(Arvore *a, int chave);
int item_cadastrar(Arvore *a, Item *item);
int item_coletar(Arvore *a, int id); 

#endif /* ARVORE_H */
