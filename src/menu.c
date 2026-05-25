/* menu.c - Menu e loop principal do jogo (Dev 4) */

#include <raylib.h> // TODO: interface grafica - raylib
#include <stdio.h>
#include "menu.h"
#include "jogo.h"

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
            if (CheckCollisionPointRec(mouse, botao_jogar))   { jogo_iniciar(); }
            if (CheckCollisionPointRec(mouse, botao_ranking)) { /* ranking */ }
            if (CheckCollisionPointRec(mouse, botao_sair))    { break; }
        }

        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))  opcao = (opcao + 1) % 3;
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))    opcao = (opcao + 2) % 3;

        if (IsKeyPressed(KEY_ENTER)) {
            if (opcao == 0) { jogo_iniciar(); }
            if (opcao == 1) { /* ranking */  }
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