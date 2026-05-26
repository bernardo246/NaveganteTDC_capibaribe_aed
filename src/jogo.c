/* jogo.c - Logica principal do jogo Navegador Capibaribe (Dev 4) */
#include "jogo.h"
#include "hud.h"

#include "../lib/fila.h"
#include "../lib/lista.h"
#include "../lib/ranking.h"
#include "../lib/mecanica/movimentacao.h"
#include "../lib/mecanica/fila_de_obstaculos.h"
#include "../lib/inventario/inventario.h"

static jogador jogador_principal;
static Fila *obstaculos_ativos;
static int capacidade_itens_diferentes = 3; // capacidade máxima de tipos de itens diferentes no inventário do jogador
static Texture2D fundo_jogo;

static Texture2D tronco_textures[9];
static Texture2D garrafa_textures[9];
static Texture2D sacola_textures[3];
static Texture2D pedra1_textures[1];
static Texture2D pedra2_textures[1];

// Índices: 0=devagar, 1=acelerando_e_re, 2=vel_media, 3=rapido,
//          4=cima_devagar, 5=baixo_devagar, 6=cima_rapido, 7=baixo_rapido
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

void jogo_iniciar(void) {
    jogador_principal = (jogador){.nome = "Navegante",
        .vida = 100,
        .pontuacao = 0,
        .velocidade = 5,
        .invencivel=0,
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

        // inventario
        .inventario = inventario_criar(capacidade_itens_diferentes)

    };

    fundo_jogo = LoadTexture("assets/sprites/imagem_fundo1.png");
    for (int i = 0; i < 8; i++)
        jogador_textures[i] = LoadTexture(JOGADOR_SPRITE_PATHS[i]);

    for (int i = 0; i < TRONCO_PADRAO.animacao_andar.num_frames; i++)
        tronco_textures[i] = LoadTexture(TRONCO_PADRAO.animacao_andar.frames[i]);
    for (int i = 0; i < LIXO_NO_RIO_GARRAFA_PADRAO.animacao_andar.num_frames; i++)
        garrafa_textures[i] = LoadTexture(LIXO_NO_RIO_GARRAFA_PADRAO.animacao_andar.frames[i]);
    for (int i = 0; i < LIXO_NO_RIO_SACOLA_PADRAO.animacao_andar.num_frames; i++)
        sacola_textures[i] = LoadTexture(LIXO_NO_RIO_SACOLA_PADRAO.animacao_andar.frames[i]);
    for (int i = 0; i < PEDRA1_PADRAO.animacao_andar.num_frames; i++)
        pedra1_textures[i] = LoadTexture(PEDRA1_PADRAO.animacao_andar.frames[i]);
    for (int i = 0; i < PEDRA2_PADRAO.animacao_andar.num_frames; i++)
        pedra2_textures[i] = LoadTexture(PEDRA2_PADRAO.animacao_andar.frames[i]);

    printf("Iniciando jogo...\n");
    obstaculos_ativos = fila_criar();
    if (jogador_principal.inventario == NULL || obstaculos_ativos == NULL) {
        fprintf(stderr, "Falha ao inicializar o estado do jogo.\n");
        if (obstaculos_ativos != NULL) {
            fila_destruir(obstaculos_ativos);
            obstaculos_ativos = NULL;
        }
        free(jogador_principal.inventario);
        jogador_principal.inventario = NULL;
        return;
    }

    jogador_principal.pontuacao = 0;
    jogador_principal.invencivel = 0;
    jogador_principal.poderes.escudo = false;
    jogador_principal.poderes.pa = false;

    iniciar_cronometro_jogo();
    iniciar_spawn_obstaculos();
    spawn_obstaculo(obstaculos_ativos);
    jogo_atualizar();
    jogo_encerrar();
}

void jogo_atualizar(void) {
    /* TODO: logica de cada frame/turno */

    while(!WindowShouldClose()){
            if(jogador_principal.vida<=0)break;
            mov_jogador(&jogador_principal);
            atualizar_spawn_obstaculos(obstaculos_ativos);
            atualizar_obstaculos(obstaculos_ativos, &jogador_principal);
            if (jogador_principal.vida < 0) {
                jogador_principal.vida = 0;
            }

            BeginDrawing();
            DrawTexturePro(fundo_jogo,
                (Rectangle){0, 0, fundo_jogo.width, fundo_jogo.height},
                (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                (Vector2){0, 0},
                0,
                WHITE
            );
            // Atualiza o tier de velocidade (só sobe, nunca desce)
            {
                int vel = get_velocidade_atual_obstaculos();
                int novo_nivel = (vel <= 1) ? 0 : (vel == 2) ? 1 : (vel == 3) ? 2 : 3;
                if (novo_nivel > jogador_principal.nivel_velocidade)
                    jogador_principal.nivel_velocidade = novo_nivel;
            }

            // Seleciona o sprite correto
            Texture2D *tex_j;
            if (jogador_principal.dir_x == -1) {
                tex_j = &jogador_textures[1]; // esquerda: sempre acelerando_e_re
            } else if (jogador_principal.dir_y == -1) {
                tex_j = (jogador_principal.nivel_velocidade <= 1)
                    ? &jogador_textures[4]   // cima_devagar
                    : &jogador_textures[6];  // cima_rapido
            } else if (jogador_principal.dir_y == 1) {
                tex_j = (jogador_principal.nivel_velocidade <= 1)
                    ? &jogador_textures[5]   // baixo_devagar
                    : &jogador_textures[7];  // baixo_rapido
            } else {
                tex_j = &jogador_textures[jogador_principal.nivel_velocidade]; // devagar/acelerando/vel_media/rapido
            }

            DrawTexturePro(*tex_j,
                (Rectangle){0, 0, tex_j->width, tex_j->height},
                (Rectangle){jogador_principal.pos.x, jogador_principal.pos.y,
                             jogador_principal.hitbox.largura, jogador_principal.hitbox.altura},
                (Vector2){0, 0},
                0.0f,
                WHITE
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

                Texture2D *textures = NULL;
                if (strcmp(obstaculo_atual->nome, "Tronco") == 0)          textures = tronco_textures;
                else if (strcmp(obstaculo_atual->nome, "Garrafa no rio") == 0) textures = garrafa_textures;
                else if (strcmp(obstaculo_atual->nome, "Sacola no rio") == 0)  textures = sacola_textures;
                else if (strcmp(obstaculo_atual->nome, "Pedra pequena") == 0)  textures = pedra1_textures;
                else if (strcmp(obstaculo_atual->nome, "Pedra grande") == 0)   textures = pedra2_textures;

                if (textures != NULL && obstaculo_atual->animacao_andar.num_frames > 0) {
                    obstaculo_atual->animacao_andar.anim_timer += GetFrameTime();
                    if (obstaculo_atual->animacao_andar.anim_timer >= obstaculo_atual->animacao_andar.intervalo_frame) {
                        obstaculo_atual->animacao_andar.anim_timer = 0.0f;
                        obstaculo_atual->animacao_andar.frame_atual =
                            (obstaculo_atual->animacao_andar.frame_atual + 1) % obstaculo_atual->animacao_andar.num_frames;
                    }
                    Texture2D tex = textures[obstaculo_atual->animacao_andar.frame_atual];
                    DrawTexturePro(tex,
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

            hud_desenhar(&jogador_principal);
            
            EndDrawing();

            //fechar janela, por enquanto que n faz algo para retornar ao menu
            if(IsKeyDown(KEY_P))break;
    }
}

void jogo_encerrar(void) {
    UnloadTexture(fundo_jogo);
    for (int i = 0; i < 8; i++)
        UnloadTexture(jogador_textures[i]);

    for (int i = 0; i < TRONCO_PADRAO.animacao_andar.num_frames; i++)
        UnloadTexture(tronco_textures[i]);
    for (int i = 0; i < LIXO_NO_RIO_GARRAFA_PADRAO.animacao_andar.num_frames; i++)
        UnloadTexture(garrafa_textures[i]);
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

}
