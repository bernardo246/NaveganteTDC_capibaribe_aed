/* menu.c - Menu e loop principal do jogo (Dev 4) */

#include <raylib.h> // TODO: interface grafica - raylib
#include <stdio.h>
#include "menu.h"
#include "jogo.h"

void menu_iniciar(void) {
    InitWindow(1280, 720, "Navegador do Capibaribe");
    SetTargetFPS(60);

    Rectangle botao_jogar  = {490, 300, 300, 60};
    Rectangle botao_ranking = {490, 380, 300, 60};
    Rectangle botao_sair   = {490, 460, 300, 60};

    int opcao = 0;

    while (!WindowShouldClose()) {
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
        ClearBackground((Color){0, 105, 148, 255});

        DrawText("Navegador do Capibaribe", 340, 150, 50, WHITE);

        DrawRectangleRec(botao_jogar, (opcao == 0 || CheckCollisionPointRec(mouse, botao_jogar))   ? BLUE : DARKBLUE);
        DrawRectangleRec(botao_ranking, (opcao == 1 || CheckCollisionPointRec(mouse, botao_ranking)) ? BLUE : DARKBLUE);
        DrawRectangleRec(botao_sair, (opcao == 2 || CheckCollisionPointRec(mouse, botao_sair))    ? BLUE : DARKBLUE);

        DrawText("Novo Jogo",   555, 318, 30, WHITE);
        DrawText("Ver Ranking", 540, 398, 30, WHITE);
        DrawText("Sair",        600, 478, 30, WHITE);

        EndDrawing();
    }

    CloseWindow();
}