#ifndef MECANICA_GERACAO_ITENS_H
#define MECANICA_GERACAO_ITENS_H

#include <stdlib.h>
#include <raylib.h>
#include "item.h"
#include "entidades.h"

#define MAPA_LARGURA   1280
#define MAPA_ALTURA     720
#define MAX_TENTATIVAS   10

Item *gerar_item(Linkedlist_item *lista_itens);
void  iniciar_spawn_itens(void);
void  spawn_item(Linkedlist_item *lista_itens);
void  atualizar_spawn_itens(Linkedlist_item *lista_itens);
void  atualizar_itens(Linkedlist_item *lista_itens, jogador *jogador);

#endif 