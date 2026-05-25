#ifndef GERENCIADOR_TEXTURAS_H
#define GERENCIADOR_TEXTURAS_H

#include <raylib.h>

typedef struct {
    Texture2D tronco[8];
} TexturasJogo;

void texturas_carregar(TexturasJogo *texturas);
void texturas_descarregar(TexturasJogo *texturas);
Texture2D texturas_get_frame_tronco(TexturasJogo *texturas, int frame_atual);

#endif