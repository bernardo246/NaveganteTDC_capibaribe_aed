/* jogo.h - Declaracoes da logica principal do jogo (Dev 4) */

#ifndef JOGO_H
#define JOGO_H

#include <raylib.h> // TODO: interface grafica - raylib
#include <stdio.h>
#include "../include/default_structs.h"
#include "../include/entidades.h"
#include "../lib/fila.h"
#include "../lib/lista.h"
#include "../lib/ranking.h"
#include "../lib/mecanica/movimentacao.h"
#include "../lib/mecanica/fila_de_obstaculos.h"


// includes de inventario e itens:

// #include "../lib/mecanica/mecanicaItens/mecanicageracaoItens.h"
#include "../lib/mecanica/mecanicaItens/mecanicaItensInventario.h"
#include "../lib/mecanica/mecanicaItens/mecanicaUsoItens.h"
#include "../lib/inventario/inventario.h"

void jogo_iniciar(const char *nome_jogador);
void jogo_atualizar(void);
void jogo_encerrar(void);

#endif /* JOGO_H */
