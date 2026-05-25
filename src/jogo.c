/* jogo.c - Logica principal do jogo Navegador Capibaribe (Dev 4) */
#include "jogo.h"
#include "hud.h"

#include "../lib/fila.h"
#include "../lib/lista.h"
#include "../lib/ranking.h"
#include "../lib/mecanica/movimentacao.h"
#include "../lib/mecanica/fila_de_obstaculos.h"
#include "../lib/mecanica/mecanicaItens/mecanicaGeracaoItens.h"
#include "../lib/inventario/inventario.h"

static jogador jogador_principal;
static Fila *obstaculos_ativos;
static Linkedlist_item *itens_ativos;
static int capacidade_itens_diferentes = 3;

static Color cor_obstaculo(const obstaculo *obstaculo_atual) {
    if (strcmp(obstaculo_atual->nome, "Tronco") == 0) return BROWN;
    if (strcmp(obstaculo_atual->nome, "Lixo no rio") == 0) return DARKGREEN;
    if (strcmp(obstaculo_atual->nome, "Pilastra de ponte") == 0) return GRAY;
    if (strcmp(obstaculo_atual->nome, "Barco parado") == 0) return BLUE;
    return DARKGRAY;
}

static Color cor_item(const Item *item_atual) {
    if (item_atual->tipo == ITEM_MOEDA) return GOLD;
    if (item_atual->tipo == ITEM_ESCUDO) return BLUE;
    if (item_atual->tipo == ITEM_PEIXE) return ORANGE;
    if (item_atual->tipo == ITEM_PA) return BROWN;
    return BLACK;
}

static const char *nome_item(const Item *item_atual) {
    if (item_atual->tipo == ITEM_MOEDA) return "Moeda";
    if (item_atual->tipo == ITEM_ESCUDO) return "Escudo";
    if (item_atual->tipo == ITEM_PEIXE) return "Peixe";
    if (item_atual->tipo == ITEM_PA) return "Pa";
    return "Item";
}

void jogo_iniciar(void) {
    jogador_principal = (jogador){
        .nome = "Navegante",
        .vida = 100,
        .pontuacao = 0,
        .velocidade = 5,
        .invencivel = 0,
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
        },
        .poderes = {
            .escudo = false,
            .pa = false
        },
        .inventario = inventario_criar(capacidade_itens_diferentes)
    };

    printf("Iniciando jogo...\n");

    obstaculos_ativos = fila_criar();
    itens_ativos = malloc(sizeof(Linkedlist_item));

    if (jogador_principal.inventario == NULL || obstaculos_ativos == NULL || itens_ativos == NULL) {
        fprintf(stderr, "Falha ao inicializar o estado do jogo.\n");

        if (obstaculos_ativos != NULL) {
            fila_destruir(obstaculos_ativos);
            obstaculos_ativos = NULL;
        }

        if (itens_ativos != NULL) {
            free(itens_ativos);
            itens_ativos = NULL;
        }

        free(jogador_principal.inventario);
        jogador_principal.inventario = NULL;
        return;
    }

    itens_ativos->next = NULL;

    jogador_principal.pontuacao = 0;
    jogador_principal.invencivel = 0;
    jogador_principal.poderes.escudo = false;
    jogador_principal.poderes.pa = false;

    iniciar_cronometro_jogo();

    iniciar_spawn_obstaculos();
    spawn_obstaculo(obstaculos_ativos);

    iniciar_spawn_itens();
    spawn_item(itens_ativos);

    jogo_atualizar();
    jogo_encerrar();
}

void jogo_atualizar(void) {
    while (!WindowShouldClose()) {
        if (jogador_principal.vida <= 0) break;

        mov_jogador(&jogador_principal);

        atualizar_spawn_obstaculos(obstaculos_ativos);
        atualizar_obstaculos(obstaculos_ativos, &jogador_principal);

        atualizar_spawn_itens(itens_ativos);
        atualizar_itens(itens_ativos, &jogador_principal);

        if (jogador_principal.vida < 0) {
            jogador_principal.vida = 0;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Navegante Capibaribe", 40, 40, 30, DARKBLUE);
        DrawText(TextFormat("Tempo: %.1fs", tempo_desde_inicio_jogo()), 40, 125, 20, DARKGRAY);
        DrawText(TextFormat("Obstaculos ativos: %d", fila_tamanho(obstaculos_ativos)), 40, 150, 20, DARKGRAY);

        DrawRectangle(
            jogador_principal.pos.x,
            jogador_principal.pos.y,
            jogador_principal.hitbox.largura,
            jogador_principal.hitbox.altura,
            RED
        );

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

        Item *item_atual = itens_ativos->next;
        while (item_atual != NULL) {
            DrawRectangle(
                item_atual->pos.x,
                item_atual->pos.y,
                item_atual->hitbox.largura,
                item_atual->hitbox.altura,
                cor_item(item_atual)
            );

            DrawText(
                nome_item(item_atual),
                item_atual->pos.x,
                item_atual->pos.y - 18,
                16,
                BLACK
            );

            item_atual = item_atual->next;
        }

        hud_desenhar(&jogador_principal);

        EndDrawing();

        if (IsKeyDown(KEY_P)) break;
    }
}

void jogo_encerrar(void) {
    if (jogador_principal.inventario != NULL) {
        inventario_destruir(jogador_principal.inventario);
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

    if (itens_ativos != NULL) {
        Item *atual = itens_ativos->next;

        while (atual != NULL) {
            Item *proximo = atual->next;
            free(atual);
            atual = proximo;
        }

        free(itens_ativos);
        itens_ativos = NULL;
    }
}