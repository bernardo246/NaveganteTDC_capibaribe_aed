#include "hud.h"

#define SLOT_TAMANHO 50
#define SLOT_MARGEM  10
#define TOTAL_SLOTS  4

void hud_desenhar(jogador *j) {
    int inicio_x = 20;
    int inicio_y = 720 - SLOT_TAMANHO - 50;

    // desenha os 4 slots vazios semi-transparentes
    for (int i = 0; i < TOTAL_SLOTS; i++) {
        int x = inicio_x + i * (SLOT_TAMANHO + SLOT_MARGEM);
        DrawRectangle(x, inicio_y, SLOT_TAMANHO, SLOT_TAMANHO, Fade(DARKGRAY, 0.5f));
        DrawRectangleLines(x, inicio_y, SLOT_TAMANHO, SLOT_TAMANHO, WHITE);
    }

        // corações de vida
    int coracao_x = inicio_x + TOTAL_SLOTS * (SLOT_TAMANHO + SLOT_MARGEM) + 20;
    int coracao_y = inicio_y + 10;

    int coracoes_cheios = 0;
    if (j->vida > 60) coracoes_cheios = 3;
    else if (j->vida > 20) coracoes_cheios = 2;
    else if (j->vida > 0)  coracoes_cheios = 1;

    for (int i = 0; i < 3; i++) {
        Color cor = (i < coracoes_cheios) ? RED : GRAY;
        DrawText("\xe2\x99\xa5", coracao_x + i * 40, coracao_y, 40, cor);
    }

    // percorre o inventario e preenche os slots
    if (j->inventario == NULL || j->inventario->atual == NULL) return;

    InventarioItem *item = j->inventario->atual;
    do {
        int slot_index = (int)item->tipo - 1;
        int x = inicio_x + slot_index * (SLOT_TAMANHO + SLOT_MARGEM);

        DrawText(TextFormat("%d", item->quantidade),
                 x + SLOT_TAMANHO - 16,
                 inicio_y + SLOT_TAMANHO - 18,
                 16, YELLOW);

        item = item->next;
    } while (item != j->inventario->atual);
}