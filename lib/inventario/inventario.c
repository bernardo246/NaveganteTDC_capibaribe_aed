#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <raylib.h>
#include "inventario.h"

const char *InventarioItem_IMAGEM[] = {
    NULL,
    "assets/sprites/itensInventario/moeda.png",   // índice 1
    "assets/sprites/itensInventario/escudo.png",  // índice 2
    "assets/sprites/itensInventario/peixe.png",   // índice 3
    "assets/sprites/itensInventario/pa.png"       // índice 4
};

static const char *inventario_obter_imagem_por_tipo(TipoItem tipo_item) {
    int max_tipo = (int)(sizeof(InventarioItem_IMAGEM) / sizeof(InventarioItem_IMAGEM[0])); // calcula o número de elementos no array
    if ((int)tipo_item <= 0 || (int)tipo_item >= max_tipo) {
        return InventarioItem_IMAGEM[0];
    }
    return InventarioItem_IMAGEM[tipo_item];
}





// iniciando o inventario 
// esse capacidade itens diferentes serve pra limitar o número de tipos de itens diferentes, não a quantidade total
Inventario* inventario_criar(int capacidade_itens_diferentes) {
    if (capacidade_itens_diferentes <= 0) {
        return NULL;
    }

    Inventario* inv = malloc(sizeof(Inventario));
    if (!inv) {
        return NULL;
    }

    inv->primeiro = NULL;
    inv->atual = NULL;
    inv->capacidade_itens_diferentes = capacidade_itens_diferentes;
    inv->quantidade_itens_diferentes = 0;
    return inv;
}

//lista é duplamente encadeada e circular
bool fetch_item(Inventario* inventario, TipoItem tipo_item) {
    if (inventario == NULL || inventario->atual == NULL) {
        return false;
    }

    InventarioItem* item_atual = inventario->atual;
    do {
        if (item_atual->tipo == tipo_item) {
            return true; // item encontrado
        }
        item_atual = item_atual->next;
    } while (item_atual != inventario->atual); // loop até voltar ao início

    return false; // item não encontrado
}


// adicionanto um item no inventario, se o item já existir, apenas aumenta a quantidade
bool add_item(Inventario* inventario, TipoItem tipo_item, int quantidade) {
    // implementação da função de adicionar item
    // verifica se o item já existe, se sim, aumenta a quantidade
    if (fetch_item(inventario, tipo_item)) {
        while (inventario->atual->tipo != tipo_item) {
            inventario->atual = inventario->atual->next; // move para o item encontrado
        }
        inventario->atual->quantidade += quantidade; // aumenta a quantidade do item
        return true; // placeholder
    }
    else {
        // verifica se a capacidade de itens diferentes foi atingida antes de adicionar um novo tipo de item
        if (inventario->quantidade_itens_diferentes >= inventario->capacidade_itens_diferentes) {
            return false; // não é possível adicionar mais tipos de itens
        }
        // se não, cria um novo item e adiciona na lista
        InventarioItem* novo_item = malloc(sizeof(InventarioItem));
        if (!novo_item) {
            return false; // falha ao alocar memória para o novo item
        }
        novo_item->tipo = tipo_item;
        novo_item->quantidade = quantidade;
        novo_item->capacidade = 100; // exemplo de capacidade para cada item, pode ser ajustado conforme necessário

        // define a imagem do item com base no tipo
        strncpy(novo_item->imagem, inventario_obter_imagem_por_tipo(tipo_item), sizeof(novo_item->imagem) - 1);
        novo_item->imagem[sizeof(novo_item->imagem) - 1] = '\0';

        // adiciona o novo item na lista circular duplamente encadeada
        if (inventario->atual == NULL) {
            // primeiro item no inventário
            novo_item->next = novo_item;
            novo_item->prev = novo_item;
            inventario->atual = novo_item;
            inventario->primeiro = novo_item; // ← adiciona isso
        } else {
            // adiciona o novo item antes do item atual
            InventarioItem* ultimo = inventario->atual->prev;

            ultimo->next = novo_item;
            novo_item->prev = ultimo;

            novo_item->next = inventario->atual;
            inventario->atual->prev = novo_item;

            inventario->atual = novo_item; // torna o novo item o atual
        }
        inventario->quantidade_itens_diferentes++; // incrementa a contagem de tipos de itens diferentes
    }
    
    return true; // placeholder
}



bool remove_item(Inventario* inventario, TipoItem tipo_item, int quantidade) {
    // implementação da função de remover item
    if (inventario == NULL || inventario->atual == NULL) {
        return false;
    }

    InventarioItem* item_atual = inventario->atual;
    do {
        if (item_atual->tipo == tipo_item) {
            if (item_atual->quantidade > quantidade) {
                item_atual->quantidade -= quantidade; // reduz a quantidade do item
            } else {
                // remove o item da lista
                item_atual->prev->next = item_atual->next;
                item_atual->next->prev = item_atual->prev;

                // se o item removido for o atual, move o ponteiro atual para o próximo item
                if (inventario->atual == item_atual) {
                    inventario->atual = item_atual->next != item_atual ? item_atual->next : NULL; // se for o único item, define como NULL
                }
                // se o item removido for o primeiro, move o ponteiro primeiro para o próximo
                if (inventario->primeiro == item_atual) {
                    inventario->primeiro = item_atual->next != item_atual ? item_atual->next : NULL;
                }

                free(item_atual); // libera a memória do item removido
                inventario->quantidade_itens_diferentes--; // decrementa a contagem de tipos de itens diferentes
            }
            return true; // item encontrado e processado, sai da função
        }
        item_atual = item_atual->next;
    } while (item_atual != inventario->atual); // loop até voltar ao início
    return false; // item não encontrado
}

int inventario_quantidade_item(Inventario* inventario, TipoItem tipo_item) {
    if (inventario == NULL || inventario->atual == NULL) {
        return 0;
    }

    InventarioItem* item_atual = inventario->atual;
    do {
        if (item_atual->tipo == tipo_item) {
            return item_atual->quantidade;
        }
        item_atual = item_atual->next;
    } while (item_atual != inventario->atual);

    return 0;
}

void inventario_destruir(Inventario* inventario) {
    if (inventario == NULL) {
        return;
    }

    if (inventario->atual != NULL) {
        InventarioItem* item_atual = inventario->atual;
        do {
            InventarioItem* item_para_remover = item_atual;
            item_atual = item_atual->next; // move para o próximo item antes de liberar a memória
            free(item_para_remover); // libera a memória do item
        } while (item_atual != inventario->atual); // loop até voltar ao início
    }

    free(inventario); // libera a memória do inventário
}
