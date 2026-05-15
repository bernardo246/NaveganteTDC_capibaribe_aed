// definicao de item do jogo
#ifndef ITEM_H
#define ITEM_H

#incldue <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "default_structs.h"

struct Linkedlist_item;

typedef enum {
    ITEM_MOEDA = 1,
    ITEM_ESCUDO = 2,
    ITEM_PEIXE = 3,
    ITEM_PA = 4
} TipoItem;

typedef struct Item {
    int id;
    TipoItem tipo; // aqui ele guarda um numero que representa o tipo do item, por exemplo, 1 para moeda, 2 para escudo, etc.
    int valor;

    Hitbox hitbox;
    Animacao animacao;
    Posicao pos;

    struct Linkedlist_item* all_itens;
    struct Linkedlist_item* itens_ativos;
} Item;



#endif /* ITEM_H */
