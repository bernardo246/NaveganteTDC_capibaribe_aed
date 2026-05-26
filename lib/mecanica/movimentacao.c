#include "movimentacao.h"

void mov_jogador(jogador *jogador){
    jogador->dir_x = 0;
    jogador->dir_y = 0;

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    { jogador->pos.y -= jogador->velocidade; jogador->dir_y = -1; }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  { jogador->pos.y += jogador->velocidade; jogador->dir_y =  1; }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { jogador->pos.x += jogador->velocidade; jogador->dir_x =  1; }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  { jogador->pos.x -= jogador->velocidade; jogador->dir_x = -1; }

    if (jogador->pos.y > 720)  jogador->pos.y = 720;
    if (jogador->pos.y < 0)    jogador->pos.y = 0;
    if (jogador->pos.x > 1280) jogador->pos.x = 1280;
    if (jogador->pos.x < 0)    jogador->pos.x = 0;
}

void mov_obstacle(obstaculo *obstaculo){
    obstaculo->pos.x -=obstaculo->velocidade;
}
