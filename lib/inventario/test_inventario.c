#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "inventario.h"

static void imprimir_inventario(Inventario* inv) {
    if (!inv || !inv->atual) {
        printf("Inventario vazio\n");
        return;
    }

    InventarioItem* atual = inv->atual;
    do {
        printf("Tipo %d | qtd=%d | img=%s\n",
               atual->tipo,
               atual->quantidade,
               atual->imagem[0] != '\0' ? atual->imagem : "(sem imagem)");
        atual = atual->next;
    } while (atual != inv->atual);
}

int main(void) {
    Inventario* inv = inventario_criar(4);
    if (!inv) {
        fprintf(stderr, "Falha ao criar inventario\n");
        return EXIT_FAILURE;
    }

    printf("-- adicionando itens --\n");
    add_item(inv, ITEM_MOEDA, 1); // moeda
    add_item(inv, ITEM_ESCUDO, 3); // escudo
    add_item(inv, ITEM_MOEDA, 2); // acumula moeda
    add_item(inv, ITEM_PA, 5); // pa
    imprimir_inventario(inv);

    printf("\n-- removendo 1 escudo --\n");
    remove_item(inv, ITEM_ESCUDO, 1);
    imprimir_inventario(inv);

    printf("\n-- removendo 3 escudos (deve remover o tipo) --\n");
    remove_item(inv, ITEM_ESCUDO, 3);
    imprimir_inventario(inv);

    printf("\n-- verificando fetch_item --\n");
    printf("moeda existe? %s\n", fetch_item(inv, ITEM_MOEDA) ? "sim" : "nao");
    printf("escudo existe? %s\n", fetch_item(inv, ITEM_ESCUDO) ? "sim" : "nao");
    printf("peixe existe? %s\n", fetch_item(inv, ITEM_PEIXE) ? "sim" : "nao");

    return EXIT_SUCCESS;
}
