/* jogo.c - Logica principal do jogo Navegador Capibaribe (Dev 4) */

#include <raylib.h> // TODO: interface grafica - raylib
#include <stdio.h>
#include "../include/default_structs.h"
#include "../include/entidades.h"
#include "../include/tipos.h"
#include "jogo.h"
#include "../lib/fila.h"
#include "../lib/lista.h"
#include "../lib/ranking.h"
#include "../lib/mecanica/movimentacao.h"
#include "../lib/mecanica/fila_de_obstaculos.h"

static jogador jogador_principal;
static Fila *obstaculos_ativos;

static Color cor_obstaculo(const obstaculo *obstaculo_atual) {
    if (strcmp(obstaculo_atual->nome, "Tronco") == 0) return BROWN;
    if (strcmp(obstaculo_atual->nome, "Lixo no rio") == 0) return DARKGREEN;
    if (strcmp(obstaculo_atual->nome, "Pilastra de ponte") == 0) return GRAY;
    if (strcmp(obstaculo_atual->nome, "Barco parado") == 0) return BLUE;
    return DARKGRAY;
}

void jogo_iniciar(void) {
    jogador_principal = (jogador){.nome = "Navegante",
        .vida = 100,
        .pontuacao = 0,
        .velocidade = 5,
        .invencivel=0,
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
    iniciar_cronometro_jogo();
    iniciar_spawn_obstaculos();
    spawn_obstaculo(obstaculos_ativos);
    SetTargetFPS(60); 
    jogo_atualizar();
    jogo_encerrar();
}

void jogo_atualizar(void) {
    /* TODO: logica de cada frame/turno */
    const int vida_maxima = 100;
    const int barra_x = 40;
    const int barra_y = 85;
    const int barra_largura = 300;
    const int barra_altura = 24;

    while(!WindowShouldClose()){
            if(jogador_principal.vida<=0)break;
            mov_jogador(&jogador_principal);
            atualizar_spawn_obstaculos(obstaculos_ativos);
            atualizar_obstaculos(obstaculos_ativos, &jogador_principal);
            if (jogador_principal.vida < 0) {
                jogador_principal.vida = 0;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Navegante Capibaribe", 40, 40, 30, DARKBLUE);
            DrawText("Vida", barra_x, barra_y - 26, 20, BLACK);
            DrawRectangleLines(barra_x, barra_y, barra_largura, barra_altura, BLACK);

            int largura_vida = (jogador_principal.vida * barra_largura) / vida_maxima;
            Color cor_vida = (jogador_principal.vida > 50) ? GREEN :
                             (jogador_principal.vida > 20) ? ORANGE : RED;
            DrawRectangle(barra_x, barra_y, largura_vida, barra_altura, cor_vida);
            DrawText(TextFormat("Tempo: %.1fs", tempo_desde_inicio_jogo()), 40, 125, 20, DARKGRAY);
            DrawText(TextFormat("Obstaculos ativos: %d", fila_tamanho(obstaculos_ativos)), 40, 150, 20, DARKGRAY);

            DrawRectangle(jogador_principal.pos.x, jogador_principal.pos.y,jogador_principal.hitbox.largura,jogador_principal.hitbox.altura, RED);

            No *no_atual = obstaculos_ativos->inicio;
            while (no_atual != NULL) {
                obstaculo *obstaculo_atual = (obstaculo *)no_atual->dado;
                Rectangle hitbox_visual = {
                    obstaculo_atual->pos.x - obstaculo_atual->hitbox.largura / 2.0f,
                    obstaculo_atual->pos.y - obstaculo_atual->hitbox.altura / 2.0f,
                    obstaculo_atual->hitbox.largura,
                    obstaculo_atual->hitbox.altura
                };

                DrawRectangleRec(hitbox_visual, Fade(cor_obstaculo(obstaculo_atual), 0.5f));
                DrawRectangleLinesEx(hitbox_visual, 2.0f, cor_obstaculo(obstaculo_atual));
                DrawText(obstaculo_atual->nome, obstaculo_atual->pos.x - 65, obstaculo_atual->pos.y + 36, 18, DARKGRAY);
                no_atual = no_atual->proximo;
            }

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
