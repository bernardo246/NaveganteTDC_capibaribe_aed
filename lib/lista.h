#ifndef LISTA_H
#define LISTA_H

#include "entidades.h"

typedef struct Linkedlist_item Linkedlist_item;

Linkedlist_item *lista_criar(void);
void lista_destruir(Linkedlist_item *lista);
int lista_inserir(Linkedlist_item *lista, Item *item);
int lista_coletar(Linkedlist_item *lista, int id);

#endif /* LISTA_H */