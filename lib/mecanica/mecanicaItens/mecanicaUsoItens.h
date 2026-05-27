#ifndef MECANICA_USO_ITENS_H
#define MECANICA_USO_ITENS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "item.h"
#include "entidades.h"
#include "../../inventario/inventario.h"



bool usar_item(jogador* player, TipoItem tipo_item);

/*
 * Desativa um poder ativo do jogador (chamado quando o tempo do poder expira)
 * @param player: ponteiro para o jogador
 * @param tipo_item: tipo do item cujo poder deve ser desativado
 */
void atualizar_poderes(jogador* player);

#endif /* MECANICA_USO_ITENS_H */
