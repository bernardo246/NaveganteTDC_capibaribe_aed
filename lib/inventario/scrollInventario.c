#include <raylib.h>
#include "scrollInventario.h"

void scroll_proximo(Inventario *inventario) {
    if (!inventario || !inventario->atual) return;
    inventario->atual = inventario->atual->next;
}

void scroll_anterior(Inventario *inventario) {
    if (!inventario || !inventario->atual) return;
    inventario->atual = inventario->atual->prev;
}

void atualizar_scroll(Inventario *inventario) {
    if (!inventario || !inventario->atual) return;

    float roda = GetMouseWheelMove();
    if (roda > 0) scroll_proximo(inventario);
    if (roda < 0) scroll_anterior(inventario);
}