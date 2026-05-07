/* jogo.c - Logica principal do jogo Navegador Capibaribe (Dev 4) */

#include <raylib.h> // TODO: interface grafica - raylib
#include <stdio.h>
#include "../include/default_structs.h"
#include "../include/entidades.h"
#include "../include/tipos.h"
#include "jogo.h"
#include "../lib/fila.h"
#include "../lib/arvore.h"
#include "../lib/ranking.h"
#include "../lib/mecanica/movimentacao.h"

static jogador jogador_principal;

void jogo_iniciar(void) {
    jogador_principal = (jogador){.nome = "Navegante",
        .vida = 100,
        .pontuacao = 0,
        .velocidade = 5,
        .inventario = NULL,
        .hitbox = {
            .largura = 32.0f,
            .altura = 32.0f
        },
        .animacao_andar = {
            .num_frames = 0,
            .frame_atual = 0
        },
        .pos = {
            .x = 640.0f,
            .y = 360.0f
        }
    };

    printf("Iniciando jogo...\n");
    /* TODO: inicializar fila de trechos, arvore de itens, estado do jogador */
    InitWindow(1280,720,"navegante_tdc");
    SetTargetFPS(60); 
    jogo_atualizar();
    jogo_encerrar();
}

void jogo_atualizar(void) {
    /* TODO: logica de cada frame/turno */
    while(!WindowShouldClose()){
            mov_jogador(&jogador_principal);
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Navegante Capibaribe", 40, 40, 30, DARKBLUE);
            DrawCircle((int)jogador_principal.pos.x, (int)jogador_principal.pos.y, 20.0f, RED);
            EndDrawing();

            //fechar janela, por enquanto que n faz algo para retornar ao menu
            if(IsKeyDown(KEY_P))break;
    }
}

void jogo_encerrar(void) {
    /* TODO: liberar recursos e salvar recorde */
    CloseWindow();
}
