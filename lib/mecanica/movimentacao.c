#include "movimentacao.h"

void mov_jogador(jogador *jogador){
    if (IsKeyDown(KEY_W)) jogador->pos.y -= jogador->velocidade;
    if (IsKeyDown(KEY_S)) jogador->pos.y += jogador->velocidade;
    if (IsKeyDown(KEY_D)) jogador->pos.x += jogador->velocidade;
    if (IsKeyDown(KEY_A)) jogador->pos.x -= jogador->velocidade;

    if (jogador->pos.y > 720) jogador->pos.y = 720;
    if (jogador->pos.y < 0) jogador->pos.y = 0;
    if (jogador->pos.x > 1280) jogador->pos.x = 1280;
    if (jogador->pos.x < 0) jogador->pos.x = 0;
}

void mov_obstacle(obstaculo *obstaculo){
    obstaculo->pos.x--;
}
