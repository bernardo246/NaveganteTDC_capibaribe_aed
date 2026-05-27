#include "hud.h"

#define SLOT_TAMANHO 50
#define SLOT_MARGEM  10

static Texture2D coracao_hud  = {0};
static Texture2D escudo_sprite = {0};
static Texture2D pa_sprite     = {0};
static Texture2D moeda_sprite  = {0};
static Texture2D peixe_sprite  = {0};

void hud_iniciar(void) {
    coracao_hud   = LoadTexture("assets/sprites/coracao_hud.png");
    escudo_sprite = LoadTexture("assets/sprites/itens/escudo.png");
    pa_sprite     = LoadTexture("assets/sprites/itens/pa.png");
    moeda_sprite  = LoadTexture("assets/sprites/itens/moeda.png");
    peixe_sprite  = LoadTexture("assets/sprites/itens/peixe.png");
}

void hud_encerrar(void) {
    UnloadTexture(coracao_hud);
    UnloadTexture(escudo_sprite);
    UnloadTexture(pa_sprite);
    UnloadTexture(moeda_sprite);
    UnloadTexture(peixe_sprite);
}

void hud_desenhar_moedas(int quantidade) {
    char texto[32];
    snprintf(texto, sizeof(texto), "Moedas: %d", quantidade);
    
    int largura_texto = MeasureText(texto, 20);
    int x = GetScreenWidth() - largura_texto - 20;
    int y = 20;

    DrawTexturePro(
        moeda_sprite,
        (Rectangle){0, 0, moeda_sprite.width, moeda_sprite.height},
        (Rectangle){x - 40, y, 30, 30},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    DrawText(texto, x, y + 5, 20, WHITE);
}

void hud_desenhar(jogador *j) {
    int inicio_x = 20;
    int inicio_y = 720 - SLOT_TAMANHO - 50;

    int total_slots = (j->inventario)
        ? j->inventario->capacidade_itens_diferentes
        : 4;

    // determina qual slot esta selecionado
    int slot_selecionado = -1;
    if (j->inventario && j->inventario->atual && j->inventario->primeiro) {
        InventarioItem *item = j->inventario->primeiro;
        int idx = 0;
        do {
            if (item == j->inventario->atual) {
                slot_selecionado = idx;
                break;
            }
            idx++;
            item = item->next;
        } while (item != j->inventario->primeiro);
    }

    hud_desenhar_moedas(int quantidade);

    // desenha slots vazios
    for (int i = 0; i < total_slots; i++) {
        int x = inicio_x + i * (SLOT_TAMANHO + SLOT_MARGEM);

        Color cor_slot  = (i == slot_selecionado) ? Fade(YELLOW, 0.4f) : Fade(DARKGRAY, 0.5f);
        Color cor_borda = (i == slot_selecionado) ? YELLOW : WHITE;

        DrawRectangle(x, inicio_y, SLOT_TAMANHO, SLOT_TAMANHO, cor_slot);
        DrawRectangleLines(x, inicio_y, SLOT_TAMANHO, SLOT_TAMANHO, cor_borda);
    }

    // desenha itens nos slots em ordem de coleta
    if (j->inventario && j->inventario->primeiro) {
        InventarioItem *item = j->inventario->primeiro;
        int slot_index = 0;

        do {
            int x = inicio_x + slot_index * (SLOT_TAMANHO + SLOT_MARGEM);

            // barra de duracao do poder
            double tempo_total    = 0;
            double tempo_decorrido = 0;
            bool poder_ativo = false;

            if (item->tipo == ITEM_ESCUDO && j->poderes.escudo) {
                tempo_total     = 5.0;
                tempo_decorrido = GetTime() - j->poderes.tempo_escudo;
                poder_ativo     = true;
            } else if (item->tipo == ITEM_PA && j->poderes.pa) {
                tempo_total     = 10.0;
                tempo_decorrido = GetTime() - j->poderes.tempo_pa;
                poder_ativo     = true;
            }

            if (poder_ativo) {
                double progresso = 1.0 - (tempo_decorrido / tempo_total);
                if (progresso < 0) progresso = 0;
                int altura_barra = (int)(SLOT_TAMANHO * progresso);
                DrawRectangle(x, inicio_y, SLOT_TAMANHO, altura_barra, Fade(GREEN, 0.7f));
            }

            // sprite do item
            Texture2D *tex = NULL;
            if (item->tipo == ITEM_ESCUDO)     tex = &escudo_sprite;
            else if (item->tipo == ITEM_PA)    tex = &pa_sprite;
            else if (item->tipo == ITEM_MOEDA) tex = &moeda_sprite;
            else if (item->tipo == ITEM_PEIXE) tex = &peixe_sprite;

            if (tex != NULL) {
                DrawTexturePro(
                    *tex,
                    (Rectangle){0, 0, tex->width, tex->height},
                    (Rectangle){x + 4, inicio_y + 4, 42, 42},
                    (Vector2){0, 0},
                    0.0f,
                    WHITE
                );
            }

            // quantidade
            DrawText(
                TextFormat("%d", item->quantidade),
                x + SLOT_TAMANHO - 16,
                inicio_y + SLOT_TAMANHO - 18,
                16,
                WHITE
            );

            slot_index++;
            item = item->next;
        } while (item != j->inventario->primeiro);
    }

    // coracoes
    int coracao_x = inicio_x + total_slots * (SLOT_TAMANHO + SLOT_MARGEM) + 20;
    int coracao_y = inicio_y;

    int coracoes_cheios = 0;
    if (j->vida > 60)      coracoes_cheios = 3;
    else if (j->vida > 20) coracoes_cheios = 2;
    else if (j->vida > 0)  coracoes_cheios = 1;

    for (int i = 0; i < 3; i++) {
        Color cor = (i < coracoes_cheios) ? WHITE : GRAY;
        DrawTexture(coracao_hud, coracao_x + i * 44, coracao_y, cor);
    }
}