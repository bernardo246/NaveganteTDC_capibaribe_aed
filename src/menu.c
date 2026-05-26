/* menu.c - Menu e loop principal do jogo (Dev 4) */

#include <raylib.h> // TODO: interface grafica - raylib
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "jogo.h"
#include "../lib/ranking.h"

static int capturar_nome_jogador(char *destino, size_t tamanho) {
    if (destino == NULL || tamanho == 0) return 0;
    destino[0] = '\0';

    Rectangle campo = {
        GetScreenWidth() / 2.0f - 250,
        GetScreenHeight() / 2.0f - 40,
        500,
        60
    };
    Rectangle botao_iniciar = {
        GetScreenWidth() / 2.0f - 150,
        GetScreenHeight() / 2.0f + 40,
        300,
        60
    };

    int tamanho_atual = 0;
    while (!WindowShouldClose()) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126 && tamanho_atual < (int)tamanho - 1) {
                destino[tamanho_atual++] = (char)key;
                destino[tamanho_atual] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && tamanho_atual > 0) {
            destino[--tamanho_atual] = '\0';
        }

        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse, botao_iniciar) &&
            tamanho_atual > 0) {
            return 1;
        }

        if (IsKeyPressed(KEY_ENTER) && tamanho_atual > 0) {
            return 1;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Digite seu nome", (int)campo.x, (int)campo.y - 40, 24, RAYWHITE);
        DrawRectangleRec(campo, (Color){30, 30, 30, 255});
        DrawRectangleLinesEx(campo, 2.0f, RAYWHITE);
        DrawText(destino, (int)campo.x + 12, (int)campo.y + 16, 24, RAYWHITE);

        Color cor_botao = (tamanho_atual > 0) ? (Color){200, 180, 90, 255} : (Color){90, 90, 90, 255};
        DrawRectangleRounded(botao_iniciar, 0.2f, 10, cor_botao);
        DrawRectangleRoundedLines(botao_iniciar, 0.2f, 10, RAYWHITE);
        DrawText("INICIAR", (int)botao_iniciar.x + 85, (int)botao_iniciar.y + 16, 28, BLACK);

        EndDrawing();
    }

    return 0;
}

void menu_iniciar(void) {
    InitWindow(1280, 720, "Navegador do Capibaribe");

    int largura = GetMonitorWidth(0);
    int altura = GetMonitorHeight(0);
    
    SetTargetFPS(60);

    int opcao = 0;

    Texture2D fundo = LoadTexture("assets/sprites/tela_menu.png");

    while (!WindowShouldClose()) {

        float larguraBotao = 320;
        float alturaBotao = 70;

        float centroX = GetScreenWidth()/2 - larguraBotao/2;

        Rectangle botao_jogar = {
            centroX,
            300,
            larguraBotao,
            alturaBotao
        };

        Rectangle botao_ranking = {
            centroX,
            390,
            larguraBotao,
            alturaBotao
        };

        Rectangle botao_sair = {
            centroX,
            480,
            larguraBotao,
            alturaBotao
        };

        Vector2 mouse = GetMousePosition();

        if (GetMouseDelta().x != 0 || GetMouseDelta().y != 0) opcao = -1;
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, botao_jogar))   {
                char nome[32];
                if (capturar_nome_jogador(nome, sizeof(nome))) {
                    jogo_iniciar(nome);
                }
            }
            if (CheckCollisionPointRec(mouse, botao_ranking)) {
                Ranking *ranking = ranking_criar();
                if (ranking != NULL) {
                    ranking_exibir(ranking);
                    ranking_destruir(ranking);
                }
            }
            if (CheckCollisionPointRec(mouse, botao_sair))    { break; }
        }

        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))  opcao = (opcao + 1) % 3;
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))    opcao = (opcao + 2) % 3;

        if (IsKeyPressed(KEY_ENTER)) {
            if (opcao == 0) {
                char nome[32];
                if (capturar_nome_jogador(nome, sizeof(nome))) {
                    jogo_iniciar(nome);
                }
            }
            if (opcao == 1) {
                Ranking *ranking = ranking_criar();
                if (ranking != NULL) {
                    ranking_exibir(ranking);
                    ranking_destruir(ranking);
                }
            }
            if (opcao == 2) { break;         }
        }

        BeginDrawing();
        DrawTexturePro(fundo,
            (Rectangle){0, 0, fundo.width, fundo.height},
            (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
            (Vector2){0, 0},
            0,
            WHITE
        );

        // ================= CORES =================

        Color corBotao = (Color){70, 45, 30, 220};
        Color corHover = (Color){210, 170, 80, 255};
        Color corTexto = (Color){255, 245, 220, 255};

        // ================= HOVER =================

        bool hoverJogar = CheckCollisionPointRec(mouse, botao_jogar);
        bool hoverRanking = CheckCollisionPointRec(mouse, botao_ranking);
        bool hoverSair = CheckCollisionPointRec(mouse, botao_sair);

        // ================= BOTÕES =================

        DrawRectangleRounded(
            botao_jogar,
            0.25f,
            10,
            hoverJogar ? corHover : corBotao
        );

        DrawRectangleRounded(
            botao_ranking,
            0.25f,
            10,
            hoverRanking ? corHover : corBotao
        );

        DrawRectangleRounded(
            botao_sair,
            0.25f,
            10,
            hoverSair ? corHover : corBotao
        );

        // ================= BORDAS =================

        DrawRectangleRoundedLines(
            botao_jogar,
            0.25f,
            10,
            DARKBROWN
        );

        DrawRectangleRoundedLines(
            botao_ranking,
            0.25f,
            10,
            DARKBROWN
        );

        DrawRectangleRoundedLines(
            botao_sair,
            0.25f,
            10,
            DARKBROWN
        );

        // ================= TEXTO =================

        DrawText(
            "NOVO JOGO",
            botao_jogar.x + 55,
            botao_jogar.y + 18,
            32,
            corTexto
        );

        DrawText(
            "VER RANKING",
            botao_ranking.x + 40,
            botao_ranking.y + 18,
            32,
            corTexto
        );

        DrawText(
            "SAIR",
            botao_sair.x + 115,
            botao_sair.y + 18,
            32,
            corTexto
        );

        EndDrawing();
    }

    UnloadTexture(fundo);

    CloseWindow();
}