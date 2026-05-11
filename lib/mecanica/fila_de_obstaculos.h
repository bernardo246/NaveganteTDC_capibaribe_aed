#ifndef FILA_DE_OBSTACULOS_H
#define FILA_DE_OBSTACULOS_H

#include "entidades.h"
#include <raylib.h>
#include "fila.h"
#include <stdlib.h>
#include <string.h>

#define OBSTACULO_POS_MIN 0
#define OBSTACULO_POS_MAX 720

void init_obstacle(obstaculo *obstaculo, const char *nome);
void set_obstacle_profile(obstaculo *obstaculo, const char *nome);
void atualizar_obstaculos(Fila *obstaculos_ativos);

#endif
