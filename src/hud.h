#ifndef HUD_H
#define HUD_H

#include <raylib.h>
#include "../include/entidades.h"
#include "../lib/inventario/inventario.h"

void hud_iniciar(void);
void hud_encerrar(void);
void hud_desenhar(jogador *j);
void hud_desenhar_moedas(int quantidade);

#endif /* HUD_H */