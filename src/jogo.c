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
static Fila *obstaculos_ativos;

void jogo_iniciar(void) {
    jogador_principal = (jogador){.nome = "Navegante",
        .vida = 100,
        .pontuacao = 0,
        .velocidade = 5,
        .inventario = NULL,
        .hitbox = {
            .largura = 32,
            .altura = 32
        },
        .animacao_andar = {
            .num_frames = 0,
            .frame_atual = 0
        },
        .pos = {
            .x = 640,
            .y = 360
        }
    };

    printf("Iniciando jogo...\n");
    /* TODO: inicializar fila de trechos, arvore de itens, estado do jogador */
    obstaculos_ativos = fila_criar();
    InitWindow(1280,720,"navegante_tdc");
    SetTargetFPS(60); 
    jogo_atualizar();
    jogo_encerrar();
}

void jogo_atualizar(void) {
    /* TODO: logica de cada frame/turno */
    while(!WindowShouldClose()){
            if(jogador_principal->vida<=0)break;
            mov_jogador(&jogador_principal);
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Navegante Capibaribe", 40, 40, 30, DARKBLUE);
            DrawCircle(jogador_principal.pos.x, jogador_principal.pos.y, 20.0f, RED);
            EndDrawing();

            //fechar janela, por enquanto que n faz algo para retornar ao menu
            if(IsKeyDown(KEY_P))break;
    }
}

void jogo_encerrar(void) {
    if (jogador_principal.inventario != NULL) {
        arvore_destruir(jogador_principal.inventario);
        jogador_principal.inventario = NULL;
    }

    if (obstaculos_ativos != NULL) {
        while (!fila_vazia(obstaculos_ativos)) {
            obstaculo *obstaculo_atual = (obstaculo *)fila_desenfileirar(obstaculos_ativos);
            free(obstaculo_atual);
        }
        fila_destruir(obstaculos_ativos);
        obstaculos_ativos = NULL;
    }

    CloseWindow();
}
