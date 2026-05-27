/* jogo.c - Logica principal do jogo Navegador Capibaribe (Dev 4) */

#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/default_structs.h"
#include "../include/entidades.h"
#include "../include/som.h"

#include "jogo.h"
#include "hud.h"

#include "../lib/fila.h"
#include "../lib/lista.h"
#include "../lib/ranking.h"
#include "../lib/mecanica/movimentacao.h"
#include "../lib/mecanica/fila_de_obstaculos.h"
#include "../lib/mecanica/mecanicaItens/mecanicaGeracaoItens.h"
#include "../lib/inventario/inventario.h"
#include "../include/clima.h"
#include "../lib/inventario/scrollInventario.h"
#include "../lib/mecanica/mecanicaItens/mecanicaUsoItens.h"

static jogador jogador_principal;
static Fila *obstaculos_ativos;
static Clima clima_atual;
static Linkedlist_item *itens_ativos;
static int capacidade_itens_diferentes = 3;

static Texture2D fundo_jogo;

static Texture2D escudo_sprite;
static Texture2D pa_sprite;
static Texture2D moeda_sprite;
static Texture2D peixe_sprite;

static Texture2D tronco_textures[9];
static Texture2D garrafa_textures[9];
static Texture2D sacola_textures[3];
static Texture2D pedra1_textures[1];
static Texture2D pedra2_textures[1];
static Texture2D barco_textures[3];

static const char *BARCO_SPRITE_PATHS[3] = {
    "assets/sprites/obstaculos/barco/barco_devagar.png",
    "assets/sprites/obstaculos/barco/barco_acelerando.png",
    "assets/sprites/obstaculos/barco/barco_rapido.png",
};

static Texture2D jogador_textures[8];

static const char *JOGADOR_SPRITE_PATHS[8] = {
    "assets/sprites/jogador/jogador_devagar.png",
    "assets/sprites/jogador/jogador_acelerando_e_re.png",
    "assets/sprites/jogador/jogador_vel_media.png",
    "assets/sprites/jogador/jogador_rapido.png",
    "assets/sprites/jogador/jogador_cima_devagar.png",
    "assets/sprites/jogador/jogador_baixo_devagar.png",
    "assets/sprites/jogador/jogador_cima_rapido.png",
    "assets/sprites/jogador/jogador_baixo_rapido.png",
};

static Color cor_obstaculo(const obstaculo *obstaculo_atual) {
    if (strcmp(obstaculo_atual->nome, "Tronco") == 0) return BROWN;
    if (strcmp(obstaculo_atual->nome, "Garrafa no rio") == 0) return GREEN;
    if (strcmp(obstaculo_atual->nome, "Sacola no rio") == 0) return DARKGREEN;
    if (strcmp(obstaculo_atual->nome, "Pedra pequena") == 0) return GRAY;
    if (strcmp(obstaculo_atual->nome, "Pedra grande") == 0) return DARKGRAY;
    if (strcmp(obstaculo_atual->nome, "Barco") == 0) return SKYBLUE;
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

void jogo_iniciar(const char *nome_jogador) {
    jogador_principal = (jogador){
        .nome = "",
        .vida = 100,
        .pontuacao = 0,
        .velocidade = 5,
        .invencivel = 0,
        .nivel_velocidade = 0,
        .dir_x = 0,
        .dir_y = 0,
        .hitbox = {
            .largura = 128,
            .altura = 128
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

    if (nome_jogador != NULL && nome_jogador[0] != '\0') {
        strncpy(jogador_principal.nome, nome_jogador, sizeof(jogador_principal.nome) - 1);
        jogador_principal.nome[sizeof(jogador_principal.nome) - 1] = '\0';
    } else {
        strncpy(jogador_principal.nome, "Navegante", sizeof(jogador_principal.nome) - 1);
        jogador_principal.nome[sizeof(jogador_principal.nome) - 1] = '\0';
    }

    fundo_jogo = LoadTexture("assets/sprites/imagem_fundo1.png");

    escudo_sprite = LoadTexture("assets/sprites/itens/escudo.png");
    pa_sprite = LoadTexture("assets/sprites/itens/pa.png");
    moeda_sprite = LoadTexture("assets/sprites/itens/moeda.png");
    peixe_sprite = LoadTexture("assets/sprites/itens/peixe.png");

    for (int i = 0; i < 8; i++)
        jogador_textures[i] = LoadTexture(JOGADOR_SPRITE_PATHS[i]);

    for (int i = 0; i < 3; i++)
        barco_textures[i] = LoadTexture(BARCO_SPRITE_PATHS[i]);

    for (int i = 0; i < TRONCO_PADRAO.animacao_andar.num_frames; i++)
        tronco_textures[i] = LoadTexture(TRONCO_PADRAO.animacao_andar.frames[i]);

    for (int i = 0; i < LIXO_NO_RIO_GARRAFA_PADRAO.animacao_andar.num_frames; i++)
        garrafa_textures[i] = LoadTexture(LIXO_NO_RIO_GARRAFA_PADRAO.animacao_andar.frames[i]);

    garrafa_textures[1] = LoadTexture("assets/sprites/obstaculos/lixo/garrafa_rapida.png");

    for (int i = 0; i < LIXO_NO_RIO_SACOLA_PADRAO.animacao_andar.num_frames; i++)
        sacola_textures[i] = LoadTexture(LIXO_NO_RIO_SACOLA_PADRAO.animacao_andar.frames[i]);

    for (int i = 0; i < PEDRA1_PADRAO.animacao_andar.num_frames; i++)
        pedra1_textures[i] = LoadTexture(PEDRA1_PADRAO.animacao_andar.frames[i]);

    for (int i = 0; i < PEDRA2_PADRAO.animacao_andar.num_frames; i++)
        pedra2_textures[i] = LoadTexture(PEDRA2_PADRAO.animacao_andar.frames[i]);

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

    atualizar_clima(&clima_atual);
    print_request();

    hud_iniciar();
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

        atualizar_poderes(&jogador_principal);

        TipoItem scroll_antes = jogador_principal.inventario && jogador_principal.inventario->atual
            ? jogador_principal.inventario->atual->tipo
            : 0;

        atualizar_scroll(jogador_principal.inventario);

        TipoItem scroll_depois = jogador_principal.inventario && jogador_principal.inventario->atual
            ? jogador_principal.inventario->atual->tipo
            : 0;

        if (scroll_antes != scroll_depois)
            tocar_som(SOM_TROCA_ITEM_INVENTARIO);

        if (IsKeyPressed(KEY_SPACE)) {
            if (jogador_principal.inventario && jogador_principal.inventario->atual) {
                TipoItem tipo_usado = jogador_principal.inventario->atual->tipo;

                usar_item(&jogador_principal, tipo_usado);

                if (tipo_usado == ITEM_ESCUDO)
                    tocar_som(SOM_ATIVACAO_ESCUDO);
                else if (tipo_usado == ITEM_PA)
                    tocar_som(SOM_PEGOU_PA);
            }
        }

        if (jogador_principal.vida < 0) {
            jogador_principal.vida = 0;
        }

        int vel = get_velocidade_atual_obstaculos();
        int novo_nivel = (vel <= 1) ? 0 : (vel == 2) ? 1 : (vel == 3) ? 2 : 3;

        if (novo_nivel > jogador_principal.nivel_velocidade) {
            jogador_principal.nivel_velocidade = novo_nivel;
        }

        Texture2D *tex_j;

        if (jogador_principal.dir_x == -1) {
            tex_j = &jogador_textures[1];
        } else if (jogador_principal.dir_y == -1) {
            tex_j = (jogador_principal.nivel_velocidade <= 1)
                ? &jogador_textures[4]
                : &jogador_textures[6];
        } else if (jogador_principal.dir_y == 1) {
            tex_j = (jogador_principal.nivel_velocidade <= 1)
                ? &jogador_textures[5]
                : &jogador_textures[7];
        } else {
            tex_j = &jogador_textures[jogador_principal.nivel_velocidade];
        }

        BeginDrawing();

        DrawTexturePro(
            fundo_jogo,
            (Rectangle){0, 0, fundo_jogo.width, fundo_jogo.height},
            (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
            (Vector2){0, 0},
            0,
            WHITE
        );

        DrawTexturePro(
            *tex_j,
            (Rectangle){0, 0, tex_j->width, tex_j->height},
            (Rectangle){
                jogador_principal.pos.x,
                jogador_principal.pos.y,
                jogador_principal.hitbox.largura,
                jogador_principal.hitbox.altura
            },
            (Vector2){0, 0},
            0.0f,
            WHITE
        );

        if (jogador_principal.poderes.escudo) {
            DrawTexturePro(
                escudo_sprite,
                (Rectangle){0, 0, escudo_sprite.width, escudo_sprite.height},
                (Rectangle){
                    jogador_principal.pos.x + 70,
                    jogador_principal.pos.y + 25,
                    50,
                    50
                },
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
        } else if (jogador_principal.poderes.pa) {
            DrawTexturePro(
                pa_sprite,
                (Rectangle){0, 0, pa_sprite.width, pa_sprite.height},
                (Rectangle){
                    jogador_principal.pos.x + 65,
                    jogador_principal.pos.y + 35,
                    55,
                    55
                },
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
        }

        DrawText("Navegante Capibaribe", 40, 40, 30, DARKBLUE);
        DrawText(TextFormat("Tempo: %.1fs", tempo_desde_inicio_jogo()), 40, 125, 20, DARKGRAY);
        DrawText(TextFormat("Obstaculos ativos: %d", fila_tamanho(obstaculos_ativos)), 40, 150, 20, DARKGRAY);

        No *no_atual = obstaculos_ativos->inicio;

        while (no_atual != NULL) {
            obstaculo *obstaculo_atual = (obstaculo *)no_atual->dado;

            Rectangle hitbox_visual = {
                obstaculo_atual->pos.x - obstaculo_atual->hitbox.largura / 2.0f,
                obstaculo_atual->pos.y - obstaculo_atual->hitbox.altura / 2.0f,
                obstaculo_atual->hitbox.largura,
                obstaculo_atual->hitbox.altura
            };

            Texture2D *textures = NULL;
            int barco_idx = -1;
            int garrafa_idx = -1;

            if (strcmp(obstaculo_atual->nome, "Tronco") == 0) {
                textures = tronco_textures;
            } else if (strcmp(obstaculo_atual->nome, "Garrafa no rio") == 0) {
                garrafa_idx = (vel >= 5) ? 1 : 0;
            } else if (strcmp(obstaculo_atual->nome, "Sacola no rio") == 0) {
                textures = sacola_textures;
            } else if (strcmp(obstaculo_atual->nome, "Pedra pequena") == 0) {
                textures = pedra1_textures;
            } else if (strcmp(obstaculo_atual->nome, "Pedra grande") == 0) {
                textures = pedra2_textures;
            } else if (strcmp(obstaculo_atual->nome, "Barco") == 0 ||
                       strcmp(obstaculo_atual->nome, "Barco parado") == 0) {
                barco_idx = (vel <= 3) ? 0 : (vel <= 6) ? 1 : 2;
            }

            if (barco_idx >= 0) {
                Texture2D tex = barco_textures[barco_idx];

                DrawTexturePro(
                    tex,
                    (Rectangle){0, 0, tex.width, tex.height},
                    hitbox_visual,
                    (Vector2){0, 0},
                    0.0f,
                    WHITE
                );
            } else if (garrafa_idx >= 0) {
                Texture2D tex = garrafa_textures[garrafa_idx];

                DrawTexturePro(
                    tex,
                    (Rectangle){0, 0, tex.width, tex.height},
                    hitbox_visual,
                    (Vector2){0, 0},
                    0.0f,
                    WHITE
                );
            } else if (textures != NULL && obstaculo_atual->animacao_andar.num_frames > 0) {
                obstaculo_atual->animacao_andar.anim_timer += GetFrameTime();

                if (obstaculo_atual->animacao_andar.anim_timer >= obstaculo_atual->animacao_andar.intervalo_frame) {
                    obstaculo_atual->animacao_andar.anim_timer = 0.0f;
                    obstaculo_atual->animacao_andar.frame_atual =
                        (obstaculo_atual->animacao_andar.frame_atual + 1) %
                        obstaculo_atual->animacao_andar.num_frames;
                }

                Texture2D tex = textures[obstaculo_atual->animacao_andar.frame_atual];

                DrawTexturePro(
                    tex,
                    (Rectangle){0, 0, tex.width, tex.height},
                    hitbox_visual,
                    (Vector2){0, 0},
                    0.0f,
                    WHITE
                );
            } else {
                DrawRectangleRec(hitbox_visual, Fade(cor_obstaculo(obstaculo_atual), 0.5f));
                DrawRectangleLinesEx(hitbox_visual, 2.0f, cor_obstaculo(obstaculo_atual));
            }

            no_atual = no_atual->proximo;
        }

        Item *item_atual = itens_ativos->next;

        while (item_atual != NULL) {
            Texture2D *tex_item = NULL;

            if (item_atual->tipo == ITEM_ESCUDO)      tex_item = &escudo_sprite;
            else if (item_atual->tipo == ITEM_PA)     tex_item = &pa_sprite;
            else if (item_atual->tipo == ITEM_MOEDA)  tex_item = &moeda_sprite;
            else if (item_atual->tipo == ITEM_PEIXE)  tex_item = &peixe_sprite;

            if (tex_item != NULL) {
                float tamanho_item = 60.0f;

                DrawTexturePro(
                    *tex_item,
                    (Rectangle){0, 0, tex_item->width, tex_item->height},
                    (Rectangle){
                        item_atual->pos.x,
                        item_atual->pos.y,
                        tamanho_item,
                        tamanho_item
                    },
                    (Vector2){0, 0},
                    0.0f,
                    WHITE
                );
            } else {
                DrawRectangle(
                    item_atual->pos.x,
                    item_atual->pos.y,
                    item_atual->hitbox.largura,
                    item_atual->hitbox.altura,
                    cor_item(item_atual)
                );
            }

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

        if (clima_atual.tipo == CLIMA_CHUVA) {
            desenhar_chuva(&clima_atual);
        }

        EndDrawing();

        if (IsKeyDown(KEY_P)) break;
    }
}

void jogo_encerrar(void) {
    hud_encerrar();

    UnloadTexture(fundo_jogo);
    UnloadTexture(escudo_sprite);
    UnloadTexture(pa_sprite);
    UnloadTexture(moeda_sprite);
    UnloadTexture(peixe_sprite);

    for (int i = 0; i < 8; i++)
        UnloadTexture(jogador_textures[i]);

    for (int i = 0; i < 3; i++)
        UnloadTexture(barco_textures[i]);

    UnloadTexture(garrafa_textures[0]);
    UnloadTexture(garrafa_textures[1]);

    for (int i = 0; i < TRONCO_PADRAO.animacao_andar.num_frames; i++)
        UnloadTexture(tronco_textures[i]);

    for (int i = 0; i < LIXO_NO_RIO_SACOLA_PADRAO.animacao_andar.num_frames; i++)
        UnloadTexture(sacola_textures[i]);

    for (int i = 0; i < PEDRA1_PADRAO.animacao_andar.num_frames; i++)
        UnloadTexture(pedra1_textures[i]);

    for (int i = 0; i < PEDRA2_PADRAO.animacao_andar.num_frames; i++)
        UnloadTexture(pedra2_textures[i]);

    if (jogador_principal.inventario != NULL) {
        int moedas = inventario_quantidade_item(jogador_principal.inventario, ITEM_MOEDA);

        Ranking *ranking = ranking_criar();
        if (ranking != NULL) {
            ranking_inserir(ranking, jogador_principal.nome, moedas);
            ranking_destruir(ranking);
        }

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