#include "hud.h"

#define SLOT_TAMANHO 50
#define SLOT_MARGEM  10
#define TOTAL_SLOTS  4

static Texture2D coracao_hud = {0};
static Texture2D escudo_sprite = {0};
static Texture2D pa_sprite = {0};

void hud_iniciar(void) {
    coracao_hud = LoadTexture("assets/sprites/coracao_hud.png");

    escudo_sprite = LoadTexture("assets/sprites/itens/escudo.png");
    pa_sprite = LoadTexture("assets/sprites/itens/pa.png");
}

void hud_encerrar(void) {
    UnloadTexture(coracao_hud);

    UnloadTexture(escudo_sprite);
    UnloadTexture(pa_sprite);
}

void hud_desenhar(jogador *j) {
    int inicio_x = 20;
    int inicio_y = 720 - SLOT_TAMANHO - 50;

    for (int i = 0; i < TOTAL_SLOTS; i++) {
        int x = inicio_x + i * (SLOT_TAMANHO + SLOT_MARGEM);

        int slot_selecionado =
            (j->inventario && j->inventario->atual)
            ? (int)j->inventario->atual->tipo - 1
            : -1;

        Color cor_slot =
            (i == slot_selecionado)
            ? Fade(YELLOW, 0.4f)
            : Fade(DARKGRAY, 0.5f);

        Color cor_borda =
            (i == slot_selecionado)
            ? YELLOW
            : WHITE;

        DrawRectangle(
            x,
            inicio_y,
            SLOT_TAMANHO,
            SLOT_TAMANHO,
            cor_slot
        );

        DrawRectangleLines(
            x,
            inicio_y,
            SLOT_TAMANHO,
            SLOT_TAMANHO,
            cor_borda
        );
    }

    int coracao_x =
        inicio_x +
        TOTAL_SLOTS * (SLOT_TAMANHO + SLOT_MARGEM) +
        20;

    int coracao_y = inicio_y;

    int coracoes_cheios = 0;

    if (j->vida > 60) coracoes_cheios = 3;
    else if (j->vida > 20) coracoes_cheios = 2;
    else if (j->vida > 0) coracoes_cheios = 1;

    for (int i = 0; i < 3; i++) {
        Color cor = (i < coracoes_cheios)
            ? WHITE
            : GRAY;

        DrawTexture(
            coracao_hud,
            coracao_x + i * 44,
            coracao_y,
            cor
        );
    }

    if (j->inventario == NULL || j->inventario->atual == NULL)
        return;

    InventarioItem *item = j->inventario->atual;

    do {
        int slot_index = (int)item->tipo - 1;

        int x =
            inicio_x +
            slot_index * (SLOT_TAMANHO + SLOT_MARGEM);

        Texture2D *tex_item = NULL;

        if (item->tipo == ITEM_ESCUDO) {
            tex_item = &escudo_sprite;
        }
        else if (item->tipo == ITEM_PA) {
            tex_item = &pa_sprite;
        }

        if (tex_item != NULL) {
            DrawTexturePro(
                *tex_item,
                (Rectangle){
                    0,
                    0,
                    tex_item->width,
                    tex_item->height
                },
                (Rectangle){
                    x + 4,
                    inicio_y + 4,
                    42,
                    42
                },
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
        }

        DrawText(
            TextFormat("%d", item->quantidade),
            x + SLOT_TAMANHO - 16,
            inicio_y + SLOT_TAMANHO - 18,
            16,
            WHITE
        );

        item = item->next;

    } while (item != j->inventario->atual);
}