#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "entidades.h"
#include "item.h"

typedef struct InventarioItem {

    char imagem[128]; // caminho da imagem do item, pode ser usado para exibir o item no inventário
    
    TipoItem tipo; // tipo do item, usando o enum definido em item.h
    int quantidade;
    int capacidade;
    struct InventarioItem* next;
    struct InventarioItem* prev;
} InventarioItem;

typedef struct Inventario {
    InventarioItem* primeiro; // ponteiro para o primeiro item no inventário
    InventarioItem* atual;
    int capacidade_itens_diferentes;
    int quantidade_itens_diferentes;
} Inventario;

Inventario* inventario_criar(int capacidade_itens_diferentes);
bool fetch_item(Inventario* inventario, TipoItem tipo_item);
bool add_item(Inventario* inventario, TipoItem tipo_item, int quantidade);
bool remove_item(Inventario* inventario, TipoItem tipo_item, int quantidade);
int inventario_quantidade_item(Inventario* inventario, TipoItem tipo_item);
void inventario_destruir(Inventario* inventario);

extern const char *InventarioItem_IMAGEM[]; // o extern permite que a definição do array seja feita em um arquivo .c, evitando problemas de múltiplas definições

#endif /* INVENTARIO_H */
