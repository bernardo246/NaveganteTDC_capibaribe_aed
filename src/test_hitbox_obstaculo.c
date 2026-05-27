#include <raylib.h>
#include <stdio.h>
#include "../include/entidades.h"

int main() {
    InitWindow(1280, 720, "Teste Hitbox");
    SetTargetFPS(60);

    const obstaculo obstaculos[] = {
        TRONCO_PADRAO,
        LIXO_NO_RIO_GARRAFA_PADRAO,
        LIXO_NO_RIO_SACOLA_PADRAO,
        PEDRA1_PADRAO,
        PEDRA2_PADRAO,
        BARCO_PADRAO
    };
    int total = 6;

    // caminho manual pro barco já que não tem frame
    const char *caminhos[] = {
        obstaculos[0].animacao_andar.frames[0],
        obstaculos[1].animacao_andar.frames[0],
        obstaculos[2].animacao_andar.frames[0],
        obstaculos[3].animacao_andar.frames[0],
        obstaculos[4].animacao_andar.frames[0],
        "assets/sprites/obstaculos/barco/barco_devagar.png"
    };

    Texture2D texturas[6];
    for (int i = 0; i < total; i++) {
        texturas[i] = LoadTexture(caminhos[i]);
    }

    Vector2 posicoes[] = {
        {50,  50},
        {400, 50},
        {600, 50},
        {50,  300},
        {200, 300},
        {400, 300}
    };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < total; i++) {
            Rectangle src = {0, 0, texturas[i].width, texturas[i].height};
            Rectangle dst = {
                posicoes[i].x,
                posicoes[i].y,
                obstaculos[i].hitbox.largura,
                obstaculos[i].hitbox.altura
            };

            DrawTexturePro(texturas[i], src, dst, (Vector2){0,0}, 0, WHITE);
            DrawRectangleLinesEx(dst, 2, RED);
            DrawText(obstaculos[i].nome, dst.x, dst.y - 18, 16, BLACK);
        }

        DrawText(TextFormat("Mouse: %.0f, %.0f", mouse.x, mouse.y), 10, 680, 20, BLACK);

        EndDrawing();
    }

    for (int i = 0; i < total; i++) UnloadTexture(texturas[i]);
    CloseWindow();
    return 0;
}