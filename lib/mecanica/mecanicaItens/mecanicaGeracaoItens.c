#include <stdlib.h>
#include <raylib.h>
#include "mecanicaGeracaoItens.h"
#include "mecanicaItensInventario.h"

static double ultimo_spawn_item = -1.0;



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
    item->valor = 1; // valor padrão, pode ser ajustado para itens específicos
    item->hitbox.largura = 32;
    item->hitbox.altura  = 32;
    int tentativas = 0;
    do {
        int min_x = 0;
        int max_x = MAPA_LARGURA - item->hitbox.largura;
        int min_y = 200;
        int max_y = 610 - item->hitbox.altura;

        if (max_x < min_x) max_x = min_x;
        if (max_y < min_y) max_y = min_y;

        item->pos.x = (float)(min_x + (rand() % (max_x - min_x + 1)));
        item->pos.y = (float)(min_y + (rand() % (max_y - min_y + 1)));
        tentativas++;
    } while (posicao_ocupada(lista_itens, item) && tentativas < MAX_TENTATIVAS);
    if (tentativas >= MAX_TENTATIVAS && posicao_ocupada(lista_itens, item)) {
        free(item);
        return NULL;
    }
    item->all_itens    = NULL;
    item->itens_ativos = NULL;
    item->next = NULL;
    item->tempo_spawn = GetTime();
    return item;
}

void iniciar_spawn_itens(void) {
    ultimo_spawn_item = GetTime() - 3.0;
}

void spawn_item(Linkedlist_item *lista_itens) {
    if (!lista_itens) return;
    Item *novo = gerar_item(lista_itens);
    if (!novo) return;
    novo->next = lista_itens->next;
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

// essa função vai ser chamada a cada frame, ela vai verificar se o jogador coletou algum item ou se algum item expirou, se o jogador coletou o item, ele vai ser adicionado no inventario do jogador e removido da tela, se o item expirou ele vai ser removido da tela
void atualizar_itens(Linkedlist_item *lista_itens, jogador *jogador) {
    if (!lista_itens || !jogador) return; // segurança para evitar segfaults

    Item *anterior = NULL; 
    Item *atual = lista_itens->next;

    while (atual != NULL) {
        Item *proximo = atual->next;

        double tempo_vivo = GetTime() - atual->tempo_spawn;
        bool coletou = checarColeta_item(jogador, lista_itens, atual); // retorna se coletou, se sim ja joga no inventario
        bool expirou = tempo_vivo >= 5.0;

        if (coletou || expirou) {
            if (anterior == NULL)
                lista_itens->next = proximo;
            else
                anterior->next = proximo;
            free(atual);
        } else {
            anterior = atual;
        }

        atual = proximo;
    }
}