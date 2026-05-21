#ifndef MECANICA_ITENS_INVENTARIO_H
#define MECANICA_ITENS_INVENTARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "entidades.h"
#include "raylib.h"

/*
 * Módulo responsável pela comunicação entre itens do mapa e o inventário do jogador
 * Detecta colisões entre jogador e itens e realiza a coleta automática
 */

/*
 * Verifica se o jogador colidiu com um item
 * @param jogador: ponteiro para a estrutura do jogador
 * @param item: ponteiro para a estrutura do item
 * @return: 1 se houve colisão, 0 caso contrário
 */
int check_colisao_item_jogador(jogador *jogador, Item *item);

/*
 * Verifica a colisão entre o jogador e um item, e coleta o item se houver colisão
 * Remove o item do mapa e adiciona ao inventário do jogador
 * @param jogador: ponteiro para o jogador
 * @param lista_itens: ponteiro para a lista de itens ativos
 * @param item: ponteiro para o item a verificar colisão
 */
void checarColeta_item(jogador *jogador, Linkedlist_item *lista_itens, Item *item);

/*
 * Verifica colisão com todos os itens da lista
 * Útil para o loop principal do jogo
 * @param jogador: ponteiro para o jogador
 * @param lista_itens: ponteiro para a lista de itens ativos
 */


 
// void checar_colisoes_itens(jogador *jogador, Linkedlist_item *lista_itens); // ainda nao implementada 

#endif /* MECANICA_ITENS_INVENTARIO_H */
