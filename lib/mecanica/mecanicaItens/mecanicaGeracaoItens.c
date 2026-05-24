#include <stdlib.h>
#include <raylib.h>
#include "mecanicaGeracaoItens.h"
#include "mecanicaItensInventario.h"

static double ultimo_spawn_item = -1.0;

static const int valores_por_tipo[] = {
    0,   /* índice 0 — não usado */
    10,  /* ITEM_MOEDA  = 1 */
    0,   /* ITEM_ESCUDO = 2 */
    25,  /* ITEM_PEIXE  = 3 */
    50   /* ITEM_PA     = 4 */
};

static int posicao_ocupada(Linkedlist_item *lista, Item *novo) {
    if (!lista) return 0;
    Item *atual = lista->next;
    while (atual) {
        if (atual->pos.x == novo->pos.x && atual->pos.y == novo->pos.y)
            return 1;
        atual = atual->all_itens ? atual->all_itens->next : NULL;
    }
    return 0;
}

Item *gerar_item(Linkedlist_item *lista_itens) {
    Item *item = (Item *)malloc(sizeof(Item));
    if (!item) return NULL;
    item->tipo  = (TipoItem)((rand() % 4) + 1);
    item->id    = rand() % 10000;
    item->valor = valores_por_tipo[item->tipo];
    item->hitbox.largura = 32;
    item->hitbox.altura  = 32;
    int tentativas = 0;
    do {
        item->pos.x = (float)(rand() % (MAPA_LARGURA - item->hitbox.largura));
        item->pos.y = (float)(rand() % (MAPA_ALTURA  - item->hitbox.altura));
        tentativas++;
    } while (posicao_ocupada(lista_itens, item) && tentativas < MAX_TENTATIVAS);
    if (tentativas >= MAX_TENTATIVAS && posicao_ocupada(lista_itens, item)) {
        free(item);
        return NULL;
    }
    item->all_itens    = NULL;
    item->itens_ativos = NULL;
    return item;
}

void iniciar_spawn_itens(void) {
    ultimo_spawn_item = GetTime() - 3.0;
}

void spawn_item(Linkedlist_item *lista_itens) {
    if (!lista_itens) return;
    Item *novo = gerar_item(lista_itens);
    if (!novo) return;
    novo->all_itens = lista_itens;
    lista_itens->next = novo;
}

void atualizar_spawn_itens(Linkedlist_item *lista_itens) {
    if (!lista_itens) return;
    if (ultimo_spawn_item < 0.0) iniciar_spawn_itens();
    double agora = GetTime();
    double intervalo = 5.0; 
    if ((agora - ultimo_spawn_item) >= intervalo) {
        spawn_item(lista_itens);
        ultimo_spawn_item = agora;
    }
}

void atualizar_itens(Linkedlist_item *lista_itens, jogador *jogador) {
    if (!lista_itens || !jogador) return;
    Item *atual = lista_itens->next;
    while (atual) {
        Item *proximo = atual->all_itens ? atual->all_itens->next : NULL;
        checarColeta_item(jogador, lista_itens, atual);
        atual = proximo;
    }
}