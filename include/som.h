#ifndef SOM_H
#define SOM_H

#include <raylib.h>

typedef enum {
    SOM_NENHUM = 0,
    SOM_REMANDO = 1,
    SOM_TROCA_ITEM_INVENTARIO = 2,
    SOM_PEGOU_PA = 3,
    SOM_PEGOU_MOEDA = 4,
    SOM_COLISAO_GARRAFA = 5,
    SOM_COLISAO_PONTE = 6,
    SOM_ATIVACAO_ESCUDO = 7,
    SOM_COLISAO_SACOLA = 8,
    SOM_PEGOU_ESCUDO = 9,
    SOM_PEGOU_PEIXE = 10,
    SOM_COLISAO_TRONCO = 11,
    SOM_COLISAO_PEDRA = 12,
    SOM_CURAR = 13,
    SOM_MUSICA_INTRO = 14,
    SOM_TOTAL = 15
} TipoSom;

void sons_carregar(void);
void sons_descarregar(void);
void tocar_som(TipoSom tipo);
void atualizar_musica(void);

#endif