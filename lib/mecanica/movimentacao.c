#include "movimentacao.h"

void mov_jogador(jogador *jogador){
    if (IsKeyDown(KEY_W)|| IsKeyDown(KEY_UP)) jogador->pos.y -= jogador->velocidade;
    if (IsKeyDown(KEY_S)|| IsKeyDown(KEY_DOWN)) jogador->pos.y += jogador->velocidade;
    if (IsKeyDown(KEY_D)|| IsKeyDown(KEY_RIGHT)) jogador->pos.x += jogador->velocidade;
    if (IsKeyDown(KEY_A)|| IsKeyDown(KEY_LEFT)) jogador->pos.x -= jogador->velocidade;

    if (jogador->pos.y > 720) jogador->pos.y = 720;
    if (jogador->pos.y < 0) jogador->pos.y = 0;
    if (jogador->pos.x > 1280) jogador->pos.x = 1280;
    if (jogador->pos.x < 0) jogador->pos.x = 0;
}

void mov_obstacle(obstaculo *obstaculo){
    obstaculo->pos.x--;
}
