#include <stdlib.h>
#include "lista.h"

Linkedlist_item *lista_criar(void) {
    Linkedlist_item *lista = (Linkedlist_item *)malloc(sizeof(Linkedlist_item));
    if (!lista) return NULL;
    lista->next = NULL;
    lista->prev = NULL;
    return lista;
}

void lista_destruir(Linkedlist_item *lista) {
    if (!lista) return;
    Item *atual = lista->next;
    while (atual) {
        Item *proximo = atual->all_itens ? atual->all_itens->next : NULL;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int lista_inserir(Linkedlist_item *lista, Item *item) {
    if (!lista || !item) return 0;
    item->all_itens = lista;
    lista->next = item;
    return 1;
}

int lista_coletar(Linkedlist_item *lista, int id) {
    if (!lista) return 0;
    Item *atual = lista->next;
    Item *anterior = NULL;
    while (atual) {
        if (atual->id == id) {
            int valor = atual->valor;
            if (anterior) anterior->all_itens->next = atual->all_itens ? atual->all_itens->next : NULL;
            else lista->next = atual->all_itens ? atual->all_itens->next : NULL;
            free(atual);
            return valor;
        }
        anterior = atual;
        atual = atual->all_itens ? atual->all_itens->next : NULL;
    }
    return 0;
}