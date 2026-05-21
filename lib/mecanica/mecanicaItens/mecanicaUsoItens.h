#ifndef MECANICA_USO_ITENS_H
#define MECANICA_USO_ITENS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "item.h"
#include "entidades.h"
#include "inventario.h"

/*
 * Módulo responsável por gerenciar o uso de itens do inventário
 * Verifica se um item pode ser usado e aplica seus efeitos ao jogador
 */

/*
 * Verifica se um item pode ser utilizado pelo jogador
 * Valida se o jogador possui o item e se as condições permitem seu uso
 * (ex: não pode usar escudo se já está invencível)
 * @param player: ponteiro para o jogador
 * @param tipo_item: tipo do item a verificar (TipoItem enum)
 * @return: true se o item pode ser usado, false caso contrário
 */
bool checar_item_usavel(jogador* player, TipoItem tipo_item);

/*
 * Usa um item do inventário do jogador e aplica seus efeitos
 * Remove 1 unidade do item do inventário e ativa o poder correspondente
 * @param player: ponteiro para o jogador
 * @param tipo_item: tipo do item a usar (TipoItem enum)
 * @return: true se o item foi usado com sucesso, false caso contrário
 */
bool usar_item(jogador* player, TipoItem tipo_item);

/*
 * Desativa um poder ativo do jogador (chamado quando o tempo do poder expira)
 * @param player: ponteiro para o jogador
 * @param tipo_item: tipo do item cujo poder deve ser desativado
 */
void desativar_poder(jogador* player, TipoItem tipo_item);

#endif /* MECANICA_USO_ITENS_H */
