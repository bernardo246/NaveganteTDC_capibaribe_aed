#include "../include/gerenciador_texturas.h"
#include "../include/default_structs.h"
#include "../include/entidades.h"

extern const Tronco TRONCO_PADRAO;

void texturas_carregar(TexturasJogo *texturas) {
    for (int i = 0; i < TRONCO_PADRAO.animacao_andar.num_frames; i++) {
        texturas->tronco[i] = LoadTexture(TRONCO_PADRAO.animacao_andar.frames[i]);
    }
}

void texturas_descarregar(TexturasJogo *texturas) {
    for (int i = 0; i < 8; i++) {
        UnloadTexture(texturas->tronco[i]);
    }
}

Texture2D texturas_get_frame_tronco(TexturasJogo *texturas, int frame_atual) {
    return texturas->tronco[frame_atual];
}