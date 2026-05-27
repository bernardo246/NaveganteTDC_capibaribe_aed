#ifndef FILA_DE_OBSTACULOS_H
#define FILA_DE_OBSTACULOS_H

#include "entidades.h"
#include <raylib.h>
#include "fila.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OBSTACULO_POS_MIN 200
#define OBSTACULO_POS_MAX 610

void init_obstacle(obstaculo *obstaculo, const char *nome);
void set_obstacle_profile(obstaculo *obstaculo, const char *nome);
void iniciar_spawn_obstaculos(void);
void spawn_obstaculo(Fila *obstaculos_ativos);
void atualizar_spawn_obstaculos(Fila *obstaculos_ativos);
void iniciar_cronometro_jogo(void);
double tempo_desde_inicio_jogo(void);
void atualizar_velocidade_obstaculos(void);
void dificuldade_progressiva(obstaculo *obstaculo);
void tempo_invencivel(jogador *jogador_atual);
void atualizar_obstaculos(Fila *obstaculos_ativos, jogador *jogador_atual);
int colisao_jogador_X_obstaculo(jogador *jogador,obstaculo *obstaculo);
int get_velocidade_atual_obstaculos(void);

#endif
