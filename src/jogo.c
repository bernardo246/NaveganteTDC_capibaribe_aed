/* jogo.c - Logica principal do jogo Navegador Capibaribe (Dev 4) */

#include <raylib.h> // TODO: interface grafica - raylib
#include <stdio.h>
#include "jogo.h"
#include "../lib/fila.h"
#include "../lib/arvore.h"
#include "../lib/ranking.h"

void jogo_iniciar(void) {
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
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Navegante Capibaribe", 40, 40, 30, DARKBLUE);
            EndDrawing();
    }
}

void jogo_encerrar(void) {
    /* TODO: liberar recursos e salvar recorde */
    CloseWindow();
}
